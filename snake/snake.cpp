#include "snake.hpp"
#include <cpp-terminal/terminal.h>
#include <folf/timeTools.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <snake/info.hpp>

// TODO: move to library
#include <random>
static unsigned long long randomNum(unsigned long long maxNum) {
    unsigned long long randomNumber;
    do {
        // make the generator ready
        std::mt19937_64 generator(snake::get_timepoint());
        randomNumber = generator() % (maxNum + 1);
    } while (randomNumber == 0);

    return randomNumber - 1;
}

snake::snake::snake(bool testing) {
    if (testing)
        drawField();
    prepareGame();
}

void snake::snake::prepareGame() {
    // draws the HUD
    drawDisplay();
    // set snake start:
    snakePos[0][0] = 12;
    snakePos[1][0] = 5;
    // dummy values for the first run after resume
    snakePos[0][1] = 0;
    snakePos[1][1] = 0;
    // reset values
    snakeLength = 1;
    score = 0;
    // draw snake
    drawSnake();
    createApple();
    drawApple();
    setSnakeSpeed();
    input = Input::none;
}

inline std::string snake::snake::move_cursor(unsigned short int& row,
                                             unsigned short int& column) {
    return Term::move_cursor(row + FieldPos::f_row,
                             column + FieldPos::f_column);
}

void snake::snake::drawDisplay() {
    std::cout << Term::color24_bg(153, 0, 76) << Term::color24_fg(255, 255, 255)
              << Term::move_cursor(6, 2) << " Score    0 | Time 00:00 "
              << Term::move_cursor(18, 2) << " " << SNAKE_VERSION_STRING
              << " |       | by BVS " << Term::color(Term::style::reset)
              << std::flush;
}
void snake::snake::drawSnake() {
    // tail gets erased before drawing the snake to avoid removing of the
    // snakeHead erase tail, but dont erase on first move due to last location
    // at 0,0
    if (snakePos[0][snakeLength] != 0 && snakePos[1][snakeLength] != 0)
        std::cout << move_cursor(snakePos[1][snakeLength],
                                 snakePos[0][snakeLength])
                  << ' ';

    // draw the snake head
    std::cout << Term::color(Term::fg::green)
              << move_cursor(snakePos[1][0], snakePos[0][0]) << 'O';

    // change the old snake head to snake body
    if (snakeLength > 1) {
        std::cout << move_cursor(snakePos[1][1], snakePos[0][1]) << 'o';
    }
    std::cout << std::flush;
}

