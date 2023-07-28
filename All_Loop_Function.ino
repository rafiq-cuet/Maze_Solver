
void pid_lfr() {

  for (int i = 0; i < numSensors; i++) {
    int sensorValue = analogRead(sensorPins[i]);
    if (sensorValue > threshold) {
      s[i] = 0;
    } else {
      s[i] = 1;
    }
  }

  if (s[2] == 1 && s[11] == 0) left();
  else if (s[2] == 0 && s[11] == 1) right();
  else if (s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0 && s[4] == 0 && s[5] == 0 && s[6] == 0 && s[7] == 0 && s[8] == 0 && s[9] == 0 && s[10] == 0 && s[11] == 0 && s[12] == 0 && s[13] == 0) u_turn();
  else if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 1 && s[6] == 1 && s[7] == 1 && s[8] == 1 && s[9] == 1 && s[10] == 1 && s[11] == 1 && s[12] == 1 && s[13] == 1) short_path();




  int position = (s[2] * 0 + s[3] * 1000 + s[4] * 2000 + s[5] * 3000 + s[6] * 4000 + s[7] * 5000 + s[8] * 6000 + s[9] * 7000 + s[10] * 8000 + s[11] * 9000) / (s[2] + s[3] + s[4] + s[5] + s[6] + s[7] + s[8] + s[9] + s[10] + s[11]);

  int error = position - 4500;

  float P = error;
  float I = I + error;
  float D = error - lastError;
  lastError = error;


  int motorSpeed = Kp * error + Ki * I + Kd * D;


  int rightMotorSpeed = BaseSpeed + motorSpeed;
  int leftMotorSpeed = BaseSpeed - motorSpeed;

  if (rightMotorSpeed > MaxSpeed) rightMotorSpeed = MaxSpeed;  // prevent the motor from going beyond max speed
  if (leftMotorSpeed > MaxSpeed) leftMotorSpeed = MaxSpeed;    // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0;
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;

  motor(leftMotorSpeed, rightMotorSpeed);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// This is for Maze Solver
void pid_maze() {

  for (int i = 0; i < numSensors; i++) {
    int sensorValue = analogRead(sensorPins[i]);
    if (sensorValue > threshold) {
      s[i] = 0;
    } else {
      s[i] = 1;
    }
  }

  // 90 degree left
  if ((s[0] == 1 || s[1] == 1 || s[2] == 1) && (s[3] == 1 && s[4] == 0 && s[5] == 0 && s[6] == 0 && s[7] == 0 && s[8] == 0 && s[9] == 0 && s[10] == 0 && s[11] == 0 && s[12] == 0 && s[13] == 0)) left();
  // 90 degree right
  else if ((s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0 && s[4] == 0 && s[5] == 0 && s[6] == 0 && s[7] == 0 && s[8] == 0 && s[9] == 0) && (s[10] == 1 || s[11] == 1 || s[12] == 1 || s[13] == 1)) right();
  // maze left
  else if ((s[0] == 1 || s[1] == 1) && (s[4] == 1 || s[5] == 1 || s[6] == 1 || s[7] == 1 || s[8] == 1 || s[9] == 1) && (s[2] == 0 && s[3] == 0 && s[10] == 0 && s[11] == 0 && s[12] == 0 && s[13] == 0)) force_maze_left();
  // maze right  000--111100011
  else if ((s[12] == 1 || s[13] == 1) && (s[4] == 1 || s[5] == 1 || s[6] == 1 || s[7] == 1 || s[8] == 1 || s[9] == 1) && (s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0 && s[10] == 0 && s[11] == 0)) maze_right();
  // T junction  11100000000111
  //else if ((s[0] == 1 || s[1] == 1 || s[2] == 1) && (s[11] == 1 || s[12] == 1 || s[13] == 1) && (s[3] == 0 && s[4] == 0 && s[5] == 0 && s[6] == 0 && s[7] == 0 && s[8] == 0 && s[9] == 0 && s[10] == 0)) maze_left();
  else if ((s[3] == 1 && s[4] == 1 && s[5] == 1 && s[6] == 1 && s[7] == 1 && s[8] == 1 && s[9] == 1 && s[10] == 1)) t_junction();
  // backward
  else if (s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0 && s[4] == 0 && s[5] == 0 && s[6] == 0 && s[7] == 0 && s[8] == 0 && s[9] == 0 && s[10] == 0 && s[11] == 0 && s[12] == 0 && s[13] == 0) u_turn();
  // stop
  else if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 1 && s[6] == 1 && s[7] == 1 && s[8] == 1 && s[9] == 1 && s[10] == 1 && s[11] == 1 && s[12] == 1 && s[13] == 1) short_path();



  int position = (s[2] * 0 + s[3] * 1000 + s[4] * 2000 + s[5] * 3000 + s[6] * 4000 + s[7] * 5000 + s[8] * 6000 + s[9] * 7000 + s[10] * 8000 + s[11] * 9000) / (s[2] + s[3] + s[4] + s[5] + s[6] + s[7] + s[8] + s[9] + s[10] + s[11]);

  int error = position - 4500;

  float P = error;
  float I = I + error;
  float D = error - lastError;
  lastError = error;


  int motorSpeed = Kp * error + Ki * I + Kd * D;


  int rightMotorSpeed = BaseSpeed + motorSpeed;
  int leftMotorSpeed = BaseSpeed - motorSpeed;

  if (rightMotorSpeed > MaxSpeed) rightMotorSpeed = MaxSpeed;  // prevent the motor from going beyond max speed
  if (leftMotorSpeed > MaxSpeed) leftMotorSpeed = MaxSpeed;    // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0;
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;

  motor(leftMotorSpeed, rightMotorSpeed);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// This is for Maze Solver
