#include <iostream>
#include <chrono>
#include <thread>
#include <string>

/* the timer_ measures the life of the scope inside it is called */
struct timer_
{
    std::chrono::_V2::system_clock::time_point init;
    std::chrono::_V2::system_clock::time_point end;
    std::chrono::duration<double> latency;
    std::string name;

    /* with explicit we make the struct only callable with this constructor */
    explicit timer_(const std::string& function_name)
        : name(function_name)
    {
        init = std::chrono::high_resolution_clock::now();
    }

    /* when the destructor is called the latency is computed */
    ~timer_()
    {
        end = std::chrono::high_resolution_clock::now();
        latency = end - init;
        std::cout << "[" << name << "]: Duration of " << latency.count()*1000.0 << " ms" << std::endl;
    }
};

void testFunction(const std::string& name_of_func)
{
    timer_ time(name_of_func);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
}

int main()
{
    /* create the main latency timer */
    timer_ mainTimer("main_function");

    /* we can not do this as the struct is explicitly created *
    *  timer_ mainTimer;
    */

    /* call a function that has its own timer inside*/
    testFunction("test_function");
    return 0;
}
