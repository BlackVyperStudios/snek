#include <cpp-terminal/terminal.h>
#include <filesystem>
#include <fstream>
#include <menu/menu.hpp>
#include <menu/visual.hpp>
#include <snake/snake.hpp>

unsigned short int menu::menu::start(Term::Terminal* term) {
    // draw menu
    anim::snakeHeader();
    anim::snakeMenuBase();
    updateDescription();
    updateCursor(cursor::notMoved);

    // menu loop
    bool running = true;
    while (running) {
        switch (term->read_key()) {
            case 'w':
            case Term::Key::ARROW_UP:
                if (license_sub_open)
                    anim::license_menu_toggle(&license_page_toggle);
                else if (cursorState > 0) {
                    updateCursor(cursor::up);
                    updateDescription();
                }
                break;
            case 's':
            case Term::Key::ARROW_DOWN:
                if (license_sub_open)
                    anim::license_menu_toggle(&license_page_toggle);
                else if (!sub && cursorState <= 5) {
                    updateCursor(cursor::down);
                    updateDescription();
                }
                else if (sub && cursorState <= 3) {
                    updateCursor(cursor::down);
                    updateDescription();
                }
                break;
            case 'a':
            case 'd':
            case Term::Key::ARROW_LEFT:
            case Term::Key::ARROW_RIGHT:
                if (license_sub_open)
                    anim::license_menu_toggle(&license_page_toggle);
                break;
            case 'q':
                if (sub) {
                    sub = false;
                    license_sub_open = false;
                    arrow = true;
                    draw::clearMenu();
                    cursorState = lastCursorState;
                    draw::snakeMenuBase();
                    updateDescription();
                    updateCursor(cursor::notMoved);
                }
                else
                    running = false;
                break;
            case Term::Key::ESC:
                running = false;
                break;
            case Term::Key::ENTER:
                if (!sub)
                    subMenu();
                else if (arrow) {
                    sub = false;
                    draw::clearField();
                    snake::snake snakeObj(false);
                    switch (cursorState) {
                        case 0:  // SNEK
                            snakeObj.run(*term);
                            draw::snakeMenuBase();
                            updateDescription();
                            updateCursor(cursor::notMoved);
                            break;
                        case 1:  // Classic
                            snakeObj.run(*term);
                            draw::snakeMenuBase();
                            updateDescription();
                            updateCursor(cursor::notMoved);
                            break;
                        case 2:  // Infinite
                            snakeObj.run(*term);
                            draw::snakeMenuBase();
                            updateDescription();
                            updateCursor(cursor::notMoved);
                            break;
                        case 3:  // Chaos
                            snakeObj.run(*term);
                            draw::snakeMenuBase();
                            updateDescription();
                            updateCursor(cursor::notMoved);
                            break;
                        case 4:  // Creative
                            snakeObj.run(*term);
                            draw::snakeMenuBase();
                            updateDescription();
                            updateCursor(cursor::notMoved);
                            break;
                    }
                }
                break;
        }
    }
    return 0;
}
void menu::menu::subMenu() {
    sub = true;
    draw::clearMenu();

    switch (cursorState) {
        case 0:
            std::cout << Term::move_cursor(7, 8)
                      << Term::color24_fg(255, 255, 0) << "SINGLEPLAYER!";
            arrow = true;
            updateDescription();
            anim::snakeGamemodes();
            break;
        case 1:
            std::cout << Term::move_cursor(7, 9)
                      << Term::color24_fg(255, 255, 0) << "MULTIPLAYER";
            arrow = true;
            updateDescription();
            anim::snakeGamemodes();
            break;
        case 2:
            std::cout << Term::move_cursor(7, 9)
                      << Term::color24_fg(255, 255, 0) << "ONLINE MODE";
            arrow = true;
            updateDescription();
            anim::snakeGamemodes();
            break;
        case 3: {
            std::cout << Term::move_cursor(17, 7)
                      << Term::color24_fg(255, 64, 0) << "    Press Q";
            arrow = false;
            anim::snakeHighscores();
#if defined(__WIN32)
            // get the  current users home directory
            std::string path = getenv("%appdata%");
            // add the config foler
            path.append("/snek/");
            // create the directory
            // TODO: only create it when it does not exist
            // TODO: measure permissions
            // TODO: move to foxspace
            // TODO: test what happens if no home directory exists
            std::filesystem::create_directory(path);
            // make the path complete
            path.append("scores.txt");
#else
            // get the  current users home directory
            std::string path = getenv("HOME");
            // add the config foler
            path.append("/.config/snek/");
            // create the directory
            // TODO: only create it when it does not exist
            // TODO: measure permissions
            // TODO: move to foxspace
            // TODO: test what happens if no home directory exists
            std::filesystem::create_directory(path);
            // make the path complete
            path.append("scores");
#endif
            unsigned short int highscores[6]{0};
            std::ifstream scores;
            std::string line;
            scores.open(path);
            if (scores.is_open()) {
                for (short int i = 0; i <= 5; i++) {
                    std::getline(scores, line);
                    highscores[i] = std::stoi(line);
                }
            }
            for (short int i = 0; i <= 5; i++) {
                std::cout << Term::move_cursor(10 + i, 6) << highscores[i];
            }
            break;
        }
        case 4:
            std::cout << Term::move_cursor(17, 7)
                      << Term::color24_fg(255, 64, 0) << "    Press Q";
            arrow = false;
            anim::snakeSettings();
            break;
        case 5:
            std::cout << Term::move_cursor(17, 7)
                      << Term::color24_fg(255, 64, 0) << "    Press Q";
            arrow = false;
            anim::snakeAbout();
            break;
        case 6:
            anim::snakeLicense();
            arrow = false;
            license_sub_open = true;
            license_page_toggle = true;
            anim::license_menu_toggle(&license_page_toggle);
            break;
    }
    lastCursorState = cursorState;
    cursorState = 0;
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
    if (arrow) {
        std::cout << Term::color(Term::bg::reset)
                  << Term::color(Term::fg::reset) << Term::move_cursor(17, 7)
                  << "               " << Term::color24_fg(255, 64, 0)
                  << Term::move_cursor(17, 7);
        if (!sub) {
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
        else if (arrow) {
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

menu::menu::menu() {
#if defined(__WIN32)
    // get the  current users home directory
    std::string path = getenv("%appdata%");
    // add the config foler
    path.append("/snek/");
    // create the directory
    // TODO: only create it when it does not exist
    // TODO: measure permissions
    // TODO: move to foxspace
    // TODO: test what happens if no home directory exists
    std::filesystem::create_directory(path);
    // make the path complete
    path.append("scores.txt");
#else
    // get the  current users home directory
    std::string path = getenv("HOME");
    // add the config foler
    path.append("/.config/snek/");
    // create the directory
    // TODO: only create it when it does not exist
    // TODO: measure permissions
    // TODO: move to foxspace
    // TODO: test what happens if no home directory exists
    std::filesystem::create_directory(path);
    // make the path complete
    path.append("scores");
#endif
    if (!std::filesystem::exists(path)) {
        std::ofstream outputFile(path, std::ios::trunc);
        for (short int i = 0; i <= 5; i++) {
            outputFile << "0" << std::endl;
        }
    }
}
