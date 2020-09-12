#pragma once
#include <ncurses/ncurses.h>
#include <iostream>
#include "utils.h"

namespace snake
{
    class snake
    {
    private:
        unsigned short int screen[2]{30, 30};
        unsigned short int snakePos[2][100]{0};
        unsigned short int snakeLength = 1;
        unsigned short int apple[2]{0};
        unsigned short int score = 0;
        unsigned short int lastDir{};
        bool consoleSupportsColors{};

        /* pre-game */
        // static void initNcurses();
        void initColorMode();
        void setDefaultPos();
        /* drawing */
        void drawScore();
        void drawApple();
        void drawField();
        /* game-object creation */
        void createApple();
        /* checks */
        bool illegalPosition(unsigned short int, unsigned short int, bool);
        // TODO implement
        void appleEaten();
    public:
        // constructor initialises the complete game and ncurses
        explicit snake(bool);
        // updates the game state
        unsigned short int update();
        // destructor destroys game and ncurses
        virtual ~snake() = default;

        // TODO make private
        void drawSnake(bool);

        // TODO change shitty names
        void updateSnakePos(unsigned short int, unsigned short int);
        unsigned short int moveSnake();
    };
}
