
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Item.h"
#include "Ntuple.h"
#include "linkedList.h"

using namespace std;

const string PROGRAM_VERSION_NUMBER = "2.1.2.0";

const int NUM_SUPPORT_LEVELS = 9;

const double SUPPORT_LEVELS[] = 
{
	-1, 0.25, 0.50, 1.00, 2.00, 5.00, 10.00, 20.00, 50.00
};

void   run();
void   waitForUser();
void   print(int number);
void   printProgramInfo();
void   printProgramMenu();
void   print(double number);
void   print(string output);
void   println(string output);
void   promptForVerboseOutput();
void   printValidSupportLevels();
void   clearList(LinkedList<Ntuple*> &list);
void   printDatabase(LinkedList<Ntuple*> &database);
void   printSupportedNtuples(LinkedList<Ntuple*> &combinationList);
void   removeUnsupportedNtuples(LinkedList<Ntuple*> &ntuples, double &supportPercentage);
void   clearIrrelevantItems(LinkedList<Ntuple*> &database, LinkedList<Ntuple*> &ntuples);

bool   normalRun();
bool   isValidSupportLevel(double &supportPercentage);
bool   isSupported(double &supportPercentage, int &tupleSupport, int &numberOfTuples);
bool   readDatabaseFile(string &databaseFileName, LinkedList<Ntuple*> &database, int &numberOfElements);
bool   getNtuples(Ntuple* &itemSet, int &tupleSize, int &databaseIndex, LinkedList<Ntuple*> &combinations);
bool   getAllNtuplesWithSupport(LinkedList<Ntuple*> &database, int &tupleSize, LinkedList<Ntuple*> &combinations);

int    getMenuChoice();
int    checkNtupleForMatch(Ntuple* &combination, LinkedList<Ntuple*> &combinations);
	 
double getSupportPercentage();

string getOutputFilename();
string getDatabaseFilename();

#endif