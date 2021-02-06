namespace anim
{
    // animates the snek header
    void snekHeader();
    // animates the main menu
    void snekMenuBase();
    // animates the change from the main to the sub menu
    void switchSubMenu();
    // singleplayer sub menu
    void snekSingle();
    // multiplayer sub menu
    void snekMulti();
    // online mode sub menu
    void snekOnline();
    // highscores sub menu
    void snekHighscores();
    // settings sub menu
    void snekSettings();
    // about sub menu
    void snekAbout();
    // license sub menu
    void snekLicense();
    // animates the change from the sub to main menu
    void switchMainMenu();
}
namespace draw
{
    void snekMenuBase();
    void clearField();
    void dummyField();
}