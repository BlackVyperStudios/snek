/*  =====================================
 *  Debug interface for SNEK
 *  Created by BlackVyperStudios
 *  Licensed under MIT on GitHub
 *  https://github.com/BlackVyperStudios/snek
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