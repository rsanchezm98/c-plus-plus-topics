#include <iostream>
#include <memory> /* use of smart pointers*/
#include <string>
#include <vector>


struct AllocationTracker
{
    uint32_t m_TotalAllocated = 0;
    uint32_t m_TotalFreed = 0;

    ~AllocationTracker()
    {
        std::cout << "Total allocated memory: " << m_TotalAllocated << " bytes\n";
        std::cout << "Total deallocated memory: " << m_TotalFreed << " bytes\n";
    }

    uint32_t CurrentUsage() { return (m_TotalAllocated - m_TotalFreed);}
};

/* create a static instance of the tracker */
static AllocationTracker s_MemoryTracker;

static void PrintMetrics()
{
    std::cout << "Memory usage: " << s_MemoryTracker.CurrentUsage() << " bytes\n";
}

void* operator new(size_t size)
{
    s_MemoryTracker.m_TotalAllocated += size;
    std::cout << "Allocating " << size << " bytes\n";   
    return malloc(size);
}

/*
void operator delete(void* memory)
{
    std::cout << "Deallocating\n";
    free(memory);
}
*/

void operator delete(void* memory, std::size_t size)
{
    s_MemoryTracker.m_TotalFreed += size;
    std::cout << "Deallocating " << size << " bytes\n";
    free(memory);
}


int main()
{   
    PrintMetrics();
    {   
        /* this allocates but does not deallocate std::vector with the overloaded delete operator */
        /* it only calls the commented overloaded delete operator */
        /* need to solve this */
        std::vector<int> vector_;
        vector_.push_back(0);
        vector_.push_back(1);
    }
    PrintMetrics();
    {
        auto unique_ = std::make_unique<std::vector<std::string>>();
    }
    PrintMetrics();

    return 0;
}
