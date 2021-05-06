#include <cpp-terminal/terminal.h>
#include <string>

namespace snake {
class snake {
   private:
        // stores the coordinates of the snake snakePos[X/Y][snakeLength]
        unsigned short int snakePos[2][100]{0};
        // stores the apple's position applePos[X/Y]
        unsigned short int applePos[2]{0};
        // length of the snake
        unsigned short int snakeLength = 1;
        // saves the score
        unsigned short int score = 0;
        // stores the movement speed
        unsigned short int snakeSpeed = 1000;
        // stores the additional space between the console borders to the borders of the field
        enum FieldPos {
            f_row = 6,
            f_column = 1,
        };
        // stores the screen size
        enum screenSize {
            s_row = 12,
            s_column = 26
        };
        // stores the values for parsing input
        enum Input {
            up,
            down,
            left,
            right,
            pause,
            quit,
            none
        };
        // set the maximum and minimum movement speed
        enum speed {
            max = 500,
            min = 10
        };
        // stores the current input
        Input input = Input::none;

        // moves the coordinated into the filed
        std::string move_cursor(unsigned short int&, unsigned short int&);

        // draws the HUD
        void drawDisplay();
        // draws the snake
        void drawSnake();
        // parses input
        void getInput(Term::Terminal&);
        // moves the snake
        void moveSnake();
        // update snakePos[][]
        void updateSnake(unsigned short int, unsigned short int);
        // checks if the game is over
        unsigned short int check_game_state();
        // checks if the given coordinate is on the snake body
        bool isOnSnake(unsigned short int&, unsigned short int&);
        // draws the score
        void drawScore();
        // sets applePos[] and draws the apple
        void createApple();
        // draws the apple
        void drawApple();
        // draws the field - used for testing
        void drawField();
        // the pause sequence
        void pauseMenu(Term::Terminal&);
        // updates the snake's speed
        void setSnakeSpeed();
        // loose screen
        bool looseScreen(Term::Terminal&);
        // clears the field
        void clearField();
        // prepares the game
        void prepareGame();

   public:
        snake(bool);

        unsigned short int run(Term::Terminal&);

        virtual ~snake() = default;
};




    // timer class
    // TODO: move into library
    static unsigned int get_timepoint()
    {
        return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
    }
    class timer
    {
        public:
        timer(unsigned int _duration) : duration{ _duration }
        {
            old_time = get_timepoint();
        }
        unsigned int duration;
        virtual ~timer() = default;
        unsigned int old_time;
        unsigned int paused_state = 0;
        bool done() {
            return (get_timepoint() - old_time) > duration;
        };
        void pause(){
            paused_state = get_timepoint() - old_time;
        }
        void resume() {
            duration = paused_state;
            old_time = get_timepoint();
        }
    };
}  // namespace snake
