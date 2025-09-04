#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <string>
#include <new>
#include <stdexcept>
#include <initializer_list>

template<typename T>
class MyVector {
public:
    MyVector();
    MyVector(size_t initial_length);
    MyVector(size_t initial_length, const T& default_item);
    MyVector(std::initializer_list<T> init_list);

    ~MyVector();
    
    void add(const T& item);
    T& get(long index);
    void set(long index, const T& item);

    inline T& front() {
        return get(0);
    }

    inline T& back() {
        return get(-1);
    }

    size_t size() const;
    size_t capacity() const;

    class Iterator;
    Iterator begin() const;
    Iterator end() const;

    T& operator[](long index);
    bool operator==(const MyVector& other);
    MyVector operator+(const MyVector& other);

private:
    // Helper to check if T is streamable
    template<typename T, typename = void>
    struct is_streamable : std::false_type {};

    template<typename T>
    struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>> : std::true_type {};

public:
    // Overload of operator<< for MyVector
    template<typename T>
    friend std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec) {
        if constexpr (is_streamable<T>::value) {
            os << '[';
            bool first = true;
            for (auto it = vec.begin(); it != vec.end(); ++it) {
                if (!first) {
                    os << ", ";
                }
                os << *it;
                first = false;
            }
            os << ']';
        }
        else {
            os << "[unprintable elements]";
        }
        return os;
    }

private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void reallocate(size_t new_size);
    static size_t next_power_of_two(size_t value);
};

template<typename T>
size_t MyVector<T>::next_power_of_two(size_t value) {
    if (value <= 0) return 1;
    size_t res = 1;
    while (res < value) {
        res <<= 1; // double the value
    }
    return res;
}

template<typename T>
void MyVector<T>::reallocate(size_t new_capacity) {
    new_capacity = next_power_of_two(new_capacity); // ensure the new capacity is a power of two

    T* new_data = new T[new_capacity];
    if (new_data == nullptr) {
        throw std::bad_alloc();
    }
    
    for (size_t i = 0; i < m_size; i++) {
        new_data[i] = m_data[i];
    }
    
    delete[] m_data;

    m_data = new_data;
    m_capacity = new_capacity;
}

template<typename T>
MyVector<T>::MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {
    reallocate(2);
}

template<typename T>
MyVector<T>::MyVector(size_t initial_length) : m_data(nullptr), m_size(0), m_capacity(initial_length) {
    if (initial_length > 0) {
        reallocate(initial_length);
    }
    else {
        m_data = nullptr;
    }

    m_size = initial_length;

    for (size_t i = 0; i < m_size; i++) {
        m_data[i] = T();
    }
}

template<typename T>
MyVector<T>::MyVector(size_t initial_length, const T& default_item) : m_data(nullptr), m_size(0), m_capacity(initial_length) {
    if (initial_length > 0) {
        reallocate(initial_length);
    }

    m_size = initial_length;

    for (size_t i = 0; i < m_size; i++) {
        m_data[i] = default_item;
    }
}

template<typename T>
MyVector<T>::~MyVector() {
    delete[] m_data;
}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> init_list) : m_data(nullptr), m_size(0), m_capacity(0) {
    for (auto it = init_list.begin(); it != init_list.end(); it++) {
        add(*it);
    }
}

template<typename T>
void MyVector<T>::add(const T& item) {
    if (m_size == m_capacity) {
        reallocate(m_capacity * 2);
    }
    m_data[m_size++] = item;
}

template<typename T>
T& MyVector<T>::get(long index) {
    long new_index = index;
    if (new_index < 0) {
        new_index = m_size + new_index;
    }
    if (new_index < 0 || static_cast<size_t>(new_index) >= m_size) {
        std::string error_message =
            "Vector index " + std::to_string(index) +
            " out of range for length " + std::to_string(m_size);
        std::cerr << error_message << '\n';
        throw std::out_of_range(error_message);
    }
    return m_data[new_index];
}

template<typename T>
void MyVector<T>::set(long index, const T& item) {
    long new_index = index;
    if (new_index < 0) {
        new_index = m_size + new_index;
    }
    if (new_index < 0 || static_cast<size_t>(new_index) >= m_size) {
        std::string error_message =
            "Vector index " + std::to_string(index) + 
            " out of range for length " + std::to_string(m_size);
        std::cerr << error_message << '\n';
        throw std::out_of_range(error_message);
    }
    m_data[new_index] = item;
}

template<typename T>
size_t MyVector<T>::size() const {
    return m_size;
}

template<typename T>
size_t MyVector<T>::capacity() const {
    return m_capacity;
}

template<typename T>
T& MyVector<T>::operator[](long index) {
    return get(index);
}

template<typename T>
bool MyVector<T>::operator==(const MyVector<T>& other) {
    if (this->m_size != other.m_size) {
        return false;
    }
    for (int i = 0; i < m_size; i++) {
        if (this->m_data[i] != other.m_data[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
MyVector<T> MyVector<T>::operator+(const MyVector<T>& other) {
    MyVector<T> res;
    for (auto it = begin(); it != end(); it++) {
        res.add(*it);
    }
    for (auto it = other.begin(); it != other.end(); it++) {
        res.add(*it);
    }
    return res;
}

// Iterator stuff
template<typename T>
class MyVector<T>::Iterator {
private:
    T* ptr;
    T* begin;
    T* end;
public:

    Iterator(T* ptr, T* begin, T* end) : ptr(ptr), begin(begin), end(end) {}

    T& operator*() const {
        if (ptr < begin || ptr >= end) {
            throw std::out_of_range("Iterator out of bounds");
        }
        return *ptr;
    }

    T* operator->() const {
        if (ptr < begin || ptr >= end) {
            throw std::out_of_range("Iterator out of bounds");
        }
        return ptr;
    }

    // prefix
    Iterator& operator++() {
        ++ptr;
        return *this;
    }

    // postfix
    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    // prefix
    Iterator& operator--() {
        --ptr;
        return *this;
    }

    // postfix
    Iterator operator--(int) {
        Iterator temp = *this;
        --(*this);
        return temp;
    }

    Iterator& operator+=(std::ptrdiff_t n) {
        ptr += n;
        return *this;
    }

    Iterator& operator-=(std::ptrdiff_t n) {
        ptr -= n;
        return *this;
    }

    Iterator operator+(std::ptrdiff_t n) const {
        return Iterator(ptr + n, begin, end);
    }

    Iterator operator-(std::ptrdiff_t n) const {
        return Iterator(ptr - n, begin, end);
    }

    std::ptrdiff_t operator-(const Iterator& other) const {
        return ptr - other.ptr;
    }

    bool operator==(const Iterator& other) const { return ptr == other.ptr; }
    bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    bool operator<(const Iterator& other) const { return ptr < other.ptr; }
    bool operator>(const Iterator& other) const { return ptr > other.ptr; }
    bool operator<=(const Iterator& other) const { return ptr <= other.ptr; }
    bool operator>=(const Iterator& other) const { return ptr >= other.ptr; }
};

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() const {
    return Iterator(m_data, m_data, m_data + m_size);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() const {
    return Iterator(m_data + m_size, m_data, m_data + m_size);
}

#endif // MYVECTOR_H
