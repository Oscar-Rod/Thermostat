void refreshScreen() {
  if (previousScreen != menu) {
    lcd.clear();
    previousScreen = menu;
    if (menu == 3) setTemporalTime();
  }
}
