#include <iostream>
#include <thread>
#include "timer_utils.hpp"

#define PROFILING 1
#if PROFILING
    #define PROFILE_SCOPE(name) timer::InstrumentationTimer timer##__LINE__(name)
    #define PROFILE_FUNCTION() PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
    #define PROFILE_SCOPE(name)
#endif

namespace test{
    void testFunction1()
    {
        PROFILE_FUNCTION();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(0.5s);
    }

    void testFunction2()
    {
        PROFILE_FUNCTION();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    }

    void RunFunctions()
    {
        PROFILE_FUNCTION();

        std::cout << "Running functions\n";
        std::thread first(testFunction1);
        std::thread second(testFunction2);

        first.join();
        second.join();
    }
}

int main()
{   
    /* create the main latency timer */
    timer::Timer mainTimer(__PRETTY_FUNCTION__);

    timer::Instrumentor::Get()->BeginSession("Profile", "results.json");
    test::RunFunctions();
    timer::Instrumentor::Get()->EndSession();

    return 0;
}
