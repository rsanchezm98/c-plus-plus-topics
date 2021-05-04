#include <iostream>
#include <string.h> /* we add this to mount our c++ String class */

class String
{
    public:
        String() = default;

        /* constructor */
        String(const char* string)
        {
            std::cout << "Created string!\n";
            m_Size = strlen(string);
            m_Data = new char[m_Size];
            memcpy(m_Data, string, m_Size);
        }
        /* copy constructor */
        String(const String& other)
        {
            std::cout << "Copied string!\n";
            m_Size = other.m_Size;
            m_Data = new char[m_Size];
            memcpy(m_Data, other.m_Data, m_Size);
        }
        /* move constructor so as to avoid copies when passed as an rvalue
        * this will be called when std::move(string) */
        String(String&& other)
        {
            std::cout << "Moved string!\n";
            m_Size = other.m_Size;
            m_Data = other.m_Data;
            other.m_Size = 0;
            other.m_Data = nullptr;
        }

        /*overload the = operator so as to allow to be assigned an rvalue without copying */
        String& operator=(String&& other)
        {
            std::cout << "Assigned string without copying!\n";

            if(this != &other)
            {
                delete[] m_Data;
                m_Size = other.m_Size;
                m_Data = other.m_Data;
                other.m_Size = 0;
                other.m_Data = nullptr;
            }

            return *this;
        }

        void Print()
        {
            for(int i = 0; i < m_Size; i++)
            {
                std::cout << m_Data[i];
            }
            std::cout << "\n";
        }

        ~String()
        {
            std::cout << "Destroyed string!\n";
            delete m_Data;
        }

    private:
        char* m_Data;
        int m_Size;
};

class Entity
{
    public:
        /* this constructor is called both with lvalues and rvalues 
        * if and rvalue is provided and an rvalue constructor exists, 
        * that will be called instead*/
        Entity(const String& name)
        : m_Name(name)
        {
            std::cout << "Created entity!\n";
        }
        /* we create an rvalue constructor, it is a temporary String
         * we move the created String to the m_Name string and call the 
         * move constructor of the String class*/
        Entity(String&& other)
            : m_Name(std::move(other))
        {
            std::cout << "Created entity by an rvalue!\n";
        }
        ~Entity()
        {
            std::cout << "Destroyed entity!\n";
        }


        void PrintName()
        {
            m_Name.Print();
        }
    private:
        String m_Name;
};



int main()
{   
    /* Expected behaviour:
    * Creation of a temporary string by giving a rvalue
    * Moving the temporary string [is an rvalue] to the Entity m_Name string
    * Creating the Entity [this will be displayed later as the constructor first moves the input]
    * Destroying the temporary string
    * Destroy entity [and the string that has inside]
    */

    std::cout << "********** Creating Entity by an rvalue **********\n";
    {
        Entity myEntity("Rodrigo");
        myEntity.PrintName();
    }


    /* Expected behaviour:
    * Creation of an lvalue string
    * Copying the lvalue string to the Entity m_Name string
    * Creating the Entity [this will be displayed later as the constructor first moves the input]
    * Destroy entity and the string that has inside
    * Destroy the String name
    */
    std::cout << "********** Creating string by an lvalue **********\n";
    {
        String name("Rodrigo");
        Entity myEntity(name);
        myEntity.PrintName();
    }

    /* We avoid one heap allocation which is done each time we copy a string */


    /* here we overload the assing operator so as to allow to reassign rvalues [from an lvalue] to an lvalue
    * the expected behaviour is that with std::move no copy takes place [any allocations are done]*/
    std::cout << "********** Reassigning a temporary string to an lvalue **********\n";
    {
        String name("Rodrigo");
        String surname("Sanchez");
        name.Print();
        /* with std::move we get an rvalue of an lvalue [surname] */
        name = std::move(surname);
        name.Print();
    }

    return 0;
}
