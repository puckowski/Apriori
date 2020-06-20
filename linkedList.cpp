#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "linkedList.h"


template <class T>
LinkedList<T>::LinkedList()
{
    mHead = NULL;
    mTail = NULL;

    mCount = 0;
}


template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T> *tempNode, *toBeDeleted;

    tempNode = mHead;

    while(tempNode != NULL)
    {
        toBeDeleted = tempNode;
        tempNode = tempNode->mNext;
        toBeDeleted->mNext = NULL;

        delete toBeDeleted;
    }

    mHead = NULL;
    mTail = NULL;
	mCount = 0;
}


template <class T>
int LinkedList<T>::getCount()
{
    return mCount;
}


template <class T>
T LinkedList<T>::getData(int index)
{
	if(index > (mCount - 1))
	{
		return NULL;
	}

    Node<T> *tempNode = NULL; 
	
    tempNode = mHead;
    for(int i = 0; i < index; i++)
    {
        tempNode = tempNode->mNext;
    }

    return tempNode->mData;
}


template <class T>
T LinkedList<T>::setData(int index, T data)
{
	if(index > (mCount - 1))
	{
		return NULL;
	}

    Node<T> *tempNode = NULL;

    tempNode = mHead;
    for(int i = 0; i < index; i++)
	{
        tempNode = tempNode->mNext;
	}

    tempNode->mData = data;

	return data;
}


template <class T>
void LinkedList<T>::clear()
{
    while(mCount > 0)
	{
		removeElementAt(0);
	}

    mHead = NULL;
    mTail = NULL;
    mCount = 0;
}


template <class T>
void LinkedList<T>::display()
{
    Node<T> *tempNode;

    if(mHead == NULL)
    {
        cout << "The list is empty. " << endl;
    
		return;
    }

    tempNode = mHead;
    while(tempNode != NULL)
    {
        cout << tempNode->mData;
		cout << " ";
        tempNode = tempNode->mNext;
    }

    cout << endl;
}


template <class T>
int LinkedList<T>::getIndex(T searchData)
{
	int midpoint = 0, minimum = 0, maximum = (mCount - 1);

	while(found == false && minimum <= maximum)
	{
		int midpoint = (minimum + maximum) / 2;

		if(getData(midpoint) == searchData)
		{
			found = true;
		}
		else if(getData(midpoint) < searchData)
		{
			minimum = (midpoint + 1);
		}
		else if(getData(midpoint) > searchData)
		{
			maximum = (midpoint - 1);
		}
	}

	return midpoint;
}


template <class T>
T LinkedList<T>::getHead()
{
	return mHead;
}


template <class T>
T LinkedList<T>::getTail()
{
	return mTail;
}


template <class T>
void LinkedList<T>::insert(T newData)
{
    Node<T> *tempNode = NULL, *newNode = NULL, *oneBefore = NULL;

    newNode = new Node<T>(newData);

    if(mHead == NULL)
    {
        mHead = newNode;
        mTail = newNode;
    }
    else
    {
		if(newData <= mHead->mData)
        {
            newNode->mNext = mHead;
            mHead = newNode;
        }
        else if(newData >= mTail->mData)
        {
            mTail->mNext = newNode;
            mTail = newNode;
        }
        else
        {
            tempNode = mHead;
            while(tempNode->mData < newData)
            {
                oneBefore = tempNode;
                tempNode = tempNode->mNext;
            }

            newNode->mNext = tempNode;
            oneBefore->mNext = newNode;
        }
    }

    mCount++;
}


template <class T>
bool LinkedList<T>::isEmpty()
{
    return (mHead == NULL);
}


template <class T>
bool LinkedList<T>::isExist(T searchData)
{
    bool found = false;
	int minimum = 0, maximum = (mCount - 1);

	while(found == false && minimum <= maximum)
	{
		int midpoint = (minimum + maximum) / 2;

		if(getData(midpoint) == searchData)
		{
			found = true;
		}
		else if(getData(midpoint) < searchData)
		{
			minimum = (midpoint + 1);
		}
		else if(getData(midpoint) > searchData)
		{
			maximum = (midpoint - 1);
		}
	}

    return found;
}


template <class T>
T LinkedList<T>::removeElementAt(int index)
{
	if(index < 0 || index >= mCount)
	{
		return NULL;
	}
	
    Node<T>  *tempNode = NULL, *oneBefore = NULL, *toBeDeleted = NULL;
    T        data = NULL;
	int      j = 0;
    bool     found = false;

    if(isEmpty() == false)
    {
        if(index == 0)
        {
            toBeDeleted = mHead;
            mHead = mHead->mNext;
            toBeDeleted->mNext = NULL;
        }
        else if(index == (mCount - 1))
        {
            toBeDeleted = mTail;
            for(oneBefore = mHead, j = 0; j < (index - 1); j++)
			{
                oneBefore = oneBefore->mNext;
			}

            oneBefore->mNext = NULL;
            mTail = oneBefore;
        }
        else
        {
            tempNode = mHead;
            for(j = 0; j < index; j++)
            {
                oneBefore = tempNode;
                tempNode = tempNode->mNext;
            }

            toBeDeleted = tempNode;
            oneBefore->mNext = tempNode->mNext;
            toBeDeleted->mNext = NULL;
        }

        data = toBeDeleted->mData;
		
        delete toBeDeleted;
		
        mCount--;
    }

    return data;
}

#endif