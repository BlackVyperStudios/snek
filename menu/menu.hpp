#pragma once
#include <cpp-terminal/terminal.h>

namespace menu {
class menu {
   private:
    // indicates the current state of the menu cursor (y = 7 + cursorState)
    unsigned short int cursorState = 1;
    // cursor parsing
    enum cursor { notMoved, up, down };

   public:
    menu() = default;

    // start the menu
    unsigned short int start(Term::Terminal*term);

    // base menu
    void updateCursor(cursor cursorDir);
    void updateDesc() const;

    virtual ~menu() = default;
};
}  // namespace menu
