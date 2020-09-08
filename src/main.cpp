// snake
#include <ncurses/ncurses.h>
#include <iostream>
#include <random>
#include <chrono>

unsigned short int screen[2]{30, 30};
unsigned short int snake[2][100]{0};
unsigned short int snakeLength = 1;
unsigned short int apple[2]{0};
unsigned short int score = 0;

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
int moveSnake()
{
    unsigned short int ch = getch();
    if (ch == KEY_UP || ch == 'w')
        updateSnake(snake[0][0], snake[1][0] -1);
    else if (ch == KEY_DOWN || ch == 's')
        updateSnake(snake[0][0], snake[1][0] +1);
    else if (ch == KEY_LEFT || ch == 'a')
        updateSnake(snake[0][0] -1, snake[1][0]);
    else if (ch == KEY_RIGHT || ch == 'd')
        updateSnake(snake[0][0] +1, snake[1][0]);
    else if (ch == 'q' || ch == 27) // 27 = ESC key
        return 1;

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
    if (!firstDraw)
        mvaddch(snake[1][snakeLength], snake[0][snakeLength], ' ');
    attroff(COLOR_PAIR(2));
}
void drawField()
{
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
    // TODO just disable colors if they are not supported
    if (has_colors() == FALSE) {
        endwin();
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
    }
    // destroys ncurses
    endwin();
    if (quit == 1)
        std::cout << "Game aborted...\n";
    else if (quit == 2)
        std::cout << "Game Over!\n";
    return 0;
}
