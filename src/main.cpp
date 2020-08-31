//by Alexander Prosser

#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;

const int width = 50;
const int height = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100];
int nTail;

enum eDirecrion {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecrion dir;

void setup()
{
    gameOver = false;
    dir = STOP;

    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;

    score == 0;
}

void draw()
{
    system("cls");

    for (int i = 0; i < width +1; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (j == width - 1)
                cout << "#";

            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width +1; i++)
        cout << "#";
    cout << endl;

    cout << "SCORE: " << score << endl;
    if (dir == STOP)
        cout << "PAUSE" << endl;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case ' ':
            dir = STOP;
            break;
        case 'x':
            gameOver = true;
            break;
        default:
            break;
        }
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prevX2, prevY2;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prevX2 = tailX[i];
        prevY2 = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prevX2;
        prevY = prevY2;
    }

    switch (dir)
    {
    case STOP:
        x, y;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x > width - 2 || x < 0 || y > height - 1 || y < 0)
        gameOver = true;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        nTail++;
        score++;

        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main()
{
    setup();
    while (!gameOver)
    {
        draw();
        input();
        logic();
    }

    return 0;
}
