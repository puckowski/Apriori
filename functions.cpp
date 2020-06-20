
#include "functions.h"
#include "linkedList.cpp"

using namespace std;

bool mVerboseOutput;

void print(int number)
{
	if(mVerboseOutput == true)
	{
		cout << number;
	}
}

void print(double number)
{
	if(mVerboseOutput == true)
	{
		cout << number;
	}
}

void print(string output)
{
	if(mVerboseOutput == true)
	{
		cout << output;
	}
}

void println(string output)
{
	if(mVerboseOutput == true)
	{
		cout << output << endl;
	}
}

void waitForUser()
{
	cout << "Press enter to continue... ";

	string foo;
	getline(cin, foo);
}

void promptForVerboseOutput()
{
	while(true)
	{
		cout << "Do you want to run program with verbose output (\"y\" or \"n\")? ";
		
		string input;
		getline(cin, input);

		if(input == "y")
		{
			mVerboseOutput = true;

			break;
		}
		else if(input == "n")
		{
			mVerboseOutput = false;

			break;
		}
		else
		{
			cout << "Sorry! Invalid input. " << endl;
		}
	}
}

void printProgramInfo()
{
	cout << "Daniel Puckowski's Apriori Implementation | Historic Data Mining Algorithm " << endl;
	cout << "Program version: " << PROGRAM_VERSION_NUMBER << ". " << endl;
}

void run()
{
	printProgramInfo();

	bool isRunning = true;

	while(isRunning == true)
	{
		printProgramMenu();

		int executionChoice = getMenuChoice();

		switch(executionChoice)
		{
			case 1:
				normalRun();

				break;
			case 2:
				isRunning = false;

				break;
			default:
				cout << "Sorry! That is an invalid menu choice. Try again. " << endl;
		}
	}

	cout << "Program execution complete. " << endl;

	waitForUser();
}

void printProgramMenu()
{
	cout << "Program execution options: " << endl;
	cout << endl;

	cout << "[1] Normal run. " << endl;
	cout << "Specify the database filename and the support level to run Apriori with. " << endl;

	cout << "[2] End program. " << endl;

	cout << endl;
}

int getMenuChoice()
{
	int menuChoice = -1;

	cout << "Enter menu choice: ";

	string inputString;
	getline(cin, inputString);

	istringstream iss(inputString);
	iss >> menuChoice;

	return menuChoice;
}

bool normalRun()
{
	cout << "Enter \"-1\" (in support prompt) or \"exit\" (in database filename prompt) to return to program menu. " << endl;

	double supportPercentage = getSupportPercentage();
		
	if(supportPercentage == -1)
	{
		return false;
	}

	string databaseFilename = getDatabaseFilename();

	if(databaseFilename == "exit")
	{
		return false;
	}

	promptForVerboseOutput();

	int numberOfElements = 0;

	LinkedList<Ntuple*> database = LinkedList<Ntuple*>();

	if(readDatabaseFile(databaseFilename, database, numberOfElements) == false)
	{
		return false;
	}

	//printDatabase(database);

	LinkedList<Ntuple*> ntuples = LinkedList<Ntuple*>();
	int tupleSize = 2;

	while(getAllNtuplesWithSupport(database, tupleSize, ntuples) == true)
	{   
		cout << "Finding supported n-tuples of size: " << tupleSize << ". " << endl;

		removeUnsupportedNtuples(ntuples, supportPercentage);

		cout << "Done finding supported n-tuples of size: " << tupleSize << ". " << endl;

		if(ntuples.getCount() == 0)
		{
			break;
		}
		else
		{
			printSupportedNtuples(ntuples);
		}
		
		tupleSize++;

		clearIrrelevantItems(database, ntuples);
		clearList(ntuples);

		waitForUser();
	}

	cout << "Done finding all associations in database. " << endl;

	clearList(database);
	
	waitForUser();

	return true;
}

void printSupportedNtuples(LinkedList<Ntuple*> &ntuples)
{
	cout << "Supported n-tuples: " << endl;

	for(int i = 0; i < ntuples.getCount(); i++)
	{
		cout << "N-tuple " << (i + 1) << ": { ";

		for(int n = 0; n < ntuples.getData(i)->getData()->getCount(); n++)
		{
			cout << ntuples.getData(i)->getData()->getData(n)->getData();
			
			if(n != (ntuples.getData(i)->getData()->getCount() - 1))
			{
				cout << ", ";
			}
		}

		cout << " } (Support: " << ntuples.getData(i)->getSupport() << ") ";

		cout << endl;
	}
}

