#include <cpp-terminal/terminal.h>
#include "menu.hpp"
#include "visual.hpp"

// definitions for updating the cursor
#define notMovedCursor 0
#define moveCursorUp 1
#define moveCursorDown 2

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

unsigned short int menu::menu::start(Term::Terminal *term)
{
    // draw menu
    anim::snekHeader();
    anim::snekMenuBase();
    updateDesc();
    updateCursor(notMovedCursor);

    bool running = true;
    // menu loop
    while (running)
    {
        switch (term->read_key())
        {
            case 'w':
            case Term::Key::ARROW_UP:
                if (cursorState != 0)
                {
                    updateCursor(moveCursorUp);
                    updateDesc();
                }
                break;
            case 's':
            case Term::Key::ARROW_DOWN:
                if (!sub && cursorState != 6)
                {
                    updateCursor(moveCursorDown);
                    updateDesc();
                }
                else if (sub && cursorState != 4)
                {
                    updateCursor(moveCursorDown);
                    updateDesc();
                }
                break;
            case 'q':
                if (sub)
                {
                    sub = false;
                    arrow = true;
                    draw::clearField();
                    cursorState = lastCursorState;
                    draw::snekMenuBase();
                    updateDesc();
                    updateCursor(notMovedCursor);
                }
                else
                    running = false;
                break;
            case Term::Key::ESC:
                running = false;
            case Term::Key::ENTER:
                if (!sub)
                    subMenu();
                break;
        }
    }

    return 0;
}

// sub menu system
void menu::menu::subMenu()
{
    lastCursorState = cursorState;
    draw::clearField();
    arrow = false;
    updateCursor(notMovedCursor);
    sub = true;

    std::cout << Term::color(Term::fg::reset)
              << Term::move_cursor(17,7)
              << Term::color(Term::fg::red);
    switch (cursorState)
    {
        case 0:
            std::cout << "    Press Q";     // every "Press Q" is a placeholder except 6 and 7
            arrow = true;
            cursorState = 0;
            std::cout << Term::move_cursor(7,8)
                      << Term::color(Term::fg::yellow)
                      << "SINGLEPLAYER!";
            anim::snekGamemodes();
            break;
        case 1:
            std::cout << "    Press Q";
            arrow = true;
            cursorState = 0;
            std::cout << Term::move_cursor(7,9)
                      << Term::color(Term::fg::yellow)
                      << "MULTIPLAYER";
            anim::snekGamemodes();
            break;
        case 2:
            std::cout << "    Press Q";
            arrow = true;
            cursorState = 0;
            std::cout << Term::move_cursor(7,9)
                      << Term::color(Term::fg::yellow)
                      << "ONLINE MODE";
            anim::snekGamemodes();
            break;
        case 3:
            std::cout << "    Press Q";
            anim::snekHighscores();
            break;
        case 4:
            arrow = true;
            std::cout << "    Press Q";
            anim::snekSettings();
            break;
        case 5:
            std::cout << "    Press Q";
            anim::snekAbout();
            break;
        case 6:
            std::cout << "    Press Q";
            anim::snekLicense();
            break;
    }
}

void menu::menu::updateCursor(unsigned short int moving)
{
    if (!arrow)
    {
        std::cout << Term::color(Term::fg::reset)
                  << Term::color(Term::bg::reset)
                  << Term::move_cursor(8 + cursorState,20)
                  << "   ";
    }
    else
    {
        if (moving != notMovedCursor)
        {
            std::cout << Term::color(Term::fg::reset)
                      << Term::color(Term::bg::reset)
                      << Term::move_cursor(9 + cursorState,20)
                      << "   ";
        }
        if (moving == moveCursorUp)
            cursorState--;
        else if (moving == moveCursorDown)
            cursorState++;
        std::cout << Term::color(Term::fg::red)
                  << Term::move_cursor(9 + cursorState, 20)
                  << "<--"
                  << Term::color(Term::fg::reset)
                  << std::flush;
    }
}
void menu::menu::updateDesc() const
{
    if (!sub)
    {
        std::cout << Term::color(Term::bg::reset)
                  << Term::color(Term::fg::reset)
                  << Term::move_cursor(17,7)
                  << "               "
                  << Term::color(Term::fg::red)
                  << Term::move_cursor(17,7);
        switch (cursorState)
        {
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
                std::cout << "Who did this???";
                break;
            case 6:
                std::cout << "  What's MIT?";
                break;
        }
        std::cout << Term::color(Term::fg::reset)
                  << std::flush;
    }
}
