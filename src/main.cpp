// snake
// TODO add proper header for source files and header with copyright notice
// TODO move from ncurses to low-level system libraries (windows.h and unistd.h)
#include <iostream>
#include "snake.h"

int main()
{
    snake::snake snek;

    unsigned short int quit;
    // game loop
    while (true)
    {
        quit = snek.update();
        if (quit != 0)
            break;
    }
    if (quit == 1)
        std::cout << "Game aborted...\n";
    else if (quit == 2)
        std::cout << "Game Over!\n";
    return 0;
}
