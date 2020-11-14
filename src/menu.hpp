#pragma once

namespace menu
{
    class menu
    {
    private:
        unsigned int cursorState = 1;
        // indicates if the easter egg is unlocked
        bool eU = false;
    public:
        menu() = default;

        unsigned short int start();

        void updateCursor(bool);
        void updateDesc();

        virtual ~menu() = default;
    };
}
