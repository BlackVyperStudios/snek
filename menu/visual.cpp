#include "visual.hpp"
#include <cpp-terminal/terminal.h>
#include <chrono>
#include <thread>
#include <snake/info.hpp>

void anim::snakeMenuBase() {
    std::cout << Term::color24_bg(32, 144, 255) << Term::color24_fg(0, 0, 0)
              << Term::move_cursor(5, 14) << ' ' << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(70));

    // draws the top line
    for (unsigned int i = 1; i < 14; i++) {
        std::cout << Term::move_cursor(5, 14 - i) << ' '
                  << Term::move_cursor(5, 14 + i) << ' ' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
    // left and right rows
    for (unsigned int i = 0; i < 14; i++) {
        std::cout << Term::move_cursor(5 + i, 1) << ' '
                  << Term::move_cursor(5 + i, 27) << ' ' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
    // bottom row
    for (unsigned int i = 0; i < 14; i++) {
        std::cout << Term::move_cursor(19, 1 + i) << ' '
                  << Term::move_cursor(19, 27 - i) << ' ' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
    std::cout << Term::color24_fg(80, 200, 120) << Term::color(Term::bg::reset)
              << std::flush;
    for (unsigned short int i = 0; i < 21; i++) {
        // draw head
        std::cout << Term::move_cursor(8, 26 - i) << 'O'
                  << Term::move_cursor(16, 2 + i) << 'O';
        // draw tail
        if (i > 0)
            std::cout << Term::move_cursor(8, 27 - i) << 'o'
                      << Term::move_cursor(16, 1 + i) << 'o';
        // erase tail
        if (i > 16)
            std::cout << Term::move_cursor(8, 27 - (i - 16)) << ' '
                      << Term::move_cursor(16, 1 + (i - 16)) << ' ';
        // flush iostream
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
    std::cout << Term::move_cursor(7, 10) << Term::color24_fg(255, 255, 0)
              << "MAIN MENU" << Term::color24_fg(21, 96, 189)
              << Term::move_cursor(9, 6) << "Singleplayer"
              << Term::move_cursor(10, 6) << "Multiplayer"
              << Term::move_cursor(11, 6) << "Online Mode"
              << Term::move_cursor(12, 6) << "Highscores"
              << Term::move_cursor(13, 6) << "Settings"
              << Term::move_cursor(14, 6) << "About" << Term::move_cursor(15, 6)
              << "License" << Term::move_cursor(17, 6) << ">               <"
              << Term::move_cursor(9, 20) << Term::color24_fg(255, 64, 0)
              << "<--" << Term::color(Term::fg::reset) << std::flush;
}
void anim::snakeHeader() {
    std::cout << Term::color(Term::bg::reset) << Term::color24_fg(32, 255, 144)
              << Term::move_cursor(1, 1) << " .----." << Term::move_cursor(2, 1)
              << "{ {__  " << Term::move_cursor(3, 1) << ".-._} }"
              << Term::move_cursor(4, 1) << "`----' " << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(70));
    std::cout << Term::move_cursor(1, 8) << ".-. .-." << Term::move_cursor(2, 8)
              << "|  `| |" << Term::move_cursor(3, 8) << "| |\\  |"
              << Term::move_cursor(4, 8) << "`-' `-'" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(70));
    std::cout << Term::move_cursor(1, 15) << ".----."
              << Term::move_cursor(2, 15) << "| {_  "
              << Term::move_cursor(3, 15) << "| {__ "
              << Term::move_cursor(4, 15) << "`----'" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(70));
    std::cout << Term::move_cursor(1, 21) << ".-. .-."
              << Term::move_cursor(2, 21) << "| |/ / "
              << Term::move_cursor(3, 21) << "| |\\ \\ "
              << Term::move_cursor(4, 21) << "`-' `-'" << std::flush
              << Term::color(Term::fg::reset) << Term::color(Term::bg::reset);
}
void anim::snakeGamemodes() {
    std::cout << Term::move_cursor(9, 6) << Term::color24_fg(36, 115, 201)
              << "SNEK" << Term::move_cursor(10, 6) << "Classic"
              << Term::move_cursor(11, 6) << "Infinite"
              << Term::move_cursor(12, 6) << "Chaos" << Term::move_cursor(13, 6)
              << "Creative" << Term::move_cursor(15, 7)
              << Term::color24_fg(226, 61, 40) << "Select Gamemode"
              << Term::move_cursor(9, 20) << Term::color24_fg(255, 64, 0)
              << "<--" << Term::color(Term::fg::reset) << std::flush;
}
void anim::snakeSettings() {
    std::cout << Term::move_cursor(7, 10) << Term::color24_fg(255, 255, 0)
              << "SETTINGS!" << Term::color(Term::fg::reset) << std::flush;
}
void anim::snakeHighscores() {
    std::cout << Term::move_cursor(7, 9) << Term::color24_fg(255, 255, 0)
              << "HIGHSCORES!" << Term::move_cursor(9, 4)
              << Term::color24_fg(0, 0, 0) << Term::color24_bg(204, 204, 204)
              << "SINGLE" << Term::move_cursor(9, 12)
              << Term::color24_fg(51, 51, 51) << Term::color(Term::bg::reset)
              << "MULTI" << Term::move_cursor(9, 19)
              << "ONLINE"
              << Term::color(Term::fg::reset) << std::flush;
}
void anim::snakeAbout() {
    std::cout << Term::move_cursor(7, 12) << Term::color24_fg(255, 255, 0)
              << "ABOUT" << Term::move_cursor(9, 12)
              << Term::color24_fg(51, 51, 51) << "~ ~ ~"
              << Term::move_cursor(10, 6) << Term::color24_fg(255, 64, 0)
              << "SNEK " << SNAKE_VERSION_STRING
              << Term::color24_fg(36, 115, 201) << " is a"
              << Term::move_cursor(11, 6) << "game developed by"
              << Term::move_cursor(12, 6) << Term::color24_fg(255, 64, 0)
              << "BlackVyperStudios" << Term::move_cursor(13, 6)
              << Term::color24_fg(36, 115, 201) << "and all contribu-"
              << Term::move_cursor(14, 7) << "tors on GitHub!"
              << Term::move_cursor(15, 12) << Term::color24_fg(51, 51, 51)
              << "~ ~ ~" << Term::color(Term::fg::reset) << std::flush;
}
void anim::snakeLicense() {
    std::cout << Term::move_cursor(7, 11) << Term::color24_fg(255, 255, 0)
              << "LICENSE" << Term::color24_fg(36, 115, 201)
              << Term::color(Term::fg::reset) << std::flush;
}
void anim::license_menu_toggle(bool* toggle)
{
    if (*toggle)
    {
        std::cout << Term::color24_fg(36, 115, 201)
                  << Term::move_cursor(9,6) << "SNEK is licensed"
                  << Term::move_cursor(10,6) << "under MIT on "
                  << Term::color24_fg(255, 64, 0)
                  << Term::move_cursor(11,6) << "http://github.com"
                  << Term::move_cursor(12,6) << "Copyright 2020:"
                  << Term::color24_fg(36, 115, 201)
                  << Term::move_cursor(13,6) << "Damon Leven     "
                  << Term::color24_fg(255, 64, 0)
                  << Term::move_cursor(14,6) << "Copyright 2021:"
                  << Term::color24_fg(36, 115, 201)
                  << Term::move_cursor(15,6) << "BlackVyperStudios"
                  << Term::move_cursor(17, 7) << Term::color24_fg(255, 64, 0)
                  << "  [Page  1/2]"
                  << std::flush;
        *toggle = false;
    }
    else
    {
        std::cout << Term::color24_fg(36, 115, 201)
                  << Term::move_cursor(9,6) << "SNEK is using   "
                  << Term::move_cursor(10,6) << "the following"
                  << Term::move_cursor(11,6) << "Dependencies:    "
                  << Term::color24_fg(255, 64, 0)
                  << Term::move_cursor(12,6) << "cpp-terminal   "
                  << Term::color24_fg(36, 115, 201)
                  << Term::move_cursor(13,6) << "by Ondřej Čertík"
                  << Term::color24_fg(255, 64, 0)
                  << Term::move_cursor(14,6) << "FOLF-namespace "
                  << Term::color24_fg(36, 115, 201)
                  << Term::move_cursor(15,6) << "by FOLF-projects "
                  << Term::move_cursor(17, 7) << Term::color24_fg(255, 64, 0)
                  << "  [Page  2/2]"
                  << std::flush;
        *toggle = true;
    }
}