void clearList(LinkedList<Ntuple*> &list)
{
	//cout << "Clearing linkedlist. " << endl;
	println("Clearing linkedlist. ");

	for(int i = 0; i < list.getCount(); i++)
	{
		list.getData(i)->getData()->clear();
	}

	list.clear();

	//cout << "Done clearing linkedlist. " << endl;
	println("Done clearing linkedlist. ");
}

void printValidSupportLevels()
{
	cout << "Valid support levels are: " << endl;

	for(int i = 1; i < NUM_SUPPORT_LEVELS; i++)
	{
		cout << SUPPORT_LEVELS[i] << " ";
	}

	cout << endl;
}

void printDatabase(LinkedList<Ntuple*> &database)
{
	cout << "Database: " << endl;

	for(int i = 0; i < database.getCount(); i++)
	{
		cout << "Item set " << (i + 1) << ": ";

		for(int n = 0; n < database.getData(i)->getData()->getCount(); n++)
		{
			cout << database.getData(i)->getData()->getData(n)->getData() << " (" << database.getData(i)->getSupport() << ") ";
		}

		cout << endl;
	}

	cout << endl;
}

bool isValidSupportLevel(double &supportPercentage)
{
	for(int i = 0; i < NUM_SUPPORT_LEVELS; i++)
	{
		if(SUPPORT_LEVELS[i] == supportPercentage)
		{
			return true;
		}
	}

	return false;
}

double getSupportPercentage()
{
	double supportPercentage = 100.00;

	while(true)
	{
		cout << "Enter support level to run Apriori with: ";

		string inputLevelString;
		getline(cin, inputLevelString);

		istringstream iss(inputLevelString);
		iss >> supportPercentage;

		if(isValidSupportLevel(supportPercentage) == false)
		{
			cout << "Sorry! That is not a valid support level! " << endl;
			printValidSupportLevels();

			continue; 
		}
		else
		{
			break;
		}
	}

	return supportPercentage;
}

bool isSupported(double &supportPercentage, int &tupleSupport, int &numberOfTuples)
{
	//cout << "Calculating support for a n-tuple. " << endl;

	double tupleSupportPercentage = ((double) tupleSupport / (double) numberOfTuples);
	tupleSupportPercentage *= 100.0;

	if(tupleSupportPercentage > supportPercentage)
	{
		return true;
	}
	else
	{
		return false;
	}
}

string getDatabaseFilename()
{
	cout << "Please enter the name of the database file to run Apriori on: ";

	string databaseName;
	getline(cin, databaseName);

	return databaseName;
}

bool readDatabaseFile(string &databaseFileName, LinkedList<Ntuple*> &database, int &numberOfElements)
{
	cout << "Reading database file. " << endl;

	ifstream databaseFile(databaseFileName);
	string   nextLine = "";

	int      elementCount = 0;

	if(databaseFile.is_open())
	{
		while(getline(databaseFile, nextLine))
		{
			Ntuple* itemSet = new Ntuple();
			stringstream      sstream(nextLine);
			string            word = "";

			while(getline(sstream, word, ' ')) 
			{
				Item* item = new Item(word);

				itemSet->getData()->insert(item);

				elementCount++;
			}

			database.insert(itemSet);
		}

		databaseFile.close();
	}
	else
	{
		cout << "Couldn't open database file \"" + databaseFileName + "\" for reading. Aborting... " << endl; 

		return false;
	}

	cout << "Done reading database file. " << endl;

	return true;
}

bool getAllNtuplesWithSupport(LinkedList<Ntuple*> &database, int &tupleSize, LinkedList<Ntuple*> &ntuples)
{
	cout << "Getting all n-tuple combinations in database of size: " << tupleSize << ". " << endl;

	for(int i = 0; i < database.getCount(); i++)
	{
		double percentTaskComplete = (((double) i) / ((double) database.getCount()));
		percentTaskComplete *= 100;
		
		print(percentTaskComplete); 
		print("% of task completed. Processing transaction number ");
		print((i + 1));
		print(" of ");
		print((database.getCount() + 1));
		println(". ");

		LinkedList<Ntuple*> itemSetCombinations = LinkedList<Ntuple*>();
		Ntuple* itemSet = database.getData(i);

		if(getNtuples(itemSet, tupleSize, i, itemSetCombinations) == true)
		{
			for(int n = 0; n < itemSetCombinations.getCount(); n++)
			{
				itemSet = itemSetCombinations.getData(n);

				int existingIndex = checkNtupleForMatch(itemSet, ntuples);
				
				if(existingIndex != -1)
				{
					Ntuple* existingSet = ntuples.getData(existingIndex);
					existingSet->increaseSupport(1);

					ntuples.setData(existingIndex, existingSet);
				}
				else
				{
					ntuples.insert(itemSet);
				}
			}
		}
	}

	if(ntuples.getCount() > 0)
	{
		cout << "Done getting combinations from database. " << endl;

		return true;
	}
	else
	{
		cout << "Done getting combinations from database (with 0 results found). " << endl;

		return false;
	}
}

