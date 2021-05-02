#include <iostream>
#include <chrono>
#include <thread>
#include <future> /* c++ library for async */
#include <vector>

using namespace std::chrono_literals;

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

#define ASYNC_MODE 1

#if ASYNC_MODE

static std::mutex s_Mutex;
void addToVect(std::vector<int>* myVector, int count)
{   
    /* we have to lock the function so as not to modify myVector by different threads simultaneously */
    std::lock_guard<std::mutex> lock(s_Mutex);
    myVector->push_back(count);
    //std::cout << "[async]: thread id: " << std::this_thread::get_id() <<  " -- add count: " << count << "\n";
    if(count == 9999) std::cout << "Finished the async stuff\n";
}
#endif


int main()
{
    /* create the main latency timer */
    timer_ mainTimer("main");
    std::vector<int> values;


#if ASYNC_MODE
    /* we must receive void future vectors */
    std::vector<std::future<void>> future_vect;
    std::cout << "Starting some async stuff\n";

    for(unsigned i = 0; i < 10000; i++)
        future_vect.push_back(std::async(std::launch::async, addToVect, &values, i));
#else
    /* Some blocking stuff */
    std::cout << "Starting some blocking stuff\n";
    std::this_thread::sleep_for(1s);
    std::cout << "Finished some blocking stuff\n";
#endif

    /* do other stuff */
    std::cout << "Started other main stuff\n";
    std::this_thread::sleep_for(1s);
    std::cout << "End of main stuff\n";
 
    return 0;
}
