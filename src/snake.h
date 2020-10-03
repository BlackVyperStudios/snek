#pragma once

namespace snake
{
    class snake
    {
    private:
        /* game variables */
        const unsigned short int screen[2]{20, 20};
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
        /* automatic options */
        bool consoleSupportsColors{};

        /* pre-game */
        inline void initColorMode();
        inline void setDefaultPos();
        void calcSpeedFactor();

        /* drawing */
        void drawScore();
        void drawField();
        void drawWatermark();
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
        // constructor initialises the complete game and ncurses
        // TODO create overload for changing the screen size
        snake();
        // updates the game state
        unsigned short int update();
        // destructor destroys game and ncurses
        virtual ~snake();
        // toggles possible movement in the opposite direction
    };
    namespace utils
    {
        // returns a std::chrono timestamp
        inline unsigned int getTimestamp();

        // returns a random number in between 0 and the given number
        unsigned short int randomNum(const unsigned short int*);

        inline void initNcurses();

        // a simple timer
        class timer
        {
        private:
            unsigned int startTime;
            unsigned int timeToWait;
        public:
            // constructor starts timer
            explicit timer(unsigned short int);
            virtual ~timer() = default;
            // true means snake moves
            [[nodiscard]] bool done() const;
            void reset();
        };
    }
}
