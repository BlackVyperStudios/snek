#include <chrono>
#include <random>
#if defined(_WIN32)
#include <ncurses/ncurses>
#elif (__linux__)
#include <ncurses.h>
#endif
#include "snake.h"

// input parsing values
#define moveUp 1
#define moveDown 2
#define moveLeft 3
#define moveRight 4
#define noInput 0
#define userQuit -1
// last direction parsing values
#define notMovedYet 0
#define lastDirUp 1
#define lastDirDown 2
#define lastDirRight 3
#define lastDirLeft 4
// apple color
#define redApple 0
#define magentaApple 1
// text color
#define blueText 1
#define greenText 2
#define redText 3
#define whiteText 4
#define magentaText 5

/* ==== pre-game ==== */
snake::snake::snake()
{
    utils::initNcurses();
    initColorMode();
    setDefaultPos();
    drawField();
    drawSnake();
    createApple(redApple);
    drawApple(redApple);
    drawScore();
}
void snake::snake::initColorMode()
{
    consoleSupportsColors = has_colors();
    if (consoleSupportsColors)
    {
        start_color();
        init_pair(blueText, COLOR_BLUE, COLOR_BLUE);
        init_pair(greenText, COLOR_GREEN, COLOR_BLACK);
        init_pair(redText, COLOR_RED, COLOR_BLACK);
        init_pair(whiteText, COLOR_WHITE, COLOR_BLACK);
        init_pair(magentaText, COLOR_MAGENTA, COLOR_BLACK);
    }
}
void snake::snake::setDefaultPos()
{
    // set snakePos coordinates
    snakePos[0][0] = screen[0] / 2;
    snakePos[1][0] = screen[1] / 2;
    snakePos[0][1] = snakePos[0][0];
    snakePos[1][1] = snakePos[1][0] + 1;
}

/* ==== drawing ==== */
void snake::snake::drawApple(unsigned short int color)
{
    // TODO make blinking for the first 1/2/3 seconds after placing it

    if (color == redApple && consoleSupportsColors)
    {
        attron(COLOR_PAIR(redText));
        mvaddch(apple[redApple][1],apple[redApple][0], 'O');
        attroff(COLOR_PAIR(redText));
    }
    else if (color == magentaApple && consoleSupportsColors)
    {
        attron(COLOR_PAIR(magentaText));
        mvaddch(apple[magentaApple][1],apple[magentaApple][0], 'O');
        attroff(COLOR_PAIR(magentaText));
    }
    else if (color == redApple && !consoleSupportsColors)
        mvaddch(apple[redApple][1],apple[redApple][0], 'A');
    else if (color == magentaApple && !consoleSupportsColors)
        mvaddch(apple[redApple][1],apple[redApple][0], 'S');
}
void snake::snake::drawSnake()
{
    if (consoleSupportsColors)
        attron(COLOR_PAIR(greenText));

    mvaddch(snakePos[1][0],snakePos[0][0], 'O');

    for (unsigned short int i = 1; i < snakeLength; i++)
    {
        mvaddch(snakePos[1][i],snakePos[0][i], 'o');
    }
    // erase tail
    mvaddch(snakePos[1][snakeLength], snakePos[0][snakeLength], ' ');
    if (consoleSupportsColors)
        attroff(COLOR_PAIR(greenText));
}
void snake::snake::drawField()
{
    // TODO animate first draw of the field
    if (consoleSupportsColors)
        attron(COLOR_PAIR(blueText));
    for (unsigned short int i = 0; i < screen[1]; i++)
    {
        for (unsigned short int j = 0; j < screen[0]; j++)
        {
            if (i == 0 || j == 0 || i == screen[1] -1 || j == screen[0] - 1)
                mvaddch(i,j,'#');
        }
    }
    if (consoleSupportsColors)
        attroff(COLOR_PAIR(blueText));

    // TODO draw watermark
    // attron(COLOR_PAIR(4));
    // mvaddch(2, screen[0])
    // attroff(COLOR_PAIR(4));
}
void snake::snake::drawScore()
{
    if (consoleSupportsColors)
        attron(COLOR_PAIR(whiteText));
    mvprintw(2,screen[0] + 2, "Score: %d", score);
    if (consoleSupportsColors)
        attroff(COLOR_PAIR(whiteText));
}

