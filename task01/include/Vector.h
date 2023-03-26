#pragma once
#include <iostream>


class Vector {
public:
    using iterator = int*;

    /* constructor section */
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::size_t size = 0, int value = 0);

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    int& operator[](std::size_t index) { return m_array[index]; }
    const int& operator[](std::size_t index) const { return m_array[index]; }

    /* functions section */
    std::size_t getSize() const { return m_size; }
    std::size_t getCapacity() const { return m_capacity; }
    int* data() const;
    bool empty() const { return (m_size == 0); }
    void clear();
    void push_back(const int& value);
    void pop_back();
    void resize(std::size_t size);
    void resize(std::size_t size, const int& value);
    void swap(Vector& other);

    /* iteratots section */
    iterator begin() { return m_array; }
    iterator end() { return m_array + m_size; }
    iterator insert(iterator position, const int& value);
    iterator erase(iterator position);
    
private:
    int* m_array = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};
bool operator==(const Vector&, const Vector& rhs);
std::ostream& operator<<(std::ostream&, const Vector&);
