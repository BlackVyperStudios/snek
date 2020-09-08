// snake
#include <ncurses/ncurses.h>
#include <iostream>
#include <random>
#include <chrono>

#if defined(_WIN32)
#include <windows.h>
#elif (__linux__)
#include <unistd.h>
#endif

// TODO make vars a struct
// optimize data types
unsigned short int screen[2]{30, 30};
unsigned short int snake[2][100]{0};
unsigned short int snakeLength = 1;
unsigned short int apple[2]{0};
unsigned short int score = 0;
unsigned short int lastDir;
bool consoleSupportsColors;
/*
 * // TODO rework field like this
 * field:
 *
 * ############# SNEK
 * #           # by MCWertGaming
 * #           #
 * #           # Time: XX:XX // TODO implement time clock
 * #           # Score: XX
 * #           #
 * #           #
 * #############
 *
 */

// TODO move universal functions into a namespace
// TODO move logic into class // namespace
// change qualified functions to inline functions

unsigned int getTimestamp()
{
    return std::chrono::time_point_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now()).time_since_epoch().count();
}

void sleepFor(long double milliSeconds)
{
    // two versions are needed due to different sleep() functions on windows and linux
#if defined(_WIN32)
    Sleep(milliSeconds);
#elif (__linux__)
    usleep(milliSeconds * 1000);
#endif
}

