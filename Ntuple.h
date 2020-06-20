
#ifndef NTUPLE_H
#define NTUPLE_H

using namespace std;

#include <iostream>
#include <string>

#include "Item.h"
#include "linkedList.h"

class Ntuple
{
	private:
		LinkedList<Item*>* mData;
		int				   mSupport;
		int				   mDatabaseIndex;

	protected:

	public:
		Ntuple();
		Ntuple(LinkedList<Item*>* &data);
		Ntuple(LinkedList<Item*>* &data, int &support);
		Ntuple(LinkedList<Item*>* &data, int &support, int &databaseIndex);

		~Ntuple();

		LinkedList<Item*>* getData();
		int                getSupport();
		int                getDatabaseIndex();

		void               setData(LinkedList<Item*>* &data);
		void			   setSupport(int &support);
		void			   setDatabaseIndex(int &databaseIndex);
		void			   increaseSupport(int additionalSupport);
};

#endif