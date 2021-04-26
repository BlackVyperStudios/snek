#include "snake.hpp"
#include <iostream>
#include <cpp-terminal/terminal.h>
#include <snake/info.hpp>

snake::snake::snake(bool testing)
{
    if (testing)
        drawField();
    
    drawDisplay();

    while (true);
}

void snake::snake::drawDisplay()
{
    std::cout << Term::color24_bg(153,0,76)
              << Term::color24_fg(255,255,255)
              << Term::move_cursor(6,2)
              << " Score    0 | Time 00:00 "
              << Term::move_cursor(18,2)
              << " " << SNAKE_VERSION_STRING << " |       | by BVS "
              << std::flush;
}











/* stuff */

void snake::snake::drawField() {
    std::cout << Term::color(Term::bg::reset) << Term::color24_fg(32, 255, 144)
              << Term::move_cursor(1, 1) << " .----." << Term::move_cursor(2, 1)
              << "{ {__  " << Term::move_cursor(3, 1) << ".-._} }"
              << Term::move_cursor(4, 1) << "`----' " << std::flush;

    std::cout << Term::move_cursor(1, 8) << ".-. .-." << Term::move_cursor(2, 8)
              << "|  `| |" << Term::move_cursor(3, 8) << "| |\\  |"
              << Term::move_cursor(4, 8) << "`-' `-'" << std::flush;

    std::cout << Term::move_cursor(1, 15) << ".----."
              << Term::move_cursor(2, 15) << "| {_  "
              << Term::move_cursor(3, 15) << "| {__ "
              << Term::move_cursor(4, 15) << "`----'" << std::flush;

    std::cout << Term::move_cursor(1, 21) << ".-. .-."
              << Term::move_cursor(2, 21) << "| |/ / "
              << Term::move_cursor(3, 21) << "| |\\ \\ "
              << Term::move_cursor(4, 21) << "`-' `-'" << std::flush
              << Term::color(Term::fg::reset) << Term::color(Term::bg::reset);

    std::cout << Term::color24_bg(32, 144, 255) << Term::color24_fg(0, 0, 0)
              << Term::move_cursor(5, 14) << ' ' << std::flush;

    // draws the top line
    for (unsigned int i = 1; i < 14; i++) {
        std::cout << Term::move_cursor(5, 14 - i) << ' '
                  << Term::move_cursor(5, 14 + i) << ' ' << std::flush;
    }
    // left and right rows
    for (unsigned int i = 0; i < 14; i++) {
        std::cout << Term::move_cursor(5 + i, 1) << ' '
                  << Term::move_cursor(5 + i, 27) << ' ' << std::flush;
    }
    // bottom row
    for (unsigned int i = 0; i < 14; i++) {
        std::cout << Term::move_cursor(19, 1 + i) << ' '
                  << Term::move_cursor(19, 27 - i) << ' ' << std::flush;
    }
    std::cout << Term::color24_fg(80, 200, 120) << Term::color(Term::bg::reset)
              << std::flush;
}