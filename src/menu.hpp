#pragma once

namespace menu
{
    class menu
    {
    private:
        // indicates the current state of the menu cursor (y = 8 + cursorState)
        unsigned short int cursorState = 0;
    public:
        menu() = default;

        // start the menu
        unsigned short int start(Term::Terminal *term);
        
        // for sub menus
        void subMenu();
        // checks if you are in a sub menu
        bool sub = false;

        short int lastCursorState = 1;

        // if false, no selection arrow
        bool arrow = true;

        // base menu
        void updateCursor(unsigned short int);
        void updateDesc() const;

        virtual ~menu() = default;
    };
}
