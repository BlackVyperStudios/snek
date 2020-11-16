#include <cpp-terminal/terminal.h>
#include "menu.hpp"

int main()
{
    try
    {
        // setup terminal library
        Term::Terminal term(true,true);
        term.save_screen();
        // turn off the cursor
        std::cout << Term::cursor_off();

        menu::menu menuObj;
        menuObj.start(&term);


        // make sure the terminal is reverted to its original state
        std::cout << Term::color(Term::style::reset)
                  << Term::color(Term::fg::reset)
                  << Term::color(Term::bg::reset)
                  << Term::cursor_on();
    }
    catch(const std::runtime_error& re)
    {
        std::cerr << "Runtime error: " << re.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error." << std::endl;
        return 2;
    }

    return 0;
}