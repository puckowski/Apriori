
#ifndef NODE_H
#define NODE_H

using namespace std;

//NODE TEMPLATE
template <class T>
struct Node
{
    T        mData;
    Node<T>  *mNext;

    Node()
	{
		mData = T();
		mNext = NULL;
	}

    Node(T data)
	{
		mData = data;
		mNext = NULL;
	}

	Node(T data, Node next)
	{
		mData = data;
		mNext = next;
	}
};

#endif