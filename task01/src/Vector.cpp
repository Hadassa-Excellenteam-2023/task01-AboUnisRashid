#pragma once
#include "Vector.h"


//--------------------------------------------------------------------------------

/*MOVE constructor*/
Vector::Vector(Vector&& other) noexcept : m_size(other.m_size), m_capacity(other.m_size), m_array(other.m_array) {
    /*std::cout << "moved" << std::endl;*/

    other.m_size = 0;
    other.m_capacity = 0;
    other.m_array = nullptr;

}
//--------------------------------------------------------------------------------
/*Vector class constructor*/
Vector::Vector(std::size_t size, int value)
{
    // Set the member variable m_size to the value of size
    m_size = size;
    
    // Set the member variable m_capacity to the value of size
    m_capacity = size;
    
    // Allocate memory for the array using the new operator
    m_array = new int[m_capacity];
    
    // Initialize each element of the array with the value provided
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = value;
    }

}

//--------------------------------------------------------------------------------
// Copy constructor
Vector::Vector(const Vector& other)
{
    // Copy the size and capacity of the other vector to the lvalue vector's member variables
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    // Allocate a new array for the lvalue vector using the capacity of the other vector
    m_array = new int[m_capacity];

    // Copy the elements of the other vector's array to the lvalue vector's array
    for (std::size_t i = 0; i < m_size; ++i) {
        m_array[i] = other.m_array[i];
    }

}
//--------------------------------------------------------------------------------
/*copy assignment operator*/
Vector& Vector::operator=(const Vector& other)
{
    // Check for self-assignment
    if (this != &other)
    {
        // Resize the lvalue vector's array if necessary
        if (m_size != other.m_size)
        {
            // Allocate a new array with the same size as the other vector's array
            int* new_array = new int[other.m_size];

            // Copy the elements of the other vector's array to the new array
            for (std::size_t i = 0; i < other.m_size; ++i) {
                new_array[i] = other.m_array[i];
            }

            // Deallocate the old array and update the lvalue vector's member variables
            delete[] m_array;
            m_array = new_array;
            m_size = other.m_size;
            m_capacity = other.m_size;
        }
        else // No need to resize the array
        {
            // Copy the elements of the other vector's array to the lvalue vector's array
            for (std::size_t i = 0; i < m_size; ++i) {
                m_array[i] = other.m_array[i];
            }
        }

    }
    return *this;
}

//--------------------------------------------------------------------------------
/*move assignment operator, receives a temporary rvalue other and moves it to lvalue*/
Vector& Vector::operator=(Vector&& other) noexcept {
    /*std::cout << "move operator" << std::endl;*/
    if (this != &other) {
        delete[] m_array;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_array = other.m_array;
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_array = nullptr;
    }
    return *this;
}

//--------------------------------------------------------------------------------

void Vector::push_back(const int& value) {
    // Check if we need to resize the array
    if (m_size >= m_capacity) {
        // Double the capacity to reduce the number of reallocations
        std::size_t new_capacity = m_capacity * 2;
        int* new_array = new int[new_capacity];

        // Copy the existing elements to the new array
        for (std::size_t i = 0; i < m_size; i++) {
            new_array[i] = m_array[i];
        }

        // Delete the old array and update the pointer and capacity
        delete[] m_array;
        m_array = new_array;
        m_capacity = new_capacity;
    }

    // Add the new element to the end of the array and update the size
    m_array[m_size] = value;
    m_size++;
}

//--------------------------------------------------------------------------------

void Vector::resize(std::size_t count) {
	resize(count, 0);
	
}

//--------------------------------------------------------------------------------