void pid_maze_solve() {

  for (int i = 0; i < numSensors; i++) {
    int sensorValue = analogRead(sensorPins[i]);
    if (sensorValue > threshold) {
      s[i] = 0;
    } else {
      s[i] = 1;
    }
  }

  // 90 degree left
  if ((s[0] == 1 || s[1] == 1 || s[2] == 1) && (s[3] == 1 && s[4] == 0 && s[5] == 0 && s[6] == 0 && s[7] == 0 && s[8] == 0 && s[9] == 0 && s[10] == 0 && s[11] == 0 && s[12] == 0 && s[13] == 0)) solve_left();
  // 90 degree right
  else if ((s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0 && s[4] == 0 && s[5] == 0 && s[6] == 0 && s[7] == 0 && s[8] == 0 && s[9] == 0) && (s[10] == 1 || s[11] == 1 || s[12] == 1 || s[13] == 1)) solve_right();
  // maze left
  else if ((s[0] == 1 || s[1] == 1) && (s[4] == 1 || s[5] == 1 || s[6] == 1 || s[7] == 1 || s[8] == 1 || s[9] == 1) && (s[2] == 0 && s[3] == 0 && s[10] == 0 && s[11] == 0 && s[12] == 0 && s[13] == 0)) SOLVE();
  // maze right  000--111100011
  else if ((s[12] == 1 || s[13] == 1) && (s[4] == 1 || s[5] == 1 || s[6] == 1 || s[7] == 1 || s[8] == 1 || s[9] == 1) && (s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0 && s[10] == 0 && s[11] == 0)) SOLVE();
  // T junction  11100000000111
  else if ((s[3] == 1 && s[4] == 1 && s[5] == 1 && s[6] == 1 && s[7] == 1 && s[8] == 1 && s[9] == 1 && s[10] == 1)) solve_t_junction();
  // backward
  else if (s[0] == 0 && s[1] == 0 && s[2] == 0 && s[3] == 0 && s[4] == 0 && s[5] == 0 && s[6] == 0 && s[7] == 0 && s[8] == 0 && s[9] == 0 && s[10] == 0 && s[11] == 0 && s[12] == 0 && s[13] == 0) u_turn();
  // stop
  else if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 1 && s[6] == 1 && s[7] == 1 && s[8] == 1 && s[9] == 1 && s[10] == 1 && s[11] == 1 && s[12] == 1 && s[13] == 1) complete();



  int position = (s[2] * 0 + s[3] * 1000 + s[4] * 2000 + s[5] * 3000 + s[6] * 4000 + s[7] * 5000 + s[8] * 6000 + s[9] * 7000 + s[10] * 8000 + s[11] * 9000) / (s[2] + s[3] + s[4] + s[5] + s[6] + s[7] + s[8] + s[9] + s[10] + s[11]);

  int error = position - 4500;

  float P = error;
  float I = I + error;
  float D = error - lastError;
  lastError = error;


  int motorSpeed = Kp * error + Ki * I + Kd * D;


  int rightMotorSpeed = solveSpeed + motorSpeed;
  int leftMotorSpeed = solveSpeed - motorSpeed;

  if (rightMotorSpeed > MaxSpeed) rightMotorSpeed = MaxSpeed;  // prevent the motor from going beyond max speed
  if (leftMotorSpeed > MaxSpeed) leftMotorSpeed = MaxSpeed;    // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0;
  if (leftMotorSpeed < 0) leftMotorSpeed = 0;

  motor(leftMotorSpeed, rightMotorSpeed);
}


void SOLVE() {
  String path = readStringFromEEPROM(STRING_ADDRESS);
  if (path[in] == 'S') go_S();
  else if (path[in] == 'L') go_L();
  else if (path[in] == 'R') go_R();
  in = in + 1;
}

void go_S() {
  motor(100, 100);
  delay(190);
}

void go_L() {
  motor(100, 100);
  delay(100);

  motor(100, -80);
  delay(300);
  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }
    if (s[5] == 1 || s[6] == 1 || s[7] == 1) break;
    motor(100, -80);
  }
}

