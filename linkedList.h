
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

#include "node.h"

using namespace std;

const int LINKED_LIST_NOT_FOUND = -1;

//LINKEDLIST TEMPLATE
template <class T>
class LinkedList
{
    private:
		Node<T>  *mHead;
	    Node<T>  *mTail;

        int      mCount;

    protected:

    public:
		//CONSTRUCTOR
        LinkedList();

		//DESTRUCTOR (DECONSTRUCTOR)
        ~LinkedList();

		T        getHead();
		T        getTail();
        T        getData(int index);
		T        setData(int index, T data);
        T        removeElementAt(int index);

		int      getCount();
		int      getIndex(T searchData);   

        void     clear();
        void     display();        		
        void     insert(T data);

        bool     isEmpty();
        bool     isExist(T searchData);
};

#endif