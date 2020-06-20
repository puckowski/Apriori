
#include "Ntuple.h"
#include "linkedList.cpp"

using namespace std;

Ntuple::Ntuple()
{
	mData = new LinkedList<Item*>();

	mSupport = 1;
	mDatabaseIndex = -1;
}

Ntuple::Ntuple(LinkedList<Item*>* &data)
{
	mData = data;

	mSupport = 1;
	mDatabaseIndex = -1;
}

Ntuple::Ntuple(LinkedList<Item*>* &data, int &support)
{
	mData = data;

	mSupport = support;
	mDatabaseIndex = -1;
}

Ntuple::Ntuple(LinkedList<Item*>* &data, int &support, int &databaseIndex)
{
	mData = data;

	mSupport = support;
	mDatabaseIndex = databaseIndex;
}

Ntuple::~Ntuple()
{
	mData->clear();

	delete mData;
}

LinkedList<Item*>* Ntuple::getData()
{
	return mData;
}

int Ntuple::getSupport()
{
	return mSupport;
}

int Ntuple::getDatabaseIndex()
{
	return mDatabaseIndex;
}

void Ntuple::setData(LinkedList<Item*>* &data)
{
	mData->clear();

	mData = data;
}

void Ntuple::setSupport(int &support)
{
	mSupport = support;
}

void Ntuple::setDatabaseIndex(int &databaseIndex)
{
	mDatabaseIndex = databaseIndex;
}

void Ntuple::increaseSupport(int additionalSupport)
{
	mSupport += additionalSupport;
}
