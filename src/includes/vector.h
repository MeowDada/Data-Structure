#ifndef DS_VECTOR_VECTOR_H
#define DS_VECTOR_VECTOR_H

#define DS_VECTOR_DEFAULT_CAPACITY (1)
#define DS_VECTOR_DEFAULT_FACTOR   (2)

#include <iostream>
#include <algorithm>
#include <utility>
#include <cstddef>
#include <cstring>

namespace meowdada 
{
    template <typename T>
    class vector
    {
        public:
            typedef T *iterator;

            vector()
            : size(0), capacity(DS_VECTOR_DEFAULT_CAPACITY), elements(new T[capacity])
            {
                std::cout << "default constructor" << std::endl;
            }

            vector(const vector<T>& other)
            : size(other.size), capacity(other.capacity), elements(new T[capacity])
            {
                std::cout << "construct by other vector" << std::endl;

                std::copy(other.elements, other.elements + other.size, elements);
            }

            vector(vector<T>&& other)
            {
                
            }

            vector& operator=(vector<T> other)
            {
                std::cout << "copy assignment" << std::endl;

                swap(*this, other);
                return *this;
            }

            vector& operator=(const vector<T>& other)
            {
                if (this == &other) return *this;
                delete[] elements;
                elements = new T[other.capacity];
                std::copy(other.elements, other.elements + other.size, elements);
                size = other.size;
                capacity = other.capacity;
                return *this;
            }

            vector& operator=(vector<T>&& other);
            ~vector()
            {
                std::cout << "destructor" << std::endl;

                delete[] elements;
            }

            T& operator[] (int index)
            {
                return elements[index];
            }

            iterator begin()
            {
                return elements;
            }

            iterator end()
            {
                return &elements[size];
            }

            void push_front(const T& val)
            {
                resize_if_needed();
                if (size > 0) {
                    std::copy(elements, elements+size, elements+1);
                    elements[0].~T();
                }
                elements[0] = val;
                size++;
            }

            void push_back(const T& val)
            {                
                resize_if_needed();
                elements[size] = val;
                size++;
            }

            void pop_front()
            {
                if (size > 0) {
                    elements[0].~T();
                    std::copy(elements+1, elements+size, elements);
                    elements[size-1].~T();
                    size--;
                    resize_if_needed();
                }
            }

            void pop_back()
            {
                if (size > 0) {
                    elements[size-1].~T();
                    size--;
                    resize_if_needed();
                }
            }

            size_t get_size()
            {
                return this.size;
            }

            size_t get_capacity()
            {
                return this.capacity;
            }

            friend void swap(vector<T>& first, vector<T>& second)
            {
                using std::swap;

                swap(first.size, second.size);
                swap(first.capacity, second.capacity);
                swap(first.elements, second.elements);
            }

            void dump()
            {
                std::cout << "capacity: " << capacity << std::endl;
                std::cout << "size: " << size << std::endl;
                std::cout << "(";
                for(size_t i = 0 ; i < size ; i++)
                    std::cout << " " << elements[i];
                std::cout << " )" << std::endl;
            }

        private:
            size_t  size;
            size_t  capacity;
            T      *elements;

            void resize_if_needed()
            {
                if (capacity == size) {
                    capacity *= DS_VECTOR_DEFAULT_FACTOR;
                    reallocate_memory(capacity);
                }
                else if (capacity > 4 && size == capacity / 4) {
                    capacity /= DS_VECTOR_DEFAULT_FACTOR;
                    reallocate_memory(capacity);
                }
            }

            void reallocate_memory(size_t capacity_new)
            {
                T *elements_new =  new T[capacity_new];
                std::copy(elements, elements + size, elements_new);
                delete[] elements;
                elements = elements_new;
            }
    };
}
#endif /* DS_VECTOR_VECTOR_H */