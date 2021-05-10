#ifndef DATA_STRUCTURES_ARRAY_HPP
#define DATA_STRUCTURES_ARRAY_HPP

namespace structures{

template<typename T, size_t S>
class array
{
    public:
        array() = default;
        
        array(const T* data)
        {
            for(size_t i = 0; i < S; i++)
            {
                m_Data[i] = data[i];
            }   
        }

        /* copy constructor */
        array(const array& other)
        {
            std::cout << "Copy constructor!\n";
            for(size_t i = 0; i < S; i++)
            {
                m_Data[i] = other.m_Data[i];
            }
        }


        constexpr size_t size() const
        {
            return S;
        }


        /* for non const */
        T& operator[](int index)
        {
            return m_Data[index];
        }

        /* allows us to define a const array */
        const T& operator[](int index) const
        {
            return m_Data[index];
        }
        
        array& operator=(array const& other) {
            if (&other != this) {
                std::cout << "Copy operator\n";
                m_Data = other.m_Data;
            }
        return *this;
    }
        T* data()
        {
            return m_Data;
        }

        const T* data() const
        {
            return m_Data;
        }

    private:
        T m_Data[S];

};

} // end of namespace

#endif // DATA_STRUCTURES_ARRAY_HPP