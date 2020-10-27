#pragma once

// text color
#define blueBackground 1
#define greenText 2
#define redText 3
#define whiteText 4
#define magentaText 5
#define yellowText 6

namespace utils
{
    // returns a std::chrono timestamp
    unsigned int getTimestamp();

    // returns a random number in between 0 and the given number
    unsigned short int randomNum(const unsigned short int*);

    void initNcurses();
    void initColorMode();

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