void go_R() {
  motor(100, 100);
  delay(100);

  motor(-80, 100);
  delay(300);
  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }
    if (s[6] == 1 || s[7] == 1 || s[8] == 1) break;
    motor(-80, 100);
  }
}


void solve_t_junction() {
  while (1) {
    motor(100, 100);
    delay(50);

    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }

    if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 1 && s[6] == 1 && s[7] == 1 && s[8] == 1 && s[9] == 1 && s[10] == 1 && s[11] == 1 && s[12] == 1 && s[13] == 1) {
      complete();
      break;
    }

    else {
      SOLVE();
      break;
    }
  }
}


void solve_left() {
  motor(100, 100);
  delay(170);


  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }
    if (s[5] == 1 || s[6] == 1 || s[7] == 1 || s[8] == 1) break;
    motor(100, -80);
  }
}

void solve_right() {
  motor(100, 100);
  delay(170);

  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }
    if (s[5] == 1 || s[6] == 1 || s[7] == 1 || s[8] == 1) break;
    motor(-80, 100);
  }
}

// -----------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------- Turning Loop ------------------------------------------------------------------------//

void left() {
  motor(100, 100);
  delay(190);
  motor(0, 0);
  delay(300);

  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }
    if (s[6] == 1 || s[7] == 1) break;
    motor(100, -80);
  }
}

void right() {
  motor(100, 100);
  delay(190);
  motor(0, 0);
  delay(300);

  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }
    if (s[6] == 1 || s[7] == 1 ) break;
    motor(-80, 100);
  }
}

void force_maze_left() {
  path += 'L';
  motor(100, 100);
  delay(190);
  motor(0, 0);
  delay(300);


  motor(100, -80);
  delay(300);
  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }
    //s[5]==1
    if (s[6] == 1 || s[7] == 1) break;
    motor(100, -80);
  }
}


void maze_left() {
  path += 'L';
  motor(0, 0);
  delay(300);

  motor(100, -80);
  delay(300);
  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }
    if (s[6] == 1 || s[7] == 1) break;
    motor(100, -80);
  }
}

void maze_right() {
  path += 'S';
  motor(40, 40);
  delay(300);
}

void t_junction() {
  while (1) {
    motor(100, 100);
    delay(200);

    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }

    if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 1 && s[6] == 1 && s[7] == 1 && s[8] == 1 && s[9] == 1 && s[10] == 1 && s[11] == 1 && s[12] == 1 && s[13] == 1) {
      short_path();
      break;
    }

    else {
      maze_left();
      break;
    }
  }
}
void u_turn() {
  motor(100, 100);
  delay(100);

  path += 'B';
  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      if (sensorValue > threshold) {
        s[i] = 0;
      } else {
        s[i] = 1;
      }
    }
    motor(-100, 100);
    if (s[6] == 1 || s[7] == 1) break;
  }
  motor(100, -100);
  delay(20);
}

void short_path() {
  motor(0, 0);
  for (int i = 0; i < 200; i++) {
    short_it();
  }

  // this is for store the path in eeprom memory
  String message = path;  // The string to be stored in EEPROM
  writeStringToEEPROM(STRING_ADDRESS, message);

  u8g.setFont(u8g_font_profont12);
  u8g.firstPage();
  do {
    u8g.setPrintPos(10, 10);
    u8g.print("Scan Complete");  // Print the sensor value at coordinates (90, 40)

    u8g.setPrintPos(10, 30);
    u8g.print(path);  // Print the sensor value at coordinates (90, 40)
  } while (u8g.nextPage());


  while (1) {
    motor(0, 0);
    if (digitalRead(23) == LOW) {
    }
  }
}


void complete() {
  u8g.setFont(u8g_font_unifont);  // Set the font
  u8g.firstPage();
  do {
    u8g.setPrintPos(45, 20);
    u8g.print("CUBIT");  // Print the sensor value at coordinates (90, 40)
    u8g.setPrintPos(15, 60);
    u8g.print("alhamdulillah");  // Print the sensor value at coordinates (90, 40)
  } while (u8g.nextPage());

  while (1) {
    motor(0, 0);
  }
}

void writeStringToEEPROM(int address, String data) {
  int length = data.length();
  for (int i = 0; i < length; i++) {
    EEPROM.write(address + i, data[i]);
  }
  EEPROM.write(address + length, '\0');  // Null-terminate the string
}


String readStringFromEEPROM(int address) {
  String data = "";
  char character;
  while (true) {
    character = EEPROM.read(address);
    if (character == '\0') {
      break;  // Null terminator found, end of string
    }
    data += character;
    address++;
  }
  return data;
}


String short_it() {
  path.replace("LBR", "B");
  path.replace("LBS", "R");
  path.replace("RBL", "B");
  path.replace("SBL", "R");
  path.replace("SBS", "B");
  path.replace("LBL", "S");
  return path;
}
