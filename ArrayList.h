//
//  ArrayList.hpp
//  HW5
//
//  Created by Kemba Konteh on 11/26/19.
//  Copyright © 2019 Kemba Konteh. All rights reserved.
//
#include "listInterface.h"

#ifndef ArrayList_hpp
#define ArrayList_hpp
#include <iostream>
#include <cstring>
using namespace std;

/* Array list class inheriting from the list interface class */
template < class TYPE>
class ArrayList : public listInterface<TYPE> {

private:
    int static const DEFAULT_CAPACITY = 100;
    int maxLength = 0;
    int currentLength = 0;
    TYPE* items;

    void growArray();

public:
    // static variables
    static int accessCount;
    static int swapCount;
    static int removeAtCount;
    static int insertAtCount;
    static int appendAt;


    // Default constructor
    ArrayList();

    // parameterized constructor, takes size.
    ArrayList(int size);

    // overloaded constructor
    ArrayList(int size, int maxLength);

    // Copy constructor
    ArrayList(const ArrayList<TYPE> &item);

    // Destructor
    ~ArrayList ();

    // The easy way to access an element
    TYPE & operator[] ( int ) const  throw (std::out_of_range);

    // Tells if it is empty
    bool isEmpty() const;

    // Return the number of elements in the list
    int getSize() const ;

    // Inserts at the location.
    void insertAt( int index, const TYPE & newEntry)
    throw ( std::out_of_range);

    // delete at location
    void removeAt ( int index) throw ( std::out_of_range);

    // Append to end
    void append( const TYPE &);

    // swaps two given numbers
    void swap( int from, int to) throw( std::out_of_range);

    // Get an item at location
    TYPE & getAt( int index) const throw ( std::out_of_range);

    // gets the current length
    int getCurrentLength();

    // gets the max length
    int getMaxLength();

    // Clear everything
    void clearAll();


    // Clear out any instrumentation
    void clearStatistics();

    // Provide statistics on number of times method was performed
    int getNumAccess() const;    // operator [] OR getAt
    int getNumSwap() const;
    int getNumRemove() const;
    int getNumInsertAt() const;
    int getNumAppends() const;

    // assignment operator
    TYPE & operator=( const TYPE &other) ;




};

/* Implementation of the array list class begins here. I chose to do the implementation with the class instead of a
 separate class.

 Access count initialized to zero
 */
template <class TYPE>
int ArrayList<TYPE>::accessCount = 0;

/* Swap count initialized to zero  */
template <class TYPE>
int ArrayList<TYPE>::swapCount = 0;

/*  Remove count initialized to zero  */
template <class TYPE>
int ArrayList<TYPE>::removeAtCount = 0;

/* Insert at count initialized to zero  */
template <class TYPE>
int ArrayList<TYPE>::insertAtCount = 0;

/* Append at initialized to zero */
template <class TYPE>
int ArrayList<TYPE>::appendAt = 0;

/* Default constrcutor*/
template <class TYPE>
ArrayList<TYPE>::ArrayList()
{
    items = new TYPE[DEFAULT_CAPACITY];
    maxLength = DEFAULT_CAPACITY;
}

/* Destructor */
template <class TYPE>
ArrayList<TYPE>::~ArrayList()
{
    delete [] items;
    items = nullptr;

}



/* parameterized constructor */
template <class TYPE>
ArrayList<TYPE>::ArrayList(int size)
{
    maxLength = size;
    currentLength = 0;
    items = new TYPE[size]; // creates a new array of size 10
}

/* overloaded constructor */
template <class TYPE>
ArrayList<TYPE>::ArrayList(int size, int max)
{
    maxLength = size;
    currentLength = 0;
    this->maxLength = max;
}

/* Assignment operator */
template <class TYPE>
TYPE & ArrayList<TYPE>::operator=(const TYPE &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->currentLength = other.currentLength;
    this->maxLength = other.maxLength;
    items = new TYPE[other.maxLength];
    for(int i = 0; i< currentLength; i++)
    {
        items[i] = other.items[i];
    }
    return *this;
}


/* Copy constructor */
template <class TYPE>
ArrayList<TYPE>::ArrayList(const ArrayList<TYPE> &item)
{
    this->currentLength = item.currentLength;
    this->maxLength = item.maxLength;
    items = new TYPE[item.maxLength];
    for (int i = 0; i< currentLength; i++)
    {
        items[i] = item.items[i];
    }
}


/* Method adds to the end of the list. Makes use of the grow array method  */
template <class TYPE>
void ArrayList<TYPE>::append(const TYPE &newEntry)
{
    if (currentLength == maxLength - 1)
    {
        growArray();
    }
    items[currentLength++] = newEntry;
    appendAt++;
}


