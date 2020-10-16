/*  =====================================
 *  Release interface for SNEK
 *  Created by MCWertGaming
 *  Licensed under MIT on GitHub
 *  https://github.com/MCWertGaming/snek
 * ===================================== */
#include "snake.hpp"

int main()
{
    snake::snake snek(true, true, 20, 20);

    unsigned short int quit = 0;
    while (quit == 0)
    {
        quit = snek.update();
    }
    return 0;
}