void Vector::resize(std::size_t count, const int& value) {
    if (count <= m_capacity) {
        if (count < m_size) {
            // Truncate the vector by updating its size
            m_size = count;
        } else if (count > m_size) {
            // Append the specified value to the vector for the remaining elements
            for (std::size_t i = m_size; i < count; ++i) {
                m_array[i] = value;
            }
            m_size = count;
        }
    } else {
        // Allocate a new buffer with appropriate size
        std::size_t new_capacity = m_capacity * 2;
        while (new_capacity < count) {
            new_capacity *= 2;
        }

        // Create new array and copy elements from old array to new array
        int* new_array = new int[new_capacity];
        for (std::size_t i = 0; i < m_size; ++i) {
            new_array[i] = m_array[i];
        }
        // Append the specified value to the vector for the remaining elements
        for (std::size_t i = m_size; i < count; ++i) {
            new_array[i] = value;
        }

        // Deallocate the old buffer and update the vector's fields
        delete[] m_array;
        m_array = new_array;
        m_capacity = new_capacity;
        m_size = count;
    }
}

//--------------------------------------------------------------------------------
/* data() function whitch returns a pointer of first cell*/
int* Vector::data() const {
	if (m_size != 0) {
		return &m_array[0];
	}
}

//--------------------------------------------------------------------------------
void Vector::clear() {
	m_size = 0;
	m_array = 0;
}

//--------------------------------------------------------------------------------

void Vector::pop_back() {
    if (m_size > 0) {
        --m_size;
    }
}

//--------------------------------------------------------------------------------
/*check if left = right */
bool operator==(const Vector& lhs, const Vector& rhs) {
    if (lhs.getSize() != rhs.getSize()) {
        return false;
    }

    for (std::size_t i = 0; i < lhs.getSize(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------
/*this function inserts a value in a giving possision.*/
int* Vector::insert(iterator pos, const int& val) {
    // calculate the index of the position iterator
    int index = pos - begin();

    // if the new size exceeds the current capacity, resize the array
    if (m_size + 1 > m_capacity) {
        m_capacity = (m_capacity == 0 ? 1 : m_capacity * 2);
        int* newArray = new int[m_capacity];
        // copy the elements before the insertion position
        for (int i = 0; i < index; i++) {
            newArray[i] = m_array[i];
        }
        // insert the new element
        newArray[index] = val;
        // copy the elements after the insertion position
        for (int i = index + 1; i < m_size + 1; i++) {
            newArray[i] = m_array[i - 1];
        }
        // update the size and delete the old array
        m_size++;
        delete[] m_array;
        m_array = newArray;
    }
    // if the new size doesn't exceed the current capacity, insert the element in-place
    else {
        // move the elements after the insertion position to make space for the new element
        for (int i = m_size; i > index; i--) {
            m_array[i] = m_array[i - 1];
        }
        // insert the new element
        m_array[index] = val;
        // update the size
        m_size++;
    }

    return pos;
}

//--------------------------------------------------------------------------------
/*this functions swaps between two vectors.*/
void Vector::swap(Vector& other) {
    // Swap size
    const std::size_t tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;

    // Swap capacity
    const std::size_t tempCapacity = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = tempCapacity;

    // Swap arrays
    int* const tempArray = m_array;
    m_array = other.m_array;
    other.m_array = tempArray;
}


//--------------------------------------------------------------------------------
/*tDelete element from an iterator*/
int* Vector::erase(iterator pos) {
    int* newArray = new int[m_size - 1];

    int* oldArray = m_array;
    int* newIter = newArray;

    // Copy elements before the erasure position
    for (iterator it = begin(); it != pos; ++it) {
        *newIter++ = *oldArray++;
    }

    // Skip the erased element
    ++oldArray;

    // Copy elements after the erasure position
    for (size_t i = 0; i < m_size - 1; ++i) {
        *newIter++ = *oldArray++;
    }

    // Delete old array and update object state
    delete[] m_array;
    m_array = newArray;
    m_size--;

    return pos;
}


//--------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& output, const Vector& vector)
{
    for (int i = 0; i < vector.getSize(); i++) {
        // write each element to the output stream
        output << vector[i];
        if (i < vector.getSize() - 1) {
            output << " ";
        }
    }
    return output;
}


