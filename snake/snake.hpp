namespace snake {
class snake {
   private:
        // stores the coordinates of the snake snakePos[X/Y][snakeLength]
        unsigned short int snakePos[2][100]{0};
        // length of the snake
        unsigned short int snakeLength = 1;
        // stores the apple applePos[X/Y]
        unsigned short int applePos[2]{0};
        // saves the score
        unsigned short int score = 0;

        // draws the HUD
        void drawDisplay();


        // draws the field - used for testing
        void drawField();
   public:
        snake(bool);
        virtual ~snake() = default;
};
}  // namespace snake
