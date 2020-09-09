#pragma once

namespace utils
{
    unsigned int getTimestamp();
    unsigned short int randomNum(const unsigned short int*);
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
