
#include "Item.h"

using namespace std;

Item::Item()
{
	mData = "";
	mSupport = 1;
}

Item::Item(string &data)
{
	mData = data;
	mSupport = 1;
}

Item::Item(string &data, int &support)
{
	mData = data;
	mSupport = support;
}

string Item::getData()
{
	return mData;
}

int Item::getSupport()
{
	return mSupport;
}

void Item::setData(string &data)
{
	mData = data;
}

void Item::setSupport(int &support)
{
	mSupport = support;
}

void Item::increaseSupport()
{
	mSupport++;
}

void Item::increaseSupport(int additionalSupport)
{
	mSupport += additionalSupport;
}