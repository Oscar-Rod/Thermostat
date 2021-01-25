void loop(void) {
  readMenuButton();
  refreshScreen();
  getClocModuleTime();
  if (menu == 0){
    controlBoiler();
    printTime();
  } else if (menu == 1) {
    setTimeControl();
  } else if (menu == 2) {
    setTimeControl();
  } else if (menu == 3) {
    setTime();
  }
}

void readMenuButton() {
  if (digitalRead(MENU_BUTTON) == LOW) {
    menu++;
    if (menu >= 4) {
      menu = 0;
    }
    delay(200);
  }
}
