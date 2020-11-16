#pragma once

namespace menu
{
    class menu
    {
    private:
        unsigned short int cursorState = 1;
        // indicates if the easter egg is unlocked
        bool eU = false;
    public:
        menu() = default;

        unsigned short int start();

        // base menu
        void updateCursor(unsigned short int);
        void updateDesc() const;

        // menu entries

        // dummy entry
        void dummyEntry();

        virtual ~menu() = default;
    };
}
