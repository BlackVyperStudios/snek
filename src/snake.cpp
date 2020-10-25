#if defined(_WIN32)
// fix for MSYS2, because they are using the old directory structure
#include <ncurses/ncurses>
#elif (__linux__)
#include <ncurses.h>
#endif
#include "snake.hpp"
#include "utils.hpp"
#include "information.hpp"

// input parsing values
#define inputUp 1
#define inputDown 2
#define inputLeft 3
#define inputRight 4
#define noInput 0
#define inputQuit -1
// last direction parsing values
#define notMovedYet 0
#define lastDirUp 1
#define lastDirDown 2
#define lastDirRight 3
#define lastDirLeft 4
// apple color
#define redApple 0
#define magentaApple 1

/* ==== pre-game ==== */
snake::snake::snake(bool initNcurses, bool startupAnimations, unsigned short _screenX, unsigned short int _screenY)
                    : screen{_screenX, _screenY}
{
    if (initNcurses)
    {
        utils::initNcurses();
        utils::initColorMode();
        consoleSupportsColors = has_colors();
    }
    setDefaultPos();
    if (startupAnimations)
    {
        animateField();
        animateWatermark();
    }
    else
    {
        drawField();
        drawWatermark();
    }
    drawSnake();
    createApple(redApple);
    drawApple(redApple);
    drawScore();
    calcSpeedFactor();
    increaseSnakeSpeed();
}
snake::snake::snake(bool initNcurses, bool startupAnimations, bool _oppositeDir, unsigned short int _minSpeed,
                    unsigned short int _maxSpeed, bool _movementFix, unsigned short int _screenX,
                    unsigned short int _screenY, bool _enableColorMode)
                    : oppositeDir{_oppositeDir}, minSpeed{_minSpeed}, maxSpeed{_maxSpeed},
                      movementFix{_movementFix}, screen{_screenX, _screenY}, consoleSupportsColors{_enableColorMode}
{
    if (initNcurses)
    {
        utils::initNcurses();
        utils::initColorMode();
        consoleSupportsColors = has_colors();
    }
    setDefaultPos();
    if (startupAnimations)
    {
        animateField();
        animateWatermark();
    }
    else
    {
        drawField();
        drawWatermark();
    }
    drawSnake();
    createApple(redApple);
    drawApple(redApple);
    drawScore();
    calcSpeedFactor();
    increaseSnakeSpeed();
}
void snake::snake::setDefaultPos()
{
    // set snakePos coordinates
    snakePos[0][0] = screen[0] / 2;
    snakePos[1][0] = screen[1] / 2;
}
void snake::snake::calcSpeedFactor()
{
    snakeSpeedFactor = (double)100 / ((screen[0] - 1) * (screen[1] - 1));
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

    // tail gets erased before drawing the snake to avoid removing of the snakeHead
    // erase tail, but dont erase on first move due to last location at 0,0
    if (snakePos[0][snakeLength] != 0 && snakePos[1][snakeLength] != 0)
        mvaddch(snakePos[1][snakeLength], snakePos[0][snakeLength], ' ');

    mvaddch(snakePos[1][0],snakePos[0][0], 'O');

    if (snakeLength > 1)
        mvaddch(snakePos[1][1],snakePos[0][1], 'o');

    if (consoleSupportsColors)
        attroff(COLOR_PAIR(greenText));
}
void snake::snake::animateField()
{
    if (consoleSupportsColors)
        attron(COLOR_PAIR(blueBackground));
    utils::timer timer(10);
    for (unsigned short int i = 0; i < screen[0]; i++)
    {
        timer.reset();
        mvaddch(0,i,'#');
        refresh();
        while (!timer.done());
    }
    for (unsigned short int i = 0; i < screen[1]; i++)
    {
        timer.reset();
        mvaddch(i,screen[0],'#');
        refresh();
        while (!timer.done());
    }
    for (unsigned short int i = screen[0]; i > 0; i--)
    {
        timer.reset();
        mvaddch(screen[1],i,'#');
        refresh();
        while (!timer.done());
    }
    for (unsigned short int i = screen[1]; i > 0; i--)
    {
        timer.reset();
        mvaddch(i,0,'#');
        refresh();
        while (!timer.done());
    }
    if (consoleSupportsColors)
        attroff(COLOR_PAIR(blueBackground));
}
void snake::snake::drawField()
{
    if (consoleSupportsColors)
        attron(COLOR_PAIR(blueBackground));
    for (unsigned short int i = 0; i < screen[0]; i++)
    {
        mvaddch(0,i,'#');
        refresh();
    }
    for (unsigned short int i = 0; i < screen[1]; i++)
    {
        mvaddch(i,screen[0],'#');
        refresh();
    }
    for (unsigned short int i = screen[0]; i > 0; i--)
    {
        mvaddch(screen[1],i,'#');
        refresh();
    }
    for (unsigned short int i = screen[1]; i > 0; i--)
    {
        mvaddch(i,0,'#');
        refresh();
    }
    if (consoleSupportsColors)
        attroff(COLOR_PAIR(blueBackground));
}
void snake::snake::animateWatermark()
{
    if (consoleSupportsColors)
        attron(COLOR_PAIR(redText));
    utils::timer timer(100);
    mvaddch(1,screen[0] + 8, 'S');
    refresh();
    timer.reset();
    addch('N');
    refresh();
    while (!timer.done());
    timer.reset();
    addch('E');
    refresh();
    while (!timer.done());
    timer.reset();
    addch('K');
    refresh();
    while (!timer.done());
    if (consoleSupportsColors)
        attron(COLOR_PAIR(greenText));
    timer.reset();
    while (!timer.done());
    mvaddch(1,screen[0] + 6,'o');
    mvaddch(1,screen[0] + 13,'o');
    refresh();
    timer.reset();
    while (!timer.done());
    mvaddch(1,screen[0] + 5, 'o');
    mvaddch(1,screen[0] + 14,'o');
    refresh();
    timer.reset();
    while (!timer.done());
    mvaddch(1,screen[0] + 4, 'o');
    mvaddch(1,screen[0] + 15,'o');
    refresh();
    timer.reset();
    while (!timer.done());
    mvaddch(1,screen[0] + 3, 'o');
    mvaddch(1,screen[0] + 16,'o');
    refresh();
    timer.reset();
    while (!timer.done());
    mvaddch(1,screen[0] + 2, 'O');
    mvaddch(1,screen[0] + 17,'O');
    refresh();
    timer.reset();
    while (!timer.done());
    if (consoleSupportsColors)
        attron(COLOR_PAIR(redText));
    mvprintw(2,screen[0] + 2, "Version: ");
    refresh();
    timer.reset();
    while (!timer.done());
    printw("%d", SNAKE_VERSION_MAJOR);
    refresh();
    timer.reset();
    while (!timer.done());
    printw(".");
    refresh();
    timer.reset();
    while (!timer.done());
    printw("%d", SNAKE_VERSION_MINOR);
    refresh();
    timer.reset();
    while (!timer.done());
    printw(".");
    refresh();
    timer.reset();
    while (!timer.done());
    printw("%d", SNAKE_VERSION_PATCH);
    refresh();
    timer.reset();
    while (!timer.done());

    if (consoleSupportsColors)
        attron(COLOR_PAIR(redText));
    mvaddch(3,screen[0] + 2, 'b');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('y');
    refresh();
    timer.reset();
    while (!timer.done());
    mvaddch(3,screen[0] + 5, 'M');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('C');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('W');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('e');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('r');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('t');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('G');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('a');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('m');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('i');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('n');
    refresh();
    timer.reset();
    while (!timer.done());
    addch('g');
    if (consoleSupportsColors)
        attroff(COLOR_PAIR(blueBackground));
}
void snake::snake::drawWatermark()
{
    if (consoleSupportsColors)
        attron(COLOR_PAIR(redText));
    mvprintw(1,screen[0] + 8, "SNEK");
    if (consoleSupportsColors)
        attron(COLOR_PAIR(greenText));
    mvprintw(1,screen[0] + 2,"Ooooo ");
    mvprintw(1,screen[0] + 13,"ooooO");
    if (consoleSupportsColors)
        attron(COLOR_PAIR(redText));
    mvprintw(2,screen[0] + 2, "Version: %d.%d.%d", SNAKE_VERSION_MAJOR, SNAKE_VERSION_MINOR, SNAKE_VERSION_PATCH);
    if (consoleSupportsColors)
        attron(COLOR_PAIR(redText));
    mvprintw(3,screen[0] + 2, "by MCWertGaming");
    if (consoleSupportsColors)
        attroff(COLOR_PAIR(blueBackground));
}
void snake::snake::drawScore()
{
    if (consoleSupportsColors)
        attron(COLOR_PAIR(greenText));
    mvprintw(4,screen[0] + 2, "Score: %d", score);
    if (consoleSupportsColors)
        attroff(COLOR_PAIR(whiteText));
}

