#pragma once
#include <algorithm>
#include <ostream>
#include <string>
#include <functional>
#include "Collection.h"

template <typename T>
class ArrayList : public Collection<T>
{
public:
    // Construct an empty list
    ArrayList(unsigned int capacity);

    // Copy constructor
    ArrayList(const ArrayList<T>& original);

    // Destructor
    ~ArrayList();

    // Copy assignment operator
    ArrayList<T>& operator= (const ArrayList<T>& original);

    // Gets size of the list.
    virtual unsigned int getSize() const override;

    // Gets a single element of the list.
    // Throws an exception if index >= size.
    const T& operator[] (unsigned int index) const;

    // Gets a single, mutable element of the list.
    // Throws an exception if index >= size.
    T& operator[] (unsigned int index);

    // Adds an element to the end of the list.
    // Increases size of the list by one.
    void add(T value);

    // Removes an element from the end of the list.
    // Decreases size of the list by one.
    // Throws an exception if the list is empty.
    void remove();

    // Adds an element to the middle or beginning of the list.
    // Increases size of the list by one.
    // Throws an exception if index > size.
    void add(unsigned int index, T value);

    // Removes an element from the middle or beginning of the list.
    // Decreases size of the list by one.
    // Throws an exception if index >= size..
    void remove(unsigned int index);

    // Performs the specified accept() function on each element in the collection (read-only).
    virtual void forEach(const std::function<void(const T&)>& accept) const override;

    // Performs the specified accept() function on each element in the collection, 
    // potentially making changes to elements as they’re visited.
    virtual void forEach(const std::function<void(T&)>& accept) override;

private:
    // Pointer to the array
    T* arr;

    // Capacity of the array (amount of currently allocated space)
    unsigned int capacity;

    // Size of the list (number of entries currently being used)
    unsigned int size{ 0 };

    // Creates a new array and copies all the values in the old array over to the new one.
    void resize(unsigned int newCapacity);

    // Shifts elements to the right by one position, starting with the one at the specified index.
    void shiftRight(unsigned int index);

    // Shifts elements to the left by one position, starting with the one immediately to the right 
    // of the specified index.  The element originally at the specified index will be overwritten.
    void shiftLeft(unsigned int index);
};

template <typename T>
std::ostream& operator << (std::ostream& out, const ArrayList<T>& list)
{
    out << '[';

    if (list.getSize() > 0)
    {
        out << list[0];

        for (unsigned int i{ 1 }; i < list.getSize(); i++)
        {
            out << ", " << list[i];
        }
    }

    out << ']';

    return out;
}

template <typename T>
ArrayList<T>::ArrayList(unsigned int capacity)
    : capacity{ capacity }, arr{ new T[capacity] }
{
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    delete[] arr;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& other)
    : ArrayList{ std::max(other.capacity, 2 * other.size) }
{
    // Copy each element from the original list to 
    // the new list.
    for (unsigned int i{ 0 }; i < other.size; i++)
    {
        this->add(other.arr[i]);
    }
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator= (const ArrayList<T>& other)
{
    if (&other != this)
    {
        // Delete the previous array.
        delete[] arr;

        // Set the capacity to be considerably larger 
        // than the initial number of elements.
        capacity = std::max(other.capacity, 2 * other.size);

        // Allocate a new array with the new capacity.
        arr = new T[capacity];

        // Reset the size to zero.
        size = 0;

        // Copy each element from the original list to 
        // the new list.
        for (unsigned int i{ 0 }; i < other.size; i++)
        {
            this->add(other.arr[i]);
        }
    }

    // Return a reference to allow chain assignments.
    return *this;
}

template <typename T>
unsigned int ArrayList<T>::getSize() const
{
    return size;
}

template <typename T>
const T& ArrayList<T>::operator[] (unsigned int index) const
{
    if (index >= size)
    {
        throw std::out_of_range(
            "Index: " + std::to_string(index) +
            ", Size: " + std::to_string(size));
    }
    else
    {
        return arr[index];
    }
}

template <typename T>
T& ArrayList<T>::operator[] (unsigned int index)
{
    if (index >= size)
    {
        throw std::out_of_range(
            "Index: " + std::to_string(index) +
            ", Size: " + std::to_string(size));
    }
    else
    {
        return arr[index];
    }
}

template<typename T>
void ArrayList<T>::resize(unsigned int newCapacity)
{
    T* original{ arr };

    capacity = newCapacity;
    arr = new T[capacity];

    for (unsigned int i{ 0 }; i < size; i++)
    {
        arr[i] = original[i];
    }

    delete[] original;
}

template <typename T>
void ArrayList<T>::add(T value)
{
    if (size == capacity)
    {
        resize(2 * (size + 1));
    }

    // Store value at the next open space.
    arr[size] = value;

    // Increment the size of the list.
    size++;
}

template <typename T>
void ArrayList<T>::remove()
{
    if (size == 0)
    {
        throw std::out_of_range("Index: -1, Size: "
            + std::to_string(size));
    }
    else
    {
        size--;
    }
}

template<typename T>
void ArrayList<T>::shiftRight(unsigned int index)
{
    // Shift right
    for (int k{ static_cast<int>(size) - 1 }; k >= static_cast<int>(index); k--)
    {
        arr[k + 1] = arr[k];
    }
}

template<typename T>
void ArrayList<T>::add(unsigned int index, T value)
{
    if (index > size)
    {
        throw std::out_of_range{ "Index: " + std::to_string(index)
            + ", Size: " + std::to_string(size) };
    }

    if (size == capacity)
    {
        resize(2 * (size + 1));
    }

    shiftRight(index);

    // Store value at the requested space.
    arr[index] = value;
    size++;
}

template <typename T>
void ArrayList<T>::shiftLeft(unsigned int index)
{
    for (int k { static_cast<int>(index) }; k + 1 < static_cast<int>(size); k++)
    {
        arr[k] = arr[k + 1];
    }
}

template<typename T>
void ArrayList<T>::remove(unsigned int index)
{
    if (index > size)
    {
        throw std::out_of_range{ "Index: " + std::to_string(index)
            + ", Size: " + std::to_string(size) };
    }
    else
    {
        shiftLeft(index);
        size--;
    }
}

template <typename T>
void ArrayList<T>::forEach(const std::function<void(const T&)>& accept) const
{
    for (int i = 0; i < size; i++)
    {
        accept(arr[i]);
    }
}

template <typename T>
void ArrayList<T>::forEach(const std::function<void(T&)>& accept)
{
    for (int i = 0; i < size; i++)
    {
        accept(arr[i]);
    }
}
