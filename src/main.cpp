// snake
#include <ncurses/ncurses.h>
#include <iostream>
#include <random>
#include <chrono>

unsigned short int screenX = 30;
unsigned int short screenY = 30;

// add snake
unsigned short int snake[2][100]{0};
unsigned short int snakeLenght = 2;
// add apple
unsigned int apple[2]{0};


bool illegalPosition(const unsigned short int locationX, const unsigned short int locationY, bool legalHead)
{
    if (locationX != 0 && locationY != 0 && locationX != screenX -1 && locationY != screenY -1)
    {
        unsigned short int i = 0;
        if (legalHead) { i++;}
        for (; i < snakeLenght; i++)
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
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed);
    return generator() % *maxNum; // lowers the number to the specified range
}
void drawApple()
{
    mvaddch(apple[1],apple[0], 'A');
}
void createApple()
{
    unsigned short int randomLocation[2];
    bool notRnadom = true;
    while (notRnadom)
    {
        // create random location
        randomLocation[0] = randomNum(&screenX);
        randomLocation[1] = randomNum(&screenY);
        if (!illegalPosition(randomLocation[0], randomLocation[1], false))
            notRnadom = false;
    }
    apple[0] = randomLocation[0];
    apple[1] = randomLocation[1];
    drawApple();
}
void updateSnake(const unsigned short int newX, const unsigned short int newY)
{
    // check if apple gets eaten
    if (newX == apple[0] && newY == apple[1])
    {
        snakeLenght++;
        createApple();
    }

    unsigned short int prevX = snake[0][0];
    unsigned short int prevY = snake[1][0];
    unsigned short int prevX2, prevY2;

    snake[0][0] = newX;
    snake[1][0] = newY;

    for (unsigned short int i = 1; i < snakeLenght +1; i++)
    {
        prevX2 = snake[0][i];
        prevY2 = snake[1][i];

        snake[0][i] = prevX;
        snake[1][i] = prevY;

        prevX = prevX2;
        prevY = prevY2;
    }
    snake[0][0] = newX;
    snake[1][0] = newY;
}
int moveSnake()
{
    unsigned short int ch = getch();
    if (ch == KEY_UP)
        updateSnake(snake[0][0], snake[1][0] -1);
    else if (ch == KEY_DOWN)
        updateSnake(snake[0][0], snake[1][0] +1);
    else if (ch == KEY_LEFT)
        updateSnake(snake[0][0] -1, snake[1][0]);
    else if (ch == KEY_RIGHT)
        updateSnake(snake[0][0] +1, snake[1][0]);
    else if (ch == 'q')
        return 1;

    // TODO make preMoveChecks before updateSnake() to avoid 2 size glitch and save time
    if (illegalPosition(snake[0][0], snake[1][0], true))
        return 2;
    return 0;
}
void drawSnake(bool firstDraw)
{
    for (unsigned short int i = 0; i < snakeLenght; i++)
    {
        mvaddch(snake[1][i],snake[0][i], 'S');
    }
    // exclude remove of edge 0/0 on first draw
    if (!firstDraw)
        mvaddch(snake[1][snakeLenght], snake[0][snakeLenght], ' ');
}
void drawField()
{
    for (unsigned short int i = 0; i < screenY; i++)
    {
        for (unsigned short int j = 0; j < screenX; j++)
        {
            if (i == 0 || j == 0 || i == screenY -1 || j == screenX - 1)
                mvaddch(i,j,'#');
        }
    }
}

void gameSetup()
{
    // initialise ncurses
    initscr();
    cbreak();
    noecho();
    raw();
    curs_set(0);
    keypad(stdscr,true);

    drawField();

    // set snake coordinates
    snake[0][0] = screenX / 2;
    snake[1][0] = screenY / 2;
    snake[0][1] = snake[0][0];
    snake[1][1] = snake[1][0] + 1;
    snakeLenght = 2;

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
    }
    // destroys ncurses
    endwin();
    if (quit == 1)
        std::cout << "Game aborted...\n";
    else if (quit == 2)
        std::cout << "Game Over!\n";
    return 0;
}