/* ==== game-object creation ==== */
void snake::snake::createApple(unsigned short int color)
{
    unsigned short int randomLocation[2];
    bool notRandom = true;
    while (notRandom)
    {
        // create random location
        randomLocation[0] = utils::randomNum(&screen[0]);
        randomLocation[1] = utils::randomNum(&screen[1]);
        if (!illegalPosition(&randomLocation[0], &randomLocation[1], true))
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
        score += 1;
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
        if (snakeLength % 5 == 0)
            increaseSnakeSpeed();
    }
    else if (magentaAppleEaten())
    {
        score += 2;
        snakeLength++;
        magentaAppleExist = false;
        drawScore();
        if (snakeLength % 5 == 0)
            increaseSnakeSpeed();
    }
}

/* ==== checks ==== */
bool snake::snake::illegalPosition(const unsigned short int *locationX, const unsigned short int *locationY,
                                   bool illegalApple)
{
    // make apple pos illegal for the createApple()
    if (*locationX != 0 && *locationY != 0 && *locationX != screen[0] && *locationY != screen[1])
    {
        if (!illegalApple && *locationX == snakePos[0][snakeLength-1] && *locationY == snakePos[1][snakeLength-1])
            return false;
        unsigned short int snakeLengthCopy = snakeLength;
        // prevent spawning of the apple on the tail of the snake, which gets erased
        if (illegalApple)
            snakeLengthCopy++;
        for (unsigned short int i = 0; i < snakeLengthCopy; i++)
        {
            if (snakePos[0][i] == *locationX && snakePos[1][i] == *locationY)
            {
                return true;
            }
        }
        if (illegalApple && apple[redApple][0] == *locationX && apple[redApple][1] == *locationY ||
            illegalApple && apple[magentaApple][0] == *locationX && apple[magentaApple][0] == *locationY)
            return true;
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
    else if (input == inputQuit)
        return 1;
    // make up and down movement slower to make it feel as fast as left and right movement
    if (movementFix)
        normaliseMovementSpeed();
    // calculates the new snake position for illegalPosition() and updateSnake()
    calcNewSnakePos();
    // check, if the new snake destination is illegal (if that's true, the player looses)
    if (illegalPosition(&newSnakePos[0],&newSnakePos[1], false))
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
    utils::timer timer(snakeSpeed);
    while (!timer.done())
    {
        ch = getch();
        if (ch != ERR)
        {
            switch (ch)
            {
                case KEY_UP:
                case 'w':
                    if (oppositeDir || !oppositeDir && lastDir != lastDirDown || snakeLength == 1)
                        input = inputUp;
                    break;
                case KEY_DOWN:
                case 's':
                    if (oppositeDir || !oppositeDir && lastDir != lastDirUp || snakeLength == 1)
                        input = inputDown;
                    break;
                case KEY_LEFT:
                case 'a':
                    if (oppositeDir || !oppositeDir && lastDir != lastDirRight || snakeLength == 1)
                        input = inputLeft;
                    break;
                case KEY_RIGHT:
                case 'd':
                    if (oppositeDir || !oppositeDir && lastDir != lastDirLeft || snakeLength == 1)
                        input = inputRight;
                    break;
                case 27: // ESC key
                case 'q':
                    input = inputQuit;
                    break;
                default:
                    input = noInput;
            }
        }
        // skip timer, if it's the first move
        if (lastDir == notMovedYet)
            break;
    }
}
void snake::snake::calcNewSnakePos()
{
    switch (input)
    {
        case noInput:
            break;
        case inputUp:
            newSnakePos[0] = snakePos[0][0];
            newSnakePos[1] = snakePos[1][0] - 1;
            lastDir = lastDirUp;
            return;
        case inputDown:
            newSnakePos[0] = snakePos[0][0];
            newSnakePos[1] = snakePos[1][0] + 1;
            lastDir = lastDirDown;
            return;
        case inputLeft:
            newSnakePos[0] = snakePos[0][0] - 1;
            newSnakePos[1] = snakePos[1][0];
            lastDir = lastDirLeft;
            return;
        case inputRight:
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
void snake::snake::increaseSnakeSpeed()
{
    snakeSpeed = (unsigned int) (500 - snakeSpeedFactor * snakeLength / ((double)minSpeed / maxSpeed));
}

/* fixes */
void snake::snake::normaliseMovementSpeed() const
{
    if (input == inputUp || input == inputDown || input == noInput && lastDir == lastDirUp || input == noInput &&
        lastDir == lastDirDown)
    {
        utils::timer timer(140);
        while (!timer.done());
    }
}
snake::snake::~snake()
{
    // destroys ncurses
    endwin();
}
