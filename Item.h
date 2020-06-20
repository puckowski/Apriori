
#ifndef ITEM_H
#define ITEM_H

using namespace std;

#include <iostream>
#include <string>

class Item
{
	private:
		string mData;
		int    mSupport;

	protected:

	public:
		Item();
		Item(string &data);
		Item(string &data, int &support);

		string getData();
		int    getSupport();

		void   setData(string &data);
		void   setSupport(int &support);
		void   increaseSupport();
		void   increaseSupport(int additionalSupport);
};

#endif