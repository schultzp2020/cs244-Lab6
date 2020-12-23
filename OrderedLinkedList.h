#pragma once
#include <functional>
#include "Collection.h"
#include "LinkedList.h"

template <typename T, typename C>
class OrderedLinkedList : public Collection<T>
{
public:
    OrderedLinkedList(C compare);

    // Add an item to the list.
    void add(const T& value);

    // Remove an item from the list.
    // Return true if an item was removed; false otherwise
    bool remove(const T& value);

    // Remove all items from the list.
    void clear();

    virtual unsigned int getSize() const override;

    virtual void forEach(
        const std::function<void(const T&)>& accept)
        const override;

    virtual void forEach(
        const std::function<void(T&)>& accept)
        override;
    
    template <typename T2, typename C2>
    friend std::ostream& operator << (std::ostream& out, const OrderedLinkedList<T2, C2>& orderedList);

private:
    // The underlying linked list.
    LinkedList<T> base;

    // The compare function determining the order.
    C compare;

};

template<typename T, typename C>
OrderedLinkedList<T, C>::OrderedLinkedList(C compare)
    : compare(compare)
{
}

template<typename T, typename C>
void OrderedLinkedList<T, C>::clear()
{
    base.clear();
}

template<typename T, typename C>
unsigned int OrderedLinkedList<T, C>::getSize() const
{
    return base.getSize();
}

template<typename T, typename C>
void OrderedLinkedList<T, C>::forEach(const std::function<void(const T&)>& accept) const
{
    base.forEach(accept);
}

template<typename T, typename C>
void OrderedLinkedList<T, C>::forEach(const std::function<void(T&)>& accept)
{
    base.forEach(accept);
}

template<typename T, typename C>
void OrderedLinkedList<T, C>::add(const T& value)
{
    // Add value to the front of the linked 
    // list if its smaller than current first
    if (base.getSize() == 0 || compare(value, base.getFirst()))
    {
        base.addFirst(value);
    }
    else
    {
        // Loop until the next element for the 
        // iterator isn't smaller than the value 
        // to be added
        auto i{ base.begin() };
            while (i.hasNext()
                && compare(i.peekNext(), value))
            {
                i++;
            }

        // Add the value in its place in the list
        i.addNext(value);
    }
}

template<typename T, typename C>
bool OrderedLinkedList<T, C>::remove(const T& value)
{
    // TODO implement this function.
    auto i(base.begin());

    if (*i == value)
    {
        base.removeFirst();
        return true;
    }

    while (i != base.end())
    {
        if (i.hasNext() && i.peekNext() == value)
        {
            i.removeNext();
            return true;
        }
        i++;
    }

    return false;
}

template <typename T, typename C>
std::ostream& operator << (std::ostream& out, const OrderedLinkedList<T, C>& orderedList)
{
    out << orderedList.base;
    return out;
}
