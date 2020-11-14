#include <cpp-terminal/terminal.h>
#include "menu.hpp"
#include "animation.hpp"
#include "utils.hpp"

/*
 * .----..-. .-..----..-. .-.
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

unsigned short int menu::menu::start()
{
    try
    {
        // prerequisites
        Term::Terminal term(true,false);
        term.save_screen();
        // turn off the cursor
        std::cout << Term::cursor_off();

        // draw menu
        anim::snekHeader();
        anim::snekMenuBase();
        updateDesc();

        bool running = true;
        // menu loop
        while (running)
        {
            switch (term.read_key())
            {
                case 'w':
                case Term::Key::ARROW_UP:
                    if (cursorState != 1)
                    {
                        updateCursor(true);
                        updateDesc();
                    }
                    break;
                case 's':
                case Term::Key::ARROW_DOWN:
                    if (cursorState != 7 && !eU || cursorState != 8 && eU)
                    {
                        updateCursor(false);
                        updateDesc();
                    }
                    break;
                case 'q':
                case Term::Key::ESC:
                    running = false;
                case Term::Key::ENTER:
                    // enter
                    break;
            }
        }

        // make sure the terminal is reverted to its original state
        std::cout << Term::color(Term::style::reset);
    }
    catch(const std::runtime_error& re)
    {
        std::cerr << "Runtime error: " << re.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error." << std::endl;
        return 2;
    }

    return 0;
}
void menu::menu::updateCursor(bool movingUp)
{
    std::cout << Term::color(Term::fg::reset)
              << Term::color(Term::bg::reset)
              << Term::move_cursor(7 + cursorState,20)
              << "   ";
    if (movingUp)
        cursorState--;
    else
        cursorState++;
    std::cout << Term::color(Term::fg::red)
              << Term::move_cursor(7 + cursorState, 20)
              << "<--"
              << Term::color(Term::fg::reset)
              << std::flush;
}
void menu::menu::updateDesc()
{
    std::cout << Term::color(Term::bg::reset)
              << Term::color(Term::fg::reset)
              << Term::move_cursor(17,7)
              << "               "
              << Term::color(Term::fg::red)
              << Term::move_cursor(17,7);
    switch (cursorState)
    {
        case 1:
            std::cout << "Play alone!";
            break;
        case 2:
            std::cout << "Play together!";
            break;
        case 3:
            std::cout << "Play online";
            break;
        case 4:
            std::cout << "Secret options!";
            break;
        case 5:
            std::cout << "How do I play?";
            break;
        case 6:
            std::cout << "Who did this???";
            break;
        case 7:
            std::cout << "What's MIT?";
            break;
        case 8:
            std::cout << "Coming soon!";
            break;
    }
    std::cout << Term::color(Term::fg::reset)
              << std::flush;
}
