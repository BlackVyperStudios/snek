#pragma once
#include <cpp-terminal/terminal.h>

namespace menu {
class menu {
   private:
    // indicates the current state of the menu cursor (y = 8 + cursorState)
    unsigned short int cursorState = 0;
    // saves the state of the menu cursor from the menu before (y = 8 +
    // cursorState)
    unsigned short int lastCursorState = 0;
    // cursor parsing
    enum cursor { notMoved, up, down };

    // checks if you are in a sub menu
    bool sub = false;
    // toggles for the license sub menu
    bool license_sub_open = false;
    bool license_page_toggle = true;
    // if false, no selection arrow
    bool arrow = true;

   public:
    menu() = default;

    // start the menu
    unsigned short int start(Term::Terminal* term);

    // sub menu system
    void subMenu();

    // base menu
    void updateCursor(cursor cursorDir);
    void updateDescription() const;

    virtual ~menu() = default;
};
}  // namespace menu
