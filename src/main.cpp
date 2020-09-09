// snake
// TODO move from ncurses to low-level system libraries (windows.h and unistd.h)
#include <ncurses/ncurses.h>
#include <iostream>

#include "snake.h"

/*
 * // TODO rework field like this
 * field:
 *
 * ############# SNEK
 * #           # by MCWertGaming
 * #           #
 * #           # Time: XX:XX // TODO implement time clock
 * #           # Score: XX
 * #           #
 * #           #
 * #############
 *
 */

// TODO move universal functions into a namespace
// TODO move logic into class // namespace
// TODO change qualified functions to inline functions


int main()
{
    snake::gameSetup();

    unsigned short int quit;

    // game loop
    while (true)
    {
        quit = snake::moveSnake();
        if (quit != 0)
            break;
        snake::drawSnake(false);
    }
    // destroys ncurses
    endwin();
    if (quit == 1)
        std::cout << "Game aborted...\n";
    else if (quit == 2)
        std::cout << "Game Over!\n";
    return 0;
}
