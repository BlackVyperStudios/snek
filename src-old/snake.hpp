#pragma once

namespace snake
{
    class snake
    {
    private:
        /* game variables */
        // stores the snakes position
        unsigned short int snakePos[2][100]{0};
        // temporarily stores the next snake movement
        unsigned short int newSnakePos[2]{0};
        // snakes length
        unsigned short int snakeLength = 1;
        bool pause = false;
        // for checking if the whole snake should be drawn
        bool drawWholeSnek = false;
        // stores the apple positions apple[<appleDefinition>][<X/Y>], please use the apple definition
        unsigned short int apple[2][2]{0};
        // indicates if the magenta apple exists currently
        bool magentaAppleExist = false;
        // score
        unsigned short int score = 0;
        // indicates the last direction the snake moved to, please use the definitions
        unsigned short int lastDir{};
        // stores the input, please use the definitions
        short int input{};
        // stores the calculated snake speed factor for generating the actual snake speed
        double snakeSpeedFactor{};
        // stores the actual snake speed
        unsigned short int snakeSpeed{};
        /* game options */
        // minimum snake speed in micro seconds
        const unsigned short int minSpeed = 10;
        // maximum snake speed in micro seconds
        const unsigned short int maxSpeed = 500;
        // game screen size screen[X/Y]
        const unsigned short int screen[2];
        /* automatic options */
        // toggles, if the console supports colors
        bool consoleSupportsColors = true;

        /* pre-game */
        // places the snake to the default position
        void setDefaultPos();
        // calculates the speed factor for generating the actual snake speed
        void calcSpeedFactor();

        /* drawing */
        void drawScore();
        void drawPause();
        void drawField();
        void animateField();
        void drawWatermark();
        void animateWatermark();
        void drawSnake();
        // draws the apple drawApple(appleDefinition), please use the definitions
        void drawApple(unsigned short int);

        /* game-objects*/
        // creates a new apple createApple(appleDefinition), please use the definitions
        void createApple(unsigned short int);
        // responsible for updating the apples (creating or adding them)
        void updateApple();

        /* checks */
        // if true the given position is already in use or illegal illegalPosition(X,Y,snake?)
        // the bool toggles, if places, where the apple could exists are illegal or not (and the opposite)
        bool illegalPosition(const unsigned short int*, const unsigned short int*, bool);
        bool redAppleEaten();
        bool magentaAppleEaten();

        /* game mechanics */
        // measures the input and stores it
        void getInput();
        // updates the snakePos[][]
        void updateSnakePos();
        // calculates on what position the snake would be next
        void calcNewSnakePos();
        // calculates the actual snake speed and stores it into snakeSpeed
        void increaseSnakeSpeed();
    public:
        // constructor for default game options
        snake(bool, bool, unsigned short int, unsigned short int);
        // constructor for manual game options
        snake(bool, bool, unsigned short int, unsigned short int, unsigned short int, unsigned short int,
              bool);
        // updates the game state
        unsigned short int update();
        // destructor destroys game and ncurses
        virtual ~snake();
    };
}
