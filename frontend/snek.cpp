#include <cpp-terminal/terminal.h>
#include <menu/menu.hpp>

int main()
{
    // try/catch to make sure the destructor of Term::Terminal gets called to reset the terminal state
    try
    {
        // setup terminal library, CTRL+C will prevent Term::Terminal's destructor
        Term::Terminal termObj(true,true);
        termObj.save_screen();
        // turn off the cursor
        std::cout << Term::cursor_off();

        // start the menu
        menu::menu menuObj;
        menuObj.start(&termObj);

        // make sure the terminal is reverted to its original state
        std::cout << Term::color(Term::style::reset)
                  << Term::color(Term::fg::reset)
                  << Term::color(Term::bg::reset)
                  << Term::cursor_on();
    }
    // cpp-terminal will throw a runtime error on exceptions
    catch(const std::runtime_error& re)
    {
        std::cerr << "Runtime error: " << re.what() << std::endl;
        return 1;
    }
    // catch unknown errors
    catch (...)
    {
        std::cerr << "Unknown error." << std::endl;
        return 2;
    }
    return 0;
}