/* ==== game-object creation ==== */
void snake::snake::createApple(unsigned short int color)
{
    // TODO apple disappears sometimes (probably a problem with one field not detected by illegalPosition())
    //  probably one behind the tail and gets removed by tail erase because snake gets one larger so the free space behind the tail gets erased, increase illegalPos end point (snakeLength + 1)
    unsigned short int randomLocation[2];
    bool notRandom = true;
    while (notRandom)
    {
        // create random location
        randomLocation[0] = utils::randomNum(&screen[0]);
        randomLocation[1] = utils::randomNum(&screen[1]);
        if (!illegalPosition(randomLocation[0], randomLocation[1], true))
            notRandom = false;
    }
    apple[color][0] = randomLocation[0];
    apple[color][1] = randomLocation[1];
}

/* game-object updating */
void snake::snake::updateApple()
{
    // red apple
    if (redAppleEaten())
    {
        // TODO animate score and tail changes
        score += 10;
        snakeLength++;
        createApple(redApple);
        if (snakeLength % 5 == 0 && !magentaAppleExist)
        {
            createApple(magentaApple);
            drawApple(magentaApple);
            magentaAppleExist = true;
        }
        drawApple(redApple);
        drawScore();
    }
    else if (magentaAppleEaten())
    {
        score += 20;
        snakeLength++;
        magentaAppleExist = false;
        drawScore();
    }
}

/* ==== checks ==== */
bool snake::snake::illegalPosition(const unsigned short int locationX, const unsigned short int locationY, bool illegalApple)
{
    if (locationX != 0 && locationY != 0 || locationX != screen[0] -1 && locationY != screen[1] -1 ||
        locationX != apple[redApple][0] && locationY != apple[redApple][1] && illegalApple ||
        locationX != apple[magentaApple][0] && locationY != apple[magentaApple][1] && illegalApple)
    {
        for (unsigned short int i = 0; i < snakeLength; i++)
        {
            if (snakePos[0][i] == locationX && snakePos[1][i] == locationY)
            {
                return true;
            }
        }
        return false;
    }
    return true;
}
bool snake::snake::redAppleEaten()
{
    if (snakePos[0][0] == apple[redApple][0] && snakePos[1][0] == apple[redApple][1])
        return true;
    else
        return false;
}
bool snake::snake::magentaAppleEaten()
{
    if (snakePos[0][0] == apple[magentaApple][0] && snakePos[1][0] == apple[magentaApple][1])
        return true;
    else
        return false;
}

/* === game-update === */
unsigned short int snake::snake::update()
{
    /* pre-move tasks */
    getInput();
    // check, if the player newer moved to skip the other tasks
    if (lastDir == notMovedYet && input == noInput)
        return 0;
    // check, if the user wants to exit the game
    else if (input == userQuit)
        return 1;
    // make up and down movement slower to make it feel as fast as left and right movement
    normaliseMovementSpeed();
    // calculates the new snake position for illegalPosition() and updateSnake()
    // TODO split into X,Y to avoid declaration of newSnakePos[] -> or reimplement
    calcNewSnakePos();
    // check, if the new snake destination is illegal (if that's true, the player looses)
    if (illegalPosition(newSnakePos[0],newSnakePos[1], false))
        return 2;
    updateSnakePos();
    /* draw */
    drawSnake();
    /* object updating */
    updateApple();
    return 0;
}