void snake::snake::getInput(Term::Terminal& term) {
    Input inputCopy = input;
    timer timer(snakeSpeed);
    while (!timer.done() || input == Input::none) {
        switch (term.read_key0()) {
            case 'w':
            case Term::Key::ARROW_UP:
                if (snakeLength == 1 ||
                    inputCopy != Input::down)  // preventing the user from going
                                               // into the opposite direction
                    input = Input::up;
                break;
            case 's':
            case Term::Key::ARROW_DOWN:
                if (snakeLength == 1 || inputCopy != Input::up)
                    input = Input::down;
                break;
            case 'a':
            case Term::Key::ARROW_LEFT:
                if (snakeLength == 1 || inputCopy != Input::right)
                    input = Input::left;
                break;
            case 'd':
            case Term::Key::ARROW_RIGHT:
                if (snakeLength == 1 || inputCopy != Input::left)
                    input = Input::right;
                break;
            case Term::Key::ESC:
            case Term::Key::CTRL + 'c':
                input = Input::quit;
                return;
                break;
            case ' ':  // space for pause
                timer.pause();
                pauseMenu(term);
                if (input == Input::quit)
                    return;
                timer.resume();
                break;
            default:
                break;
        }
    }
}
void snake::snake::moveSnake() {
    switch (input) {
        case Input::quit:
            break;
        case Input::up:
            updateSnake(snakePos[0][0], snakePos[1][0] - 1);
            break;
        case Input::down:
            updateSnake(snakePos[0][0], snakePos[1][0] + 1);
            break;
        case Input::left:
            updateSnake(snakePos[0][0] - 1, snakePos[1][0]);
            break;
        case Input::right:
            updateSnake(snakePos[0][0] + 1, snakePos[1][0]);
            break;

        default:
            throw std::runtime_error("No input");
            break;
    }

    std::cout << std::flush;
}
void snake::snake::updateSnake(unsigned short int posX,
                               unsigned short int posY) {
    unsigned short int preLoc[2][2];

    preLoc[0][0] = snakePos[0][0];
    preLoc[0][1] = snakePos[1][0];

    snakePos[0][0] = posX;
    snakePos[1][0] = posY;

    for (unsigned short int i = 1; i < snakeLength + 1; i++) {
        preLoc[1][0] = snakePos[0][i];
        preLoc[1][1] = snakePos[1][i];

        snakePos[0][i] = preLoc[0][0];
        snakePos[1][i] = preLoc[0][1];

        preLoc[0][0] = preLoc[1][0];
        preLoc[0][1] = preLoc[1][1];
    }
}
unsigned short int snake::snake::check_game_state() {
    if (snakePos[0][0] == 0 || snakePos[1][0] == 0 ||
        snakePos[0][0] == screenSize::s_column ||
        snakePos[1][0] == screenSize::s_row ||
        isOnSnake(snakePos[0][0], snakePos[1][0]))
        return 1;  // TODO loose screen
    // TODO: check if snake collides with itself
    else if (input == Input::quit)
        return 2;  // quit
    else if (snakePos[0][0] == applePos[0] && snakePos[1][0] == applePos[1]) {
        createApple();
        score++;
        drawScore();
        snakeLength++;
        setSnakeSpeed();
    }
    return 0;
}
bool snake::snake::isOnSnake(unsigned short int& posX,
                             unsigned short int& PosY) {
    for (unsigned short int i = 1; i <= snakeLength - 1; i++) {
        if (snakePos[0][i] == posX && snakePos[1][i] == PosY)
            return true;
    }
    return false;
}
void snake::snake::drawScore() {
    std::cout << Term::color24_bg(153, 0, 76)
              << Term::color24_fg(255, 255, 255);
    if (score >= 1000)
        std::cout << Term::move_cursor(FieldPos::f_row, FieldPos::f_column + 8)
                  << score;
    else if (score >= 100)
        std::cout << Term::move_cursor(FieldPos::f_row, FieldPos::f_column + 8)
                  << ' ' << score;
    else if (score >= 10)
        std::cout << Term::move_cursor(FieldPos::f_row, FieldPos::f_column + 8)
                  << "  " << score;
    else
        std::cout << Term::move_cursor(FieldPos::f_row, FieldPos::f_column + 8)
                  << "   " << score;
    std::cout << Term::color(Term::fg::reset) << Term::color(Term::bg::reset)
              << std::flush;
}

void snake::snake::createApple() {
    do {
        applePos[0] = 1 + randomNum(screenSize::s_column - 2);
        applePos[1] = 1 + randomNum(screenSize::s_row - 2);
    } while (isOnSnake(applePos[0], applePos[1]) ||
             (snakePos[0][0] == applePos[0] && snakePos[1][0] == applePos[1]));
}

void snake::snake::drawApple() {
    std::cout << move_cursor(applePos[1], applePos[0])
              << Term::color(Term::fg::red) << 'O'
              << Term::color(Term::fg::reset) << std::flush;
}

unsigned short int snake::snake::run(Term::Terminal& term) {
    unsigned int game_state = 0;
    while (true)  // loose loop
    {
        while (true)  // actual game loop
        {
            getInput(term);
            moveSnake();
            game_state = check_game_state();
            if (game_state == 1)
                break;
            else if (game_state == 2) {
                clearFieldDisplay();
                return 1;
            }
            drawSnake();
            drawApple();
        }
        clearField();
        if (looseScreen(term)) {
            clearFieldDisplay();
            return 0;
        }
        clearField();
        prepareGame();
    }
    clearFieldDisplay();
    return 0;
}

