// engine source

#include <sys/ioctl.h>
#include <zconf.h>
#include <iostream>
#include "engine.h"

unsigned int engine::consoleHight()
{
    struct winsize size{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_row;
}
unsigned int engine::consoleWidth()
{
    struct winsize size{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}
void engine::clearConsole()
{
    for (int i = 0; i < consoleHight(); ++i) {
        std::cout << "\n";
    }
}