/* game mechanics */
void snake::snake::getInput()
{
    short int ch;
    utils::timer timer(500);
    while (!timer.done())
    {
        ch = getch();
        if (ch != ERR)
        {
            switch (ch)
            {
                case KEY_UP:
                case 'w':
                    input = moveUp;
                    break;
                case KEY_DOWN:
                case 's':
                    input = moveDown;
                    break;
                case KEY_LEFT:
                case 'a':
                    input = moveLeft;
                    break;
                case KEY_RIGHT:
                case 'd':
                    input = moveRight;
                    break;
                case 27: // ESC key
                case 'q':
                    input = userQuit;
                    break;
                default:
                    input = noInput;
            }
            // skip timer, if it's the first move
            if (lastDir == notMovedYet)
                break;
        }
    }

}
void snake::snake::calcNewSnakePos()
{
    switch (input)
    {
        case noInput:
            break;
        case moveUp:
            newSnakePos[0] = snakePos[0][0];
            newSnakePos[1] = snakePos[1][0] - 1;
            lastDir = lastDirUp;
            return;
        case moveDown:
            newSnakePos[0] = snakePos[0][0];
            newSnakePos[1] = snakePos[1][0] + 1;
            lastDir = lastDirDown;
            return;
        case moveLeft:
            newSnakePos[0] = snakePos[0][0] - 1;
            newSnakePos[1] = snakePos[1][0];
            lastDir = lastDirLeft;
            return;
        case moveRight:
            newSnakePos[0] = snakePos[0][0] + 1;
            newSnakePos[1] = snakePos[1][0];
            lastDir = lastDirRight;
            return;
    }
    switch (lastDir)
    {
        case lastDirUp:
            newSnakePos[0] = snakePos[0][0];
            newSnakePos[1] = snakePos[1][0] - 1;
            return;
        case lastDirDown:
            newSnakePos[0] = snakePos[0][0];
            newSnakePos[1] = snakePos[1][0] + 1;
            return;
        case lastDirLeft:
            newSnakePos[0] = snakePos[0][0] - 1;
            newSnakePos[1] = snakePos[1][0];
            return;
        case lastDirRight:
            newSnakePos[0] = snakePos[0][0] + 1;
            newSnakePos[1] = snakePos[1][0];
            return;
    }
}
void snake::snake::updateSnakePos()
{
    // first array is prev1 or prev2, seconds is x/y
    unsigned short int preLoc[2][2];

    preLoc[0][0] = snakePos[0][0];
    preLoc[0][1] = snakePos[1][0];

    snakePos[0][0] = newSnakePos[0];
    snakePos[1][0] = newSnakePos[1];

    for (unsigned short int i = 1; i < snakeLength +1; i++)
    {
        preLoc[1][0] = snakePos[0][i];
        preLoc[1][1] = snakePos[1][i];

        snakePos[0][i] = preLoc[0][0];
        snakePos[1][i] = preLoc[0][1];

        preLoc[0][0] = preLoc[1][0];
        preLoc[0][1] = preLoc[1][1];
    }
}
/* fixes */
void snake::snake::normaliseMovementSpeed() const
{
    if (input == moveUp || input == moveDown || input == noInput && lastDir == lastDirUp || input == noInput && lastDir == lastDirDown)
    {
        utils::timer timer(140);
        while (!timer.done())
        {
            // wait
        }
    }
}
snake::snake::~snake()
{
    // destroys ncurses
    endwin();
}
/* utils */
unsigned int snake::utils::getTimestamp()
{
    return std::chrono::time_point_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now()).time_since_epoch().count();
}
unsigned short int snake::utils::randomNum(const unsigned short int *maxNum)
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);
    return generator() % *maxNum; // lowers the number to the specified range
}
snake::utils::timer::timer(unsigned int millisecondsToWait)
{
    startTime = getTimestamp();
    timeToWait = millisecondsToWait;
}
bool snake::utils::timer::done() const
{
    unsigned int timeTaken = getTimestamp() - startTime;
    return timeTaken / 1000 > timeToWait;
}
void snake::utils::initNcurses()
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