void snake::snake::pauseMenu(Term::Terminal& term) {
    std::cout << Term::color24_bg(153, 0, 76) << Term::color24_fg(255, 255, 255)
              << Term::move_cursor(18, 12) << "PAUSE" << std::flush;
    while (true) {
        switch (term.read_key0()) {
            case ' ':
                std::cout << Term::move_cursor(18, 12) << "     "
                          << Term::color(Term::style::reset) << std::flush;
                return;
                break;
            case 'q':
            case Term::Key::ESC:
            case Term::Key::CTRL + 'c':
                input = Input::quit;
                std::cout << Term::move_cursor(18, 12) << "     "
                          << Term::color(Term::style::reset) << std::flush;
                return;
                break;
            default:
                break;
        }
    }
}

// TODO: make universal / variable
void snake::snake::setSnakeSpeed() {
    snakeSpeed =
        500 - (snakeLength * ((speed::max - speed::min) /
                              (screenSize::s_row * screenSize::s_column)));

    // // calculated using (maxSpeed - minSpeed) / (fieldX * fieldY)
    // const bool speedMultiplyer = 1.781;
    // // calculates maxSpeed - (snakeLength * speedMultiplyer)
    // snakeSpeed = 500 - (snakeLength * speedMultiplyer);
}

bool snake::snake::looseScreen(Term::Terminal& term) {
    std::cout << Term::move_cursor(9, 10) << Term::color(Term::fg::yellow)
              << "You Loose" << Term::move_cursor(10, 9)
              << Term::color(Term::fg::green) << "OoooooooooO"
              << Term::move_cursor(14, 7) << Term::color(Term::fg::red) << ">"
              << Term::color(Term::fg::blue) << "  Try again  "
              << Term::color(Term::fg::red) << "<" << Term::move_cursor(15, 9)
              << Term::color(Term::fg::blue) << "To the Menu"
              << Term::color(Term::style::reset) << std::flush;
    highscore();
    bool selection = true;
    while (true) {
        switch (term.read_key()) {
            case 'w':
            case Term::Key::ARROW_UP:
                std::cout << Term::move_cursor(14, 7)
                          << Term::color(Term::fg::red) << ">"
                          << Term::color(Term::fg::blue) << "  Try again  "
                          << Term::color(Term::fg::red) << "<"
                          << Term::move_cursor(15, 7)
                          << Term::color(Term::fg::blue) << "  To the Menu  "
                          << Term::color(Term::style::reset) << std::flush;
                selection = true;
                break;
            case 's':
            case Term::Key::ARROW_DOWN:
                std::cout << Term::move_cursor(14, 7)
                          << Term::color(Term::fg::blue) << "   Try again   "
                          << Term::move_cursor(15, 7)
                          << Term::color(Term::fg::red) << ">"
                          << Term::color(Term::fg::blue) << " To the Menu "
                          << Term::color(Term::fg::red) << "<"
                          << Term::color(Term::style::reset) << std::flush;
                selection = false;
                break;
            case 'q':
            case Term::Key::ESC:
            case Term::Key::CTRL + 'c':
                return true;  // quit
                break;
            case Term::Key::ENTER:
                if (selection)
                    return false;
                else
                    return true;
                break;
            default:
                break;
        }
    }
}
void snake::snake::highscore() {
    highscores[10] = score;
    std::sort(highscores, highscores + 11);
    std::ofstream outputFile("scores.txt", std::ios::trunc);
    for (short int i = 10; i > 0; i--) {
        outputFile << highscores[i] << std::endl;
        std::cout << highscores[i];
    }
    outputFile.close();
}
void snake::snake::clearField() {
    std::cout << Term::move_cursor(7, 2) << "                         "
              << Term::move_cursor(8, 2) << "                         "
              << Term::move_cursor(9, 2) << "                         "
              << Term::move_cursor(10, 2) << "                         "
              << Term::move_cursor(11, 2) << "                         "
              << Term::move_cursor(12, 2) << "                         "
              << Term::move_cursor(13, 2) << "                         "
              << Term::move_cursor(14, 2) << "                         "
              << Term::move_cursor(15, 2) << "                         "
              << Term::move_cursor(16, 2) << "                         "
              << Term::move_cursor(17, 2) << "                         "
              << std::flush;
}

void snake::snake::clearFieldDisplay() {
    clearField();
    std::cout << Term::move_cursor(6, 2) << "                         "
              << Term::move_cursor(18, 2) << "                         "
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
