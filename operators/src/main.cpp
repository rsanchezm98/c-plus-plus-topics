#include <iostream>

struct vector3d
{
    double x,y,z;

    /* default constructor */
    vector3d()
        : x(0.0), y(0.0), z(0.0)
    {
    }

    /* parameter constructor*/
    vector3d(double x, double y, double z)
        : x(x), y(y), z(z)
    {
    }

    /* add method */
    vector3d add(const vector3d& other) const
    {
        return vector3d(x + other.x, y + other.y, z + other.z); 
    }
    /* overload operator+ */
    vector3d operator+(const vector3d& other)
    {
        return add(other);
    }

    /* dot product method */
    double dot(const vector3d& other) const
    {
        return double(x*other.x + y*other.y + z*other.z); 
    }
    /* overload operator* */
    double operator*(const vector3d& other)
    {
        return dot(other);
    }

};

/* overload stream function. This overload cannot be inside the struct*/
std::ostream& operator<<(std::ostream& stream, const vector3d& vector) 
{   
    stream << "[" << vector.x << ", " << vector.y << ", " << vector.z <<"]";
    return stream;
}

int main()
{
    vector3d first(0.0, 1.0, 2.0);

    /* overload the sum */
    first = first + vector3d(1.0, 1.0, 1.0);

    /* overload the stream */
    std::cout << first << std::endl;

    vector3d second(2.0, 0.0, 2.0);

    /* overload dot product */
    std::cout << "dot product of a" << first << " and b" << second 
        << " = " <<  first*second << std::endl;

    return 0;
}
