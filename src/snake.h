#pragma once

namespace snake
{
    class snake
    {
    private:
        const unsigned short int screen[2]{30, 30};
        unsigned short int snakePos[2][100]{0};
        unsigned short int newSnakePos[2]{0};
        unsigned short int snakeLength = 1;
        unsigned short int apple[2][2]{0};
        bool magentaAppleExist = false;
        unsigned short int score = 0;
        unsigned short int lastDir{};
        bool consoleSupportsColors{};
        short int input{};

        /* pre-game */
        inline void initColorMode();
        inline void setDefaultPos();

        /* drawing */
        void drawScore();
        inline void drawField();
        inline void drawWatermark();
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
            explicit timer(unsigned int);
            virtual ~timer() = default;
            // true means snake moves
            [[nodiscard]] bool done() const;
        };
    }
}
