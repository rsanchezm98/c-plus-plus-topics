#include <iostream>
#include "data_structures_array.hpp"
#include "data_structures_vector.hpp"

int main()
{

    std::cout << "************** ARRAY SECTION **************\n";
    int prevArray[2] = {1,2};
    structures::array<int,2> test(prevArray); 

    test[0] = 1;
    test[1] = 2;

    /* this calls the copy constructor */
    structures::array<int,2> test3 = test;
    test[0] = 999;
    test3[1] = 999;

    structures::array<std::string,2> test_;
    test_[0] = "Rodrigo";
    std::cout << test_[0] << std::endl;

    std::cout << *test_.data() << std::endl;


    for(size_t i = 0; i < test.size(); i++)
    {
        std::cout << "test: " << test[i] << " -- newtest: " << test3[i] << "\n";
    }

    std::cout << "************** VECTOR SECTION **************\n";


    return 0;
}