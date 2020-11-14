#include "utils.hpp"
#include <chrono>
#include <random>
#if defined(_WIN32)
#include <ncurses/ncurses.h>
#elif (__linux__)
#include <ncurses.h>
#endif

unsigned int utils::getTimestamp()
{
    return std::chrono::time_point_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now()).time_since_epoch().count();
}
unsigned short int utils::randomNum(const unsigned short int *maxNum)
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);
    return generator() % *maxNum; // lowers the number to the specified range
}
utils::timer::timer(unsigned short int millisecondsToWait)
{
    startTime = getTimestamp();
    timeToWait = millisecondsToWait;
}
bool utils::timer::done() const
{
    unsigned int timeTaken = getTimestamp() - startTime;
    return timeTaken / 1000 > timeToWait;
}
void utils::timer::reset()
{
    startTime = getTimestamp();
}
void utils::initNcurses()
{
    initscr();
    cbreak();
    noecho();
    raw();
    nodelay(stdscr, true);
    scrollok(stdscr, true);
    curs_set(0);
    keypad(stdscr,true);
}
void utils::initColorMode()
{
    if (has_colors())
    {
        start_color();
        init_pair(blueBackground, COLOR_BLUE, COLOR_BLUE);
        init_pair(greenText, COLOR_GREEN, COLOR_BLACK);
        init_pair(redText, COLOR_RED, COLOR_BLACK);
        init_pair(whiteText, COLOR_WHITE, COLOR_BLACK);
        init_pair(magentaText, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(yellowText, COLOR_YELLOW, COLOR_BLACK);
        init_pair(cyanText, COLOR_CYAN, COLOR_BLACK);
    }
}
