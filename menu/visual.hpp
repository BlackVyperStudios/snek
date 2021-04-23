namespace anim {
// animates the snek header
void snekHeader();
// animates the main menu
void snekMenuBase();
// animates the change from the main to the sub menu
void switchSubMenu();
// sub menu for selecting gamemodes
void snekGamemodes();
// highscores sub menu
void snekHighscores();
// settings sub menu
void snekSettings();
// about sub menu
void snekAbout();
// license sub menu
// prints the menu title
void snekLicense();
// toggles between the first and seconds License menu page
void license_menu_toggle(bool*);
// animates the change from the sub to main menu
void switchMainMenu();
}  // namespace anim
namespace draw {
void snekMenuBase();
void clearMenu();
void clearField();
void dummyField();
}  // namespace draw
