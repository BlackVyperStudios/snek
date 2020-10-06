#pragma once

namespace snake
{
    class snake
    {
    private:
        /* game variables */
        unsigned short int snakePos[2][100]{0};
        unsigned short int newSnakePos[2]{0};
        unsigned short int snakeLength = 1;
        unsigned short int apple[2][2]{0};
        bool magentaAppleExist = false;
        unsigned short int score = 0;
        unsigned short int lastDir{};
        short int input{};
        double snakeSpeedFactor{};
        unsigned short int snakeSpeed{};
        /* game options */
        const bool oppositeDir = false;
        const unsigned short int minSpeed = 10;
        const unsigned short int maxSpeed = 500;
        const bool movementFix = false;
        const unsigned short int screen[2];
        /* automatic options */
        bool consoleSupportsColors = true;

        /* pre-game */
        void setDefaultPos();
        void calcSpeedFactor();

        /* drawing */
        void drawScore();
        void drawField();
        void animateField();
        void drawWatermark();
        void animateWatermark();
        void drawSnake();
        void drawApple(unsigned short int);

        /* game-object creation */
        void createApple(unsigned short int);

        /* game-object updating */
        void updateApple();

        /* checks */
        bool illegalPosition(const unsigned short int*, const unsigned short int*, bool);
        bool redAppleEaten();
        bool magentaAppleEaten();

        /* game mechanics */
        void getInput();
        void updateSnakePos();
        void calcNewSnakePos();
        void increaseSnakeSpeed();

        /* fixes */
        inline void normaliseMovementSpeed() const;
    public:
        // constructor for default game options
        explicit snake(bool, bool, unsigned short int, unsigned short int);
        // constructor for manual game options
        snake(bool, bool, bool, unsigned short int, unsigned short int, bool, unsigned short int, unsigned short int, bool);
        // updates the game state
        unsigned short int update();
        // destructor destroys game and ncurses
        virtual ~snake();
        // toggles possible movement in the opposite direction
    };
}