bool getNtuples(Ntuple* &itemSet, int &tupleSize, int &databaseIndex, LinkedList<Ntuple*> &ntuples)
{
	//cout << "Getting all n-tuple combinations from item set of size: " << tupleSize << ". " << endl;
	print("Getting all n-tuple combinations from item set of size: ");
	print(tupleSize);
	println(". ");

	if(tupleSize < itemSet->getData()->getCount())
	{
		int n = 0;

		for(int t = 0; t < (itemSet->getData()->getCount() - (tupleSize - 1)); t++)
		{
			for(int i = t; i < (itemSet->getData()->getCount() - (tupleSize - 1)); i++)
			{
				Ntuple* combinationList = new Ntuple();

				while(n < tupleSize)
				{
					combinationList->getData()->insert(itemSet->getData()->getData(i));
				
					n++;
					i++;
				}

				combinationList->setDatabaseIndex(databaseIndex);
				
				ntuples.insert(combinationList);

				n = 0;
				i -= tupleSize; 
			}
		}
	}
	else if(tupleSize == itemSet->getData()->getCount())
	{
		Ntuple* combinationList = new Ntuple();

		for(int i = 0; i < itemSet->getData()->getCount(); i++)
		{
			Item* item = new Item(itemSet->getData()->getData(i)->getData());

			combinationList->getData()->insert(item);
		}

		combinationList->setDatabaseIndex(databaseIndex);

		ntuples.insert(combinationList);
	}
	
	if(ntuples.getCount() > 0)
	{
		//cout << "Done getting combinations from item set. " << endl;
		println("Done getting combinations from item set. ");

		return true;
	}
	else
	{
		//cout << "Done getting combinations from item set (with 0 results found). " << endl;
		println("Done getting combinations from item set (with 0 results found). ");

		return false;
	}
}

int checkNtupleForMatch(Ntuple* &ntuple, LinkedList<Ntuple*> &ntuples)
{
	//cout << "Checking n-tuple for a match. " << endl;
	println("Checking n-tuple for a match. ");

	for(int t = 0; t < ntuples.getCount(); t++)
	{
		Ntuple* existingCombination = ntuples.getData(t);

		bool listsMatch = true;

		if(existingCombination->getData()->getCount() == ntuple->getData()->getCount())
		{
			for(int k = 0; k < existingCombination->getData()->getCount(); k++)
			{
				if((ntuple->getData()->getData(k) == existingCombination->getData()->getData(k)) == false)
				{
					listsMatch = false;

					break;
				}
			}

			if(listsMatch == true)
			{
				//cout << "Found a match. " << endl;
				println("Found a match. ");

				return t;
			}
		}
	}

	//cout << "Done checking for a match. " << endl;
	println("Done checking for a match. ");

	return -1;
}

void removeUnsupportedNtuples(LinkedList<Ntuple*> &ntuples, double &supportPercentage) 
{
	//cout << "Removing unsupported n-tuples. " << endl;
	println("Removing unsupported n-tuples. ");

	int ntupleTotal = ntuples.getCount();

	for(int i = 0; i < ntuples.getCount(); i++)
	{
		int ntupleSupport = ntuples.getData(i)->getSupport();
		
		if(isSupported(supportPercentage, ntupleSupport, ntupleTotal) == false)
		{
			ntuples.getData(i)->getData()->clear();
			ntuples.removeElementAt(i);

			if(i != (ntuples.getCount() - 1))
			{
				i--;
			}
		}
	}

	//cout << "Done removing unsupported n-tuples. " << endl;
	println("Done removing unsupported n-tuples. ");
}

void clearIrrelevantItems(LinkedList<Ntuple*> &database, LinkedList<Ntuple*> &ntuples)
{
	//cout << "Clearing irrelevant items from database. " << endl;
	println("Clearing irrelevant items from database. ");

	for(int i = 0; i < database.getCount(); i++)
	{
		bool needCurrentIndex = false;

		for(int n = 0; n < ntuples.getCount(); n++)
		{
			if(ntuples.getData(n)->getDatabaseIndex() == i)
			{
				needCurrentIndex = true;
				
				break;
			}
		}

		if(needCurrentIndex == false)
		{
			database.getData(i)->getData()->clear();
		}
	}

	//cout << "Done clearing irrelevant items. " << endl;
	println("Done clearing irrelevant items. ");
}