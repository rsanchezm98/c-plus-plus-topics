#include <iostream>
#include <vector>

/* simple struct*/
struct vector3d
{
    int x;
    int y;
    int z;

    /* constructor */
    vector3d(int x, int y, int z)
        : x(x), y(y), z(z)
    {
        
    }
    /* copy constructor */
    vector3d(const vector3d& copy)
        :x(copy.x), y(copy.y), z(copy.z)
    {
        std::cout << "Copied!" << std::endl;
    }

    /* print function */
    void print()
    {
        std::cout << x << ", " << y << ", " << z << std::endl;
    }
};

int main()
{
    /* create the struct */
    vector3d myVector(2, 2, 2);
    myVector.print();

    /* make a copy */
    std::cout << "Making a copy" << std::endl;
    vector3d newVector = myVector;
    newVector.print();

    /* Here there has been 6 copies, why is that possible? */
    std::cout << "Making a vector of vector3d" << std::endl;
    std::vector<vector3d> first;
    first.push_back(vector3d(1,2,3));
    first.push_back(vector3d(4,5,6));
    first.push_back(vector3d(7,8,9));

    for(unsigned i = 0; i < first.size(); i++)
    {
        first[i].print();
    }
    
    /* The answer is that the std::vector capacity is set to 1 by default,
    * each time we attempt to push_back, it manages to increase the capacity
    * by one. This is done by copying the previous content to a vector, so 
    * 1 + [1+1] + [1+1+1] = 6 copies*/

    std::cout << "Making a vector of vector3d with .reserve()" << std::endl;
    std::vector<vector3d> second;
    /* preallocate memory of 3, so that not to have to change 
    * the capacity of the vector on each push_back(). The memory is reserved previously */
    second.reserve(3);
    second.push_back(vector3d(1,2,3));
    second.push_back(vector3d(4,5,6));
    second.push_back(vector3d(7,8,9));

    /* We still have 3 copies, it is because the vector3d instance is created in the main
    * function. Then it is copied to the vector. To solve that we must use
    * .emplace_back() so that is created on the vector back and not in the main function */

    std::cout << "Making a vector of without copies!" << std::endl;
    std::vector<vector3d> final;
    final.reserve(3);
    /* With emplace_back() we just have to pass the parameter list to the constructor, not an object
    * as it will be created on the vector, and not outside */
    final.emplace_back(1,2,3);
    final.emplace_back(4,5,6);
    final.emplace_back(7,8,9);

    return 0;
}