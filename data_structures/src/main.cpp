#include <iostream>
#include "data_structures_array.hpp"
#include "data_structures_vector.hpp"
#include <string>


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
    
    structures::vector<int> vectorTest;
    vectorTest.push_back(3);
    vectorTest.push_back(4);
    std::cout << "capacity: " << vectorTest.capacity() << " -- size: " << vectorTest.size() << std::endl;
    vectorTest.push_back(3);
    std::cout << "capacity: " << vectorTest.capacity() << " -- size: " << vectorTest.size() << std::endl;

    vectorTest.print_vector();

    vectorTest.emplace_back(1);
    vectorTest.print_vector();
    vectorTest.clear();
    std::cout << "capacity: " << vectorTest.capacity() << " -- size: " << vectorTest.size() << std::endl;
    vectorTest.print_vector();
    

    structures::vector<std::string> stringVect;
    stringVect.push_back(std::string("Rodrigo"));
    stringVect.print_vector();
    stringVect.push_back("Sanchez");
    std::cout << "capacity: " << stringVect.capacity() << " -- size: " << stringVect.size() << std::endl;
    stringVect.push_back("dos");
    std::cout << "capacity: " << stringVect.capacity() << " -- size: " << stringVect.size() << std::endl;

    stringVect.print_vector();
    stringVect.clear();
    stringVect.emplace_back("Hello World");
    stringVect.print_vector();
    
    std::cout << "capacity: " << stringVect.capacity() << " -- size: " << stringVect.size() << std::endl;
    stringVect.print_vector();





    return 0;
}