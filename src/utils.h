#pragma once

namespace utils
{
    // returns a std::chrono timestamp
    unsigned int getTimestamp();

    // retuns a random number in between 0 and the given number
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