bool illegalPosition(const unsigned short int locationX, const unsigned short int locationY, bool legalHead)
{
    if (locationX != 0 && locationY != 0 && locationX != screen[0] -1 && locationY != screen[1] -1)
    {
        unsigned short int i = 0;
        if (legalHead) { i++;}
        for (; i < snakeLength; i++)
        {
            if (snake[0][i] == locationX && snake[1][i] == locationY)
            {
                return true;
            }
        }
        return false;
    }
    return true;
}
unsigned short int randomNum(const unsigned short int *maxNum)
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);
    return generator() % *maxNum; // lowers the number to the specified range
}
void drawApple()
{
    // make blinking for the first 1/2/3 seconds after placing it
    attron(COLOR_PAIR(3));
    mvaddch(apple[1],apple[0], 'O');
    attroff(COLOR_PAIR(3));
}
void drawScore()
{
    attron(COLOR_PAIR(4));
    mvprintw(2,screen[0] + 2, "Score: %d", score);
    attroff(COLOR_PAIR(4));
}
void createApple()
{
    unsigned short int randomLocation[2];
    bool notRandom = true;
    while (notRandom)
    {
        // create random location
        randomLocation[0] = randomNum(&screen[0]);
        randomLocation[1] = randomNum(&screen[1]);
        if (!illegalPosition(randomLocation[0], randomLocation[1], false))
            notRandom = false;
    }
    apple[0] = randomLocation[0];
    apple[1] = randomLocation[1];
    drawApple();
    drawScore();
}
void updateSnake(const unsigned short int newX, const unsigned short int newY)
{
    // check if apple gets eaten
    if (newX == apple[0] && newY == apple[1])
    {
        snakeLength++;
        score = score + 10;
        createApple();
    }
    // first array is prev1 or prev2, seconds is x/y
    unsigned short int preLoc[2][2];

    preLoc[0][0] = snake[0][0];
    preLoc[0][1] = snake[1][0];

    snake[0][0] = newX;
    snake[1][0] = newY;

    for (unsigned short int i = 1; i < snakeLength +1; i++)
    {
        preLoc[1][0] = snake[0][i];
        preLoc[1][1] = snake[1][i];

        snake[0][i] = preLoc[0][0];
        snake[1][i] = preLoc[0][1];

        preLoc[0][0] = preLoc[1][0];
        preLoc[0][1] = preLoc[1][1];
    }
}
class timer
{
private:
    unsigned int startTime;
    unsigned int timeToWait;
public:
    // constructor starts timer
    explicit timer(unsigned int);
    virtual ~timer() = default;
    // true means snake moves
    [[nodiscard]] bool done();
};
timer::timer(unsigned int millisecondsToWait)
{
    startTime = getTimestamp();
    timeToWait = millisecondsToWait;
}
bool timer::done()
{
    unsigned int timeTaken = getTimestamp() - startTime;
    return timeTaken / 1000 > timeToWait;
}
int moveSnake()
{
    // TODO improve this section
    // TODO skip everything, if the player has not moved yet
    // TODO add more time on up and down movement
    // TODO ignore key holding
    // TODO ignore keypress during wait
    timer timer(100);
    unsigned short int ch = getch();
    bool snakeAlreadyMoved = false;
        if (ch == KEY_UP || ch == 'w')
        {
            while (!timer.done())
            {
                sleepFor(1);
            }
            updateSnake(snake[0][0], snake[1][0] -1);
            lastDir = 1;
            snakeAlreadyMoved = true;
        }
        else if (ch == KEY_DOWN || ch == 's')
        {
            while (!timer.done())
            {
                sleepFor(1);
            }
            updateSnake(snake[0][0], snake[1][0] +1);
            lastDir = 2;
            snakeAlreadyMoved = true;
        }
        else if (ch == KEY_LEFT || ch == 'a')
        {
            while (!timer.done())
            {
                sleepFor(1);
            }
            updateSnake(snake[0][0] -1, snake[1][0]);
            lastDir = 3;
            snakeAlreadyMoved = true;
        }
        else if (ch == KEY_RIGHT || ch == 'd')
        {
            while (!timer.done())
            {
                sleepFor(1);
            }
            updateSnake(snake[0][0] +1, snake[1][0]);
            lastDir = 4;
            snakeAlreadyMoved = true;
        }
        else if (ch == 'q' || ch == 27) // 27 = ESC key
            return 1;
    if (!snakeAlreadyMoved)
    {
        while (!timer.done())
        {
            sleepFor(1);
        }
        if (lastDir == 1)
        {
            updateSnake(snake[0][0], snake[1][0] -1);
        }
        else if (lastDir == 2)
            updateSnake(snake[0][0], snake[1][0] +1);
        else if (lastDir == 3)
            updateSnake(snake[0][0] -1, snake[1][0]);
        else if (lastDir == 4)
            updateSnake(snake[0][0] +1, snake[1][0]);
    }
    // TODO make preMoveChecks before updateSnake() to avoid 2 size glitch and save time
    if (illegalPosition(snake[0][0], snake[1][0], true))
        return 2;
    return 0;
}
void drawSnake(bool firstDraw)
{
    attron(COLOR_PAIR(2));

    mvaddch(snake[1][0],snake[0][0], 'O');

    for (unsigned short int i = 1; i < snakeLength; i++)
    {
        mvaddch(snake[1][i],snake[0][i], 'o');
    }
    // exclude remove of edge 0/0 on first draw
    // dont remove snakeHead on tail remove
    if (!firstDraw)
        mvaddch(snake[1][snakeLength], snake[0][snakeLength], ' ');
    attroff(COLOR_PAIR(2));
}
void drawField()
{
    // TODO animate first draw of the field
    attron(COLOR_PAIR(1));
    for (unsigned short int i = 0; i < screen[1]; i++)
    {
        for (unsigned short int j = 0; j < screen[0]; j++)
        {
            if (i == 0 || j == 0 || i == screen[1] -1 || j == screen[0] - 1)
                mvaddch(i,j,'#');
        }
    }
    attroff(COLOR_PAIR(1));

    // TODO draw watermark
    // attron(COLOR_PAIR(4));
    // mvaddch(2, screen[0])
    // attroff(COLOR_PAIR(4));
}
void gameSetup()
{
    // initialise ncurses
    initscr();
    cbreak();
    noecho();
    raw();
    timeout(0);
    curs_set(0);
    keypad(stdscr,true);
    // TODO just disable colors if they are not supported
    consoleSupportsColors = has_colors();
    if (!consoleSupportsColors) {
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4,COLOR_WHITE, COLOR_BLACK);

    drawField();

    // set snake coordinates
    snake[0][0] = screen[0] / 2;
    snake[1][0] = screen[1] / 2;
    snake[0][1] = snake[0][0];
    snake[1][1] = snake[1][0] + 1;
    snakeLength = 1;

    drawSnake(true);

    createApple();
}
int main()
{
    gameSetup();

    unsigned short int quit;

    // game loop
    while (true)
    {
        quit = moveSnake();
        if (quit != 0)
            break;
        drawSnake(false);
        // sleepFor(1000);
    }
    // destroys ncurses
    endwin();
    if (quit == 1)
        std::cout << "Game aborted...\n";
    else if (quit == 2)
        std::cout << "Game Over!\n";
    return 0;
}