/* Method to swap the given data */

template <class TYPE>
void ArrayList<TYPE>::swap( int from, int to)
throw( std::out_of_range)
{
    if (from < 0 || to >= currentLength || from >= currentLength || to < 0)
    {
        throw std::out_of_range("Index out of bound");
    }
    TYPE temp = items[from];
    items[from] = items[to];
    items[to] = temp;
    swapCount++;
}


/* Method to get an element at a location by index. Throws an exception if the index is out of bound. */
template <class TYPE>
TYPE & ArrayList<TYPE>::getAt( int index) const
throw ( std::out_of_range)
{
    if (index < 0 || index > currentLength - 1)
    {
        throw std::out_of_range("Index out of bound!");
    }
    accessCount++;
    return items[index];

}

/* gets the current length */
template <class TYPE>
int ArrayList<TYPE>::getCurrentLength()
{
    return currentLength;
}

/* Gets the max length */
template <class TYPE>
int ArrayList<TYPE>::getMaxLength()
{
    return maxLength;
}


/* Method to clear everything in the list  */
template <class TYPE>
void ArrayList<TYPE>::clearAll()
{
    this->currentLength = 0;
    //maxLength = 2;
    delete [] this->items;
    this->items = new TYPE[0];
    //*items = new TYPE[maxLength];
    //items = 0;
}


/* Method to clear out any instrumentation */
template <class TYPE>
void ArrayList<TYPE>:: clearStatistics()
{
    accessCount = 0;
    swapCount = 0 ;
    removeAtCount = 0;
    insertAtCount = 0;
    appendAt = 0;

}


/* Method to grow or resize the array */
template <class TYPE>
void ArrayList<TYPE>::growArray()
{
    TYPE * newItems = new TYPE[maxLength * 2];
    memcpy(newItems, items, maxLength * sizeof(TYPE));
    maxLength *= 2;
    delete [] items;
    items = newItems;
}


/* Method to insert at a given location. Makes use of the grow array method. */
template <class TYPE>
void ArrayList<TYPE>::insertAt(int newPosition , const TYPE &newEntry)
throw(std::out_of_range)
{
    if (newPosition > currentLength || newPosition < 0)
    {
        throw std::out_of_range("Invalid index on insert");
    }
    if(currentLength == maxLength)
    {
        growArray();
    }

    for (int i = currentLength - 1; i >= newPosition; i--)
    {
        items[i+1] = items[i];
    }
    items[newPosition] = newEntry;
    currentLength++;
    insertAtCount++;
}


/* Method that deletes at a given location. */
template <class TYPE>
void ArrayList<TYPE>::removeAt(int index)
throw(std::out_of_range)
{
    if (index < 0 || index > currentLength - 1)
    {
        throw std::out_of_range("Index out of bound!");
    }

    for (int i = index; i< currentLength; i++)
    {
        items[i] = items[i+1];
    }
    //items[maxLength-1] = nullptr;
    //maxLength--;
    currentLength--;
    removeAtCount++;
}


/*  Method to easily access an element. Throws an exception if array is out of bound. */
template <class TYPE>
TYPE & ArrayList<TYPE>::operator[] ( int index) const
throw (std::out_of_range)
{
    if(index < 0 || index >= currentLength)
    {
        throw std::out_of_range("Array index out of bound, exiting!");
    }
    accessCount++;
    return items[index];

}

/* Method to check if empty */
template <class TYPE>
bool ArrayList<TYPE>::isEmpty() const
{
    return currentLength == 0;
}


/* Method to get the size of the list */
template <class TYPE>
int ArrayList<TYPE>::getSize() const
{
    return currentLength;
}


/* Method to to get the number of times a number was accessed.*/
template <class TYPE>
int ArrayList<TYPE>::getNumAccess() const
{
    return accessCount;
}


/* Method to get the numbers  swapped */
template <class TYPE>
int ArrayList<TYPE>::getNumSwap() const
{
    return swapCount;
}

/* Method to get the number removed */
template <class TYPE>
int ArrayList<TYPE>::getNumRemove() const
{
    return removeAtCount;
}


/* Method to get the number inserted at a given */
template <class TYPE>
int ArrayList<TYPE>::getNumInsertAt() const
{
    return  insertAtCount;

}


/* Method to get the appended number */
template <class TYPE>
int ArrayList<TYPE>::getNumAppends() const
{
    return appendAt;
}

#endif /* ArrayList_hpp */
