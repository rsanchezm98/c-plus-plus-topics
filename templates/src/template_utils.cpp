#include "template_utils.hpp"

namespace template_utils{

template<typename T>
templateClass<T>::templateClass()
{
    
}

template<typename T>
templateClass<T>::~templateClass()
{

}

template <typename T>
void templateClass<T>::print(T value)
{
    std::cout << value << std::endl;
}

template <typename T>
bool templateClass<T>::get_status()
{
    return using_class;
}
} // end of namespace