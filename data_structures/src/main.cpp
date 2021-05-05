#include <iostream>
#include "data_structures_utils.hpp"

int main()
{

    structures::array<int,2> test; 

    test[0] = 1;
    test[1] = 2;

    /* this implyies a copy */
    structures::array<int,2> newtest(test); 

    /* this implyies a copy */
    structures::array<int,2> test3 = test;

    for(size_t i = 0; i < test.size(); i++)
    {
        std::cout << "test: " << test[i] << " -- newtest: " << test3[i] << "\n";
    }


    /* to do:
    * rlvalue construction
    * std::move
    */
    return 0;
}