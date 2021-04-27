#include <iostream>
#include <string>
/* Note that what I have to include here is a .cpp not the .hpp*/
#include "template_utils.cpp"

int main()
{

    std::cout << "[template_utils] print()" << std::endl;
    template_utils::print("Rodrigo");
    template_utils::print(55);
    // we can indicate the tyname as <typename> or let the code decide
    template_utils::print<float>(55.1f);


    std::cout << "[template_utils] templateClass<int>" << std::endl;
    template_utils::templateClass<int> myClassInt;
    myClassInt.print(1);
    std::cout << myClassInt.get_status() << std::endl;

    std::cout << "[template_utils] templateClass<std::string>" << std::endl;
    template_utils::templateClass<std::string> myClassString;
    myClassString.print(std::string("Rodrigo"));
    std::cout << myClassString.get_status() << std::endl;

    return 0;
}