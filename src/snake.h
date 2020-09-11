#pragma once

#include "utils.h"

// TODO make vars a struct
// TODO optimize data types
unsigned short int screen[2]{30, 30};
unsigned short int snakePos[2][100]{0};
unsigned short int snakeLength = 1;
unsigned short int apple[2]{0};
unsigned short int score = 0;
unsigned short int lastDir;
bool consoleSupportsColors;

namespace snake
{
    void drawApple()
    {
        // make blinking for the first 1/2/3 seconds after placing it
        attron(COLOR_PAIR(3));
        mvaddch(apple[1],apple[0], 'O');
        attroff(COLOR_PAIR(3));
    }
    bool illegalPosition(const unsigned short int locationX, const unsigned short int locationY, bool legalHead)
    {
        if (locationX != 0 && locationY != 0 && locationX != screen[0] -1 && locationY != screen[1] -1)
        {
            unsigned short int i = 0;
            if (legalHead) { i++;}
            for (; i < snakeLength; i++)
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
    void drawSnake(bool firstDraw)
    {
        attron(COLOR_PAIR(2));

        mvaddch(snakePos[1][0],snakePos[0][0], 'O');

        for (unsigned short int i = 1; i < snakeLength; i++)
        {
            mvaddch(snakePos[1][i],snakePos[0][i], 'o');
        }
        // exclude remove of edge 0/0 on first draw
        // dont remove snakePosHead on tail remove
        if (!firstDraw)
            mvaddch(snakePos[1][snakeLength], snakePos[0][snakeLength], ' ');
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
            randomLocation[0] = utils::randomNum(&screen[0]);
            randomLocation[1] = utils::randomNum(&screen[1]);
            if (!snake::illegalPosition(randomLocation[0], randomLocation[1], false))
                notRandom = false;
        }
        apple[0] = randomLocation[0];
        apple[1] = randomLocation[1];
        snake::drawApple();
        drawScore();
    }
    void updateSnakePos(const unsigned short int newX, const unsigned short int newY)
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

        preLoc[0][0] = snakePos[0][0];
        preLoc[0][1] = snakePos[1][0];

        snakePos[0][0] = newX;
        snakePos[1][0] = newY;

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
    int moveSnake()
    {
        // TODO improve this section
        // TODO skip everything, if the player has not moved yet
        // TODO add more time on up and down movement
        short int ch;
        unsigned short int movementKey;
        utils::timer timer(500);
        while (!timer.done())
        {
            ch = getch();
            if (ch != ERR)
                movementKey = ch;
        }

        bool snakePosAlreadyMoved = false;
        if (movementKey == KEY_UP || movementKey == 'w')
        {
            updateSnakePos(snakePos[0][0], snakePos[1][0] -1);
            lastDir = 1;
            snakePosAlreadyMoved = true;
        }
        else if (movementKey == KEY_DOWN || movementKey == 's')
        {
            updateSnakePos(snakePos[0][0], snakePos[1][0] +1);
            lastDir = 2;
            snakePosAlreadyMoved = true;
        }
        else if (movementKey == KEY_LEFT || movementKey == 'a')
        {
            updateSnakePos(snakePos[0][0] -1, snakePos[1][0]);
            lastDir = 3;
            snakePosAlreadyMoved = true;
        }
        else if (movementKey == KEY_RIGHT || movementKey == 'd')
        {
            updateSnakePos(snakePos[0][0] +1, snakePos[1][0]);
            lastDir = 4;
            snakePosAlreadyMoved = true;
        }
        else if (movementKey == 'q' || movementKey == 27) // 27 = ESC key
            return 1;
        if (!snakePosAlreadyMoved)
        {
            if (lastDir == 1)
                updateSnakePos(snakePos[0][0], snakePos[1][0] -1);
            else if (lastDir == 2)
                updateSnakePos(snakePos[0][0], snakePos[1][0] +1);
            else if (lastDir == 3)
                updateSnakePos(snakePos[0][0] -1, snakePos[1][0]);
            else if (lastDir == 4)
                updateSnakePos(snakePos[0][0] +1, snakePos[1][0]);
        }
        // TODO make preMoveChecks before updateSnakePos() to avoid 2 size glitch and save time
        if (snake::illegalPosition(snakePos[0][0], snakePos[1][0], true))
            return 2;
        return 0;
    }
    void gameSetup()
    {
        // initialise ncurses
        initscr();
        cbreak();
        noecho();
        raw();
        nodelay(stdscr, true);
        scrollok(stdscr, true);
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

        snake::drawField();

        // set snakePos coordinates
        snakePos[0][0] = screen[0] / 2;
        snakePos[1][0] = screen[1] / 2;
        snakePos[0][1] = snakePos[0][0];
        snakePos[1][1] = snakePos[1][0] + 1;
        snakeLength = 1;

        snake::drawSnake(true);

        snake::createApple();
    }
}
