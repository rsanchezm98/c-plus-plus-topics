#ifndef TEMPLATE_UTILS_HPP
#define TEMPLATE_UTILS_HPP

#include <iostream>

namespace template_utils{


/* A template function is not created until it is called 
* with the typename or class. Here class is a synomim of 
* typename*/
template <typename T>
void print(T val)
{
    std::cout << val << std::endl;
}

/* A Template class implemenation that prints a template value
* The functions are implemented in a .cpp */
template <typename T>
class templateClass {       
    public:

        templateClass();
        ~templateClass();

        void print(T value);

        bool get_status();

    private:

        bool using_class = true;
     
};


} // end of namespace

#endif // TEMPLATE_UTILS_HPP