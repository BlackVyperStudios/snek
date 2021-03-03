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
    updateDesc();
    updateCursor(cursor::notMoved);

    // menu loop
    bool running = true;
    while (running) {
        switch (term->read_key()) {
            case 'w':
            case Term::Key::ARROW_UP:
                if (cursorState > 1) {
                    updateCursor(cursor::up);
                    updateDesc();
                }
                break;
            case 's':
            case Term::Key::ARROW_DOWN:
                if (cursorState <= 7) {
                    updateCursor(cursor::down);
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
    return 0;
}
void menu::menu::updateCursor(cursor cursorDir) {
    if (cursorDir != cursor::notMoved) {
        std::cout << Term::color(Term::fg::reset)
                  << Term::color(Term::bg::reset)
                  << Term::move_cursor(7 + cursorState, 20) << "   ";
    }
    if (cursorDir == cursor::up)
        cursorState--;
    else if (cursorDir == cursor::down)
        cursorState++;
    std::cout << Term::color(Term::fg::red)
              << Term::move_cursor(7 + cursorState, 20) << "<--"
              << Term::color(Term::fg::reset) << std::flush;
}
void menu::menu::updateDesc() const {
    std::cout << Term::color(Term::bg::reset) << Term::color(Term::fg::reset)
              << Term::move_cursor(17, 7) << "               "
              << Term::color(Term::fg::red) << Term::move_cursor(17, 7);
    switch (cursorState) {
        case 1:
            std::cout << "  Play alone!";
            break;
        case 2:
            std::cout << " Play together";
            break;
        case 3:
            std::cout << "  Play online";
            break;
        case 4:
            std::cout << "Secret options!";
            break;
        case 5:
            std::cout << "How do I play??";
            break;
        case 6:
            std::cout << "Who did this???";
            break;
        case 7:
            std::cout << "  What's MIT?";
            break;
        case 8:
            std::cout << " Coming  soon!";
            break;
    }
    std::cout << Term::color(Term::fg::reset) << std::flush;
}
