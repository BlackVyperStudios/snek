namespace anim {
// animates the snek header
void snakeHeader();
// animates the main menu
void snakeMenuBase();
// animates the change from the main to the sub menu
void switchSubMenu();
// sub menu for selecting gamemodes
void snakeGamemodes();
// highscores sub menu
void snakeHighscores();
// settings sub menu
void snakeSettings();
// about sub menu
void snakeAbout();
// license sub menu
// prints the menu title
void snakeLicense();
// toggles between the first and seconds License menu page
void license_menu_toggle(bool*);
// animates the change from the sub to main menu
void switchMainMenu();
}  // namespace anim
namespace draw {
void snakeMenuBase();
void clearMenu();
void clearField();
void dummyField();
}  // namespace draw
