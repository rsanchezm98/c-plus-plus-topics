#ifndef DATA_STRUCTURES_VECTOR_HPP
#define DATA_STRUCTURES_VECTOR_HPP

namespace structures{

template<typename T>
class vector
{
    public:

        vector()
        {
            /* we need to allocate some initial memory */
            f_ChangeCapacity(2);
            
        }

        ~vector()
        {
            clear();
            delete[] m_Data;
        }

        size_t size() const
        {
            return m_Size;
        }

        size_t capacity() const
        {
            return m_Capacity;
        }

        void push_back(const T& newC)
        {
            if(m_Size >= m_Capacity)
            {
                size_t newCapacity = m_Capacity + m_Capacity/2;
                f_ChangeCapacity(newCapacity);
            }
            
            m_Data[m_Size] = newC;
            m_Size++;
        }

        void push_back(T&& newC)
        {
            if(m_Size >= m_Capacity)
            {
                size_t newCapacity = m_Capacity + m_Capacity/2;
                f_ChangeCapacity(newCapacity);
            }
            
            m_Data[m_Size] = std::move(newC);
            m_Size++;
        }

        const T& operator[](size_t index) const
        {
            return m_Data[index];
        }

        T& operator[](size_t index)
        {
            return m_Data[index];
        }

        void print_vector()
        {
            for(size_t i = 0; i < m_Size; i++)
            {
                std::cout << m_Data[i] << "\n";
            }

            std::cout << "---------------------------\n";
        }

        template <typename... Args>
        T& emplace_back(Args&&... args)
        {
            if(m_Size >= m_Capacity)
            {
                size_t newCapacity = m_Capacity + m_Capacity/2;
                f_ChangeCapacity(newCapacity);
            }
            
            /* with this we can construct in place*/
            new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
            m_Size++;     
            return m_Data[m_Size - 1];      
        }

        void pop_back()
        {
            if(m_Size > 0)
            {
                m_Size--;
                /* We have to call the destructor of each element we delete */
                m_Data[m_Size].~T();
            }
        }

        void clear()
        {
            for(size_t i = 0; i < m_Size; i++)
            {
                m_Data[i].~T();
            }

            m_Size = 0;
        }

    private:

        /************* MEMBER FUNCTIONS *************/
        void f_ChangeCapacity(size_t newCapacity)
        {
            /* allocate a block of memory */
            T* newBlock = new T[newCapacity];
            
            /* if we decrease the size*/
            if(newCapacity < m_Size)
            {
                m_Size = newCapacity;
            }

            /* copy the previous data into the newBlock */
            for(size_t i = 0; i < m_Size; i++)
            {
                /* if there is no move constructor, it will be copied instead */
                newBlock[i] = std::move(m_Data[i]);
            }

            /* delete the m_Data and update the member variables */
            clear();
            delete[] m_Data;
            m_Data = newBlock;
            m_Capacity = newCapacity;

        
        }

        /************* ATTRIBUTES *************/
        /* the actual data is set to nullptr by default */
        T* m_Data = nullptr;

        /* the current filled size of the vector */
        size_t m_Size = 0;

        /* the total capacity of the allocated memory */
        size_t m_Capacity = 0;

};


} // end of namespace

#endif // DATA_STRUCTURES_VECTOR_HPP