#include "menu.hpp"
#include <cpp-terminal/terminal.h>
#include "visual.hpp"

/*
 *  .----..-. .-..----..-. .-.
 * { {__  |  `| || {_  | |/ /
 * .-._} }| |\  || {__ | |\ \
 * `----' `-' `-'`----'`-' `-'
 * ###########################
 * #                         #
 * #    Oooooooooooooooo     #
 * #    Singleplayer <--     #
 * #    Multiplayer  <--     #
 * #    Online Mode  <--     #
 * #    Settings     <--     #
 * #    Manual       <--     #
 * #    About        <--     #
 * #    License      <--     #
 * #    ???          <--     #
 * #    oooooooooooooooO     #
 * #    >              <     #
 * #                         #
 * ###########################
 *
 * size: 15x27
 * inner size: 13x25
 *
 */

unsigned short int menu::menu::start(Term::Terminal* term) {
    // draw menu
    anim::snekHeader();
    anim::snekMenuBase();
    updateDescription();
    updateCursor(cursor::notMoved);

    // menu loop
    bool running = true;
    while (running) {
        switch (term->read_key()) {
            case 'w':
            case Term::Key::ARROW_UP:
                if (cursorState > 0) {
                    updateCursor(cursor::up);
                    updateDescription();
                }
                break;
            case 's':
            case Term::Key::ARROW_DOWN:
                if (!sub && cursorState <= 5) {
                    updateCursor(cursor::down);
                    updateDescription();
                }
                else if (sub && cursorState <= 3) {
                    updateCursor(cursor::down);
                    updateDescription();
                }
                break;
            case 'q':
                if (sub) {
                    sub = false;
                    arrow = true;
                    draw::clearMenu();
                    cursorState = lastCursorState;
                    draw::snekMenuBase();
                    updateDescription();
                    updateCursor(cursor::notMoved);
                } else
                    running = false;
                break;
            case Term::Key::ESC:
                running = false;
                [[fallthrough]];
            case Term::Key::ENTER:
                if (!sub)
                    subMenu();
                else if (arrow)
                {
                    switch (cursorState) {
                        case 0:
                            draw::clearField();
                            break;
                        case 1:
                            draw::clearField();
                            break;
                        case 2:
                            draw::clearField();
                            break;
                        case 3:
                            draw::clearField();
                            break;
                        case 4:
                            draw::clearField();
                            break;
                    }
                }
                break;
        }
    }
    return 0;
}

// sub menu system
void menu::menu::subMenu() {
    sub = true;
    lastCursorState = cursorState;
    draw::clearMenu();
    arrow = false;
    cursorState = 0;
    updateCursor(cursor::notMoved);

    switch (lastCursorState) {
        case 0:
            std::cout << Term::move_cursor(7, 8)
                      << Term::color24_fg(255, 255, 0) << "SINGLEPLAYER!";
            arrow = true;
            updateDescription();
            anim::snekGamemodes();
            break;
        case 1:
            std::cout << Term::move_cursor(7, 9)
                      << Term::color24_fg(255, 255, 0) << "MULTIPLAYER";
            arrow = true;
            updateDescription();
            anim::snekGamemodes();
            break;
        case 2:
            std::cout << Term::move_cursor(7, 9)
                      << Term::color24_fg(255, 255, 0) << "ONLINE MODE";
            arrow = true;
            updateDescription();
            anim::snekGamemodes();
            break;
        case 3:
            std::cout << Term::move_cursor(17, 7) << Term::color24_fg(255, 64, 0)
                      << "    Press Q";
            anim::snekHighscores();
            break;
        case 4:
            std::cout << Term::move_cursor(17, 7) << Term::color24_fg(255, 64, 0)
                      << "    Press Q";
            anim::snekSettings();
            break;
        case 5:
            std::cout << Term::move_cursor(17, 7) << Term::color24_fg(255, 64, 0)
                      << "    Press Q";
            anim::snekAbout();
            break;
        case 6:
            std::cout << Term::move_cursor(17, 7) << Term::color24_fg(255, 64, 0)
                      << "    Press Q";
            anim::snekLicense();
            break;
    }
    std::cout << Term::color(Term::fg::reset) << std::flush;
}

void menu::menu::updateCursor(cursor cursorDir) {
    if (!arrow) {
        std::cout << Term::color(Term::fg::reset)
                  << Term::color(Term::bg::reset)
                  << Term::move_cursor(9 + cursorState, 20) << "   ";
    }
    else {
        if (cursorDir != cursor::notMoved) {
            std::cout << Term::color(Term::fg::reset)
                      << Term::color(Term::bg::reset)
                      << Term::move_cursor(9 + cursorState, 20) << "   ";
            if (cursorDir == cursor::up)
                cursorState--;
            else if (cursorDir == cursor::down)
                cursorState++;
        }
        std::cout << Term::color24_fg(255, 64, 0)
                  << Term::move_cursor(9 + cursorState, 20) << "<--"
                  << Term::color(Term::fg::reset) << std::flush;
    }
}
void menu::menu::updateDescription() const {
    if (arrow)
    {
        std::cout << Term::color(Term::bg::reset) << Term::color(Term::fg::reset)
                  << Term::move_cursor(17, 7) << "               "
                  << Term::color24_fg(255, 64, 0) << Term::move_cursor(17, 7);
        if (!sub)
        {
            switch (cursorState) {
                case 0:
                    std::cout << "  Play alone!";
                    break;
                case 1:
                    std::cout << " Play together";
                    break;
                case 2:
                    std::cout << "  Play online";
                    break;
                case 3:
                    std::cout << "Your best runs!";
                    break;
                case 4:
                    std::cout << "Secret options!";
                    break;
                case 5:
                    std::cout << " Who did this?";
                    break;
                case 6:
                    std::cout << "  What's MIT?";
                    break;
            }
        }
        else if (arrow)
        {
            switch (cursorState) {
                case 0:
                    std::cout << "With power-ups!";
                    break;
                case 1:
                    std::cout << " Classic Snake";
                    break;
                case 2:
                    std::cout << "   No walls!";
                    break;
                case 3:
                    std::cout << "MANY item drops";
                    break;
                case 4:
                    std::cout << "Build your snek";
                    break;
            }
        }
        std::cout << Term::color(Term::fg::reset) << std::flush;
    }
}