void draw::snakeMenuBase() {
    std::cout << Term::move_cursor(7, 10) << Term::color24_fg(255, 255, 0)
              << "MAIN MENU" << Term::color24_fg(72, 191, 132)
              << Term::move_cursor(8, 6) << "Ooooooooooooooooo"
              << Term::color24_fg(36, 115, 201)
              << Term::move_cursor(9, 6) << "Singleplayer"
              << Term::move_cursor(10, 6) << "Multiplayer"
              << Term::move_cursor(11, 6) << "Online Mode"
              << Term::move_cursor(12, 6) << "Highscores"
              << Term::move_cursor(13, 6) << "Settings"
              << Term::move_cursor(14, 6) << "About"
              << Term::move_cursor(15, 6) << "License"
              << Term::move_cursor(17, 6) << ">               <"
              << Term::color24_fg(72, 191, 132) << Term::move_cursor(16, 6)
              << "ooooooooooooooooO"
              << Term::color(Term::fg::reset) << std::flush;
}
void draw::clearMenu() {
    std::cout << Term::color(Term::fg::reset) << Term::color(Term::bg::reset)
              << Term::move_cursor(7, 2) << "                         ";
    for (unsigned short int i = 0; i < 7; i++) {
        std::cout << Term::move_cursor(9 + i, 2) << "                         ";
    }
    std::cout << Term::color24_fg(36, 115, 201) << Term::move_cursor(17, 6)
              << ">               <"
              << std::flush;
}
void draw::clearField() {
    std::cout << Term::color(Term::fg::reset) << Term::color(Term::bg::reset);
    for (unsigned short int i = 0; i < 13; i++) {
        std::cout << Term::move_cursor(6 + i, 2) << "                         ";
    }
    std::cout << std::flush;
}
