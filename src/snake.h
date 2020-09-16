#pragma once

// input parsing values
#define moveUp 1
#define moveDown 2
#define moveLeft 3
#define moveRight 4
#define noInput 0
#define userQuit -1
// last direction parsing values
#define notMovedYet 0
#define lastDirUp 1
#define lastDirDown 2
#define lastDirRight 3
#define lastDirLeft 4

namespace snake
{
    class snake
    {
    private:
        const unsigned short int screen[2]{30, 30};
        unsigned short int snakePos[2][100]{0};
        unsigned short int newSnakePos[2]{0};
        unsigned short int snakeLength = 1;
        unsigned short int apple[2]{0};
        unsigned short int score = 0;
        unsigned short int lastDir{};
        bool consoleSupportsColors{};
        short int input{};

        /* pre-game */
        void initColorMode();
        void setDefaultPos();

        /* drawing */
        void drawScore();
        void drawField();
        void drawSnake();
        void drawApple();

        /* game-object creation */
        void createApple();

        /* checks */
        bool illegalPosition(unsigned short int, unsigned short int);
        bool appleEaten();

        /* game mechanics */
        void getInput();
        void updateSnakePos();
        void calcNewSnakePos();

        /* fixes */
        void normaliseMovementSpeed() const;
    public:
        // constructor initialises the complete game and ncurses
        explicit snake();
        // updates the game state
        unsigned short int update();
        // destructor destroys game and ncurses
        virtual ~snake();
    };
    namespace utils
    {
        // returns a std::chrono timestamp
        unsigned int getTimestamp();

        // returns a random number in between 0 and the given number
        unsigned short int randomNum(const unsigned short int*);

        void initNcurses();

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
