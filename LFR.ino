void Lfr() {
  delay(500);
  while (1) {
    const int NUM_ITEMS_lfr = 2;         // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)
    const int MAX_ITEM_LENGTH_lfr = 20;  // maximum characters for the item name

    char menu_lfr[NUM_ITEMS_lfr][MAX_ITEM_LENGTH_lfr] = { // array with item names
      { "Sensor Test" },
      { "RUN" }
    };
    if (current_screen == 0) {  // MENU SCREEN

      // up and down buttons only work for the menu screen
      if ((digitalRead(BUTTON_UP_PIN) == LOW) && (button_up_clicked == 0)) {  // up button clicked - jump to previous menu item
        item_selected = item_selected - 1;                                    // select previous item
        button_up_clicked = 1;                                                // set button to clicked to only perform the action once
        if (item_selected < 0) {                                              // if first item was selected, jump to last item
          item_selected = NUM_ITEMS_lfr - 1;
        }
      } else if ((digitalRead(BUTTON_DOWN_PIN) == LOW) && (button_down_clicked == 0)) {  // down button clicked - jump to next menu item
        item_selected = item_selected + 1;                                               // select next item
        button_down_clicked = 1;                                                         // set button to clicked to only perform the action once
        if (item_selected >= NUM_ITEMS_lfr) {                                            // last item was selected, jump to first menu item
          item_selected = 0;
        }
      }

      if ((digitalRead(BUTTON_UP_PIN) == HIGH) && (button_up_clicked == 1)) {  // unclick
        button_up_clicked = 0;
      }
      if ((digitalRead(BUTTON_DOWN_PIN) == HIGH) && (button_down_clicked == 1)) {  // unclick
        button_down_clicked = 0;
      }
    }


    if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) {  // select button clicked, jump between screens
      button_select_clicked = 1;                                                    // set button to clicked to only perform the action once
      if (current_screen == 0) {
        current_screen = 1;  // menu items screen --> screenshots screen
      }
      else {
        current_screen = 0;
      }  // qr codes screen --> menu items screen
    }
    if ((digitalRead(BUTTON_SELECT_PIN) == HIGH) && (button_select_clicked == 1)) {  // unclick
      button_select_clicked = 0;
    }

    // set correct values for the previous and next items
    item_sel_previous = item_selected - 1;
    if (item_sel_previous < 0) {
      item_sel_previous = NUM_ITEMS_lfr - 1;  // previous item would be below first = make it the last
    }
    item_sel_next = item_selected + 1;
    if (item_sel_next >= NUM_ITEMS_lfr) {
      item_sel_next = 0;  // next item would be after last = make it the first
    }

    if (item_selected == 0 && button_select_clicked == 1) {
      Sensor_Test_lfr();
    } else if (item_selected == 1 && button_select_clicked == 1) {
      RUN_lfr();
    }


    u8g.firstPage();  // required for page drawing mode for u8g library
    do {
      if (current_screen == 0) {  // MENU SCREEN
        // selected item background
        u8g.drawBitmapP(5, 22, 128 / 8, 21, bitmap_item_sel_outline);

        // draw previous item as icon + label
        u8g.setFont(u8g_font_profont12);
        u8g.drawStr(10, 15, menu_lfr[item_sel_previous]);

        // draw selected item as icon + label in bold font
        u8g.setFont(u8g_font_7x14B);
        u8g.drawStr(10, 15 + 20 + 2, menu_lfr[item_selected]);

        // draw next item as icon + label
        u8g.setFont(u8g_font_profont12);
        u8g.drawStr(10, 15 + 20 + 20 + 2 + 2, menu_lfr[item_sel_next]);

        // draw scrollbar background
        u8g.drawBitmapP(128 - 8, 0, 8 / 8, 64, bitmap_scrollbar_background);
        // draw scrollbar handle
        u8g.drawBox(125, 64 / NUM_ITEMS_lfr * item_selected, 3, 64 / NUM_ITEMS_lfr);
      }

    } while (u8g.nextPage());  // required for page drawing mode with u8g library
    if (digitalRead(DEMO_PIN) == LOW) {
      current_screen = 0;
      loop();
    }
  }
}


void Sensor_Test_lfr() {
  delay(500);
  while (1) {
    for (int i = 0; i < numSensors; i++) {
      int sensorValue = analogRead(sensorPins[i]);
      s_dis[i] = (sensorValue > threshold) ? "0" : "1";
    }

    //Sensor Position--2,4,6,8,14,16,1,3,5,7,13,15,9,11

    u8g.setFont(u8g_font_profont10);  // Set the font
    u8g.firstPage();
    do {
      u8g.setPrintPos(12, 50);
      u8g.print(s_dis[0]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(20, 40);
      u8g.print(s_dis[1]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(28, 30);
      u8g.print(s_dis[2]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(36, 20);
      u8g.print(s_dis[3]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(44, 20);
      u8g.print(s_dis[4]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(52, 10);
      u8g.print(s_dis[5]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(60, 10);
      u8g.print(s_dis[6]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(68, 10);
      u8g.print(s_dis[7]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(76, 10);
      u8g.print(s_dis[8]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(84, 20);
      u8g.print(s_dis[9]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(92, 20);
      u8g.print(s_dis[10]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(100, 30);
      u8g.print(s_dis[11]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(108, 40);
      u8g.print(s_dis[12]);  // Print the sensor value at coordinates (90, 40)
      u8g.setPrintPos(116, 50);
      u8g.print(s_dis[13]);  // Print the sensor value at coordinates (90, 40)

    } while (u8g.nextPage());
    if (digitalRead(DEMO_PIN) == LOW) {
      current_screen = 0;
      Lfr();
    }
  }
}


void RUN_lfr() {
  u8g.setFont(u8g_font_profont10);  // Set the font
  u8g.firstPage();
  do {
    u8g.drawStr(5, 10, "Finding The Position");  // Print the text at coordinates (10, 20)
  } while (u8g.nextPage());

  delay(500);
  while (1) {
    pid_lfr();

    // this is for break the loop
    if (digitalRead(DEMO_PIN) == LOW) {
      motor(0, 0);
      current_screen = 0;
      Lfr();
    }
  }
}
