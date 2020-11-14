/*  =====================================
 *  Debug interface for SNEK
 *  Created by MCWertGaming
 *  Licensed under MIT on GitHub
 *  https://github.com/MCWertGaming/snek
 * ===================================== */
#include "snake.hpp"

int main()
{
    snake::snake snek(true, false, 15, 10);
    unsigned short int quit = 0;
    while (quit == 0)
    {
        quit = snek.update();
    }
    return 0;
}