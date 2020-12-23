#pragma once
#include <ostream>
#include <stdexcept>
#include <functional>
#include "Collection.h"
#include "ListNode.h"

template <typename T>
class LinkedListIterator;

template <typename T>
class MutableLinkedListIterator;

// A container class for a singly-linked list
template <typename T>
class LinkedList : public Collection<T>
{
public:
    // Default constructor
    LinkedList() = default;

    // Destructor
    ~LinkedList();

    // Copy constructor (disable for now)
    LinkedList(const LinkedList<T>& original) = delete;

    // Copy assignment op (disable for now)
    LinkedList<T>& operator= (const LinkedList<T>& original) = delete;

    // Clear list without destroying container
    void clear();

    // Add node to the beginning of the list
    void addFirst(T value);

    // Add node to the end of the list
    void addLast(T value);

    // Remove node from the beginning of the list
    void removeFirst();

    // Get element at the beginning of the list
    const T& getFirst() const;

    // Get element at the beginning of the list
    T& getFirst();

    // Get element at the end of the list
    const T& getLast() const;

    // Get element at the end of the list
    T& getLast();

    // Get number of nodes in the list
    virtual unsigned int getSize() const override;

    // Start of forward iterator
    LinkedListIterator<T> begin() const;

    // End of forward iterator
    LinkedListIterator<T> end() const;

    template <typename T2>
    friend class MutableLinkedListIterator;

    // Start of forward mutable iterator
    MutableLinkedListIterator<T> begin();

    // End of forward mutable iterator
    MutableLinkedListIterator<T> end();

    // Performs the specified accept() function on each element in the collection (read-only).
    virtual void forEach(const std::function<void(const T&)>& accept) const override;

    // Performs the specified accept() function on each element in the collection, 
    // potentially making changes to elements as they’re visited.
    virtual void forEach(const std::function<void(T&)>& accept) override;

private:
    // Pointer to first node in the list
    ListNode<T>* first{ nullptr };

    // Pointer to last node in the list
    ListNode<T>* last{ nullptr };

    // Number of nodes in the list
    unsigned int size{ 0 };
};

template<typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template<typename T>
void LinkedList<T>::clear()
{
    // Keep track of the next node to delete.
    ListNode<T>* toDelete{ first };

    // Loop until toDelete == nullptr
    while (toDelete)
    {
        // Use first as temp storage
        first = toDelete->next;

        delete toDelete;

        // Advance to the next node.
        toDelete = first;
    }
    // first should now be nullptr.

    last = nullptr;
    size = 0;
}

template <typename T>
void LinkedList<T>::addFirst(T value)
{
    // Create a new node
    ListNode<T>* newNode{ new ListNode<T>() };

    // Store the new element in the new node
    newNode->value = value;

    // Link the new node to the old first node
    newNode->next = first;

    // Set the new node as the first node
    first = newNode;

    if (!last)
    {
        // If there is just one element in the 
        // list, first and last are the same.
        last = first;
    }

    size++;
}

template<typename T>
void LinkedList<T>::addLast(T value)
{
    // Create a new node.
    ListNode<T>* newNode{ new ListNode<T>() };

    // Store the element in the new node.
    newNode->value = value;

    // Link the old last node to the new node (if it exists)
    if (last)
    {
        last->next = newNode;
    }

    // Set the new node as the last node.
    last = newNode;

    // We also need to set the new node as the first node if the list was empty.
    if (!first)
    {
        first = last;
    }

    // Increment size.
    size++;
}

template<typename T>
void LinkedList<T>::removeFirst()
{
    if (first)
    {
        ListNode<T>* nodeToDelete{ first };

        // Find the second element of the list and set it as the first element.
        first = first->next;

        //	Delete the old first node.
        delete nodeToDelete;

        // Decrement size.
        size--;

        //	If the list is now empty, set last to nullptr.
        if (!first)
        {
            last = nullptr;
        }
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T const& LinkedList<T>::getFirst() const
{
    if (first)
    {
        return first->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T& LinkedList<T>::getFirst()
{
    if (first)
    {
        return first->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T const& LinkedList<T>::getLast() const
{
    if (last)
    {
        return last->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T& LinkedList<T>::getLast()
{
    if (last)
    {
        return last->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template<typename T>
unsigned int LinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
std::ostream& operator << (
    std::ostream& os, const LinkedList<T>& list)
{
    if (list.getSize() == 0)
    {
        // Special case: empty list
        os << "[]";
    }
    else
    {
        // Print opening bracket and first element
        os << "[" << list.getFirst();

        auto i{ ++list.begin() }; // Start at second element
        while (i != list.end())
        {
            // Print a comma, then the next element
            os << ", " << *i;

            // Advance iterator to the next node
            i++;
        }

        // Print closing bracket
        os << "]";
    }

    return os;
}

#include "LinkedListIterator.h"
#include "MutableLinkedListIterator.h"

template <typename T>
LinkedListIterator<T> LinkedList<T>::begin() const
{
    return LinkedListIterator<T>{first};
}

template <typename T>
LinkedListIterator<T> LinkedList<T>::end() const
{
    return LinkedListIterator<T>{nullptr};
}

template <typename T>
MutableLinkedListIterator<T> LinkedList<T>::begin()
{
    return MutableLinkedListIterator<T>{
        first, * this};
}

template <typename T>
MutableLinkedListIterator<T> LinkedList<T>::end()
{
    return MutableLinkedListIterator<T>{
        nullptr, * this};
}

template <typename T>
void LinkedList<T>::forEach(const std::function<void(const T&)>& accept) const
{
    for (const T& item : *this)
    {
        accept(item);
    }
}

template <typename T>
void LinkedList<T>::forEach(const std::function<void(T&)>& accept)
{
    for (T& item : *this)
    {
        accept(item);
    }
}
