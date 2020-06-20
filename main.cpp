/*  Apriori Historic Data Mining Algorithm Implementation in C++
 *  Author: Daniel Puckowski
 *
 *  Description of algorithm (from Wikipedia article):
 *	Apriori is a classic algorithm for frequent item set mining and association rule learning over 
 *	transactional databases. It proceeds by identifying the frequent individual items in the database 
 *	and extending them to larger and larger item sets as long as those item sets appear sufficiently often 
 *	in the database. The frequent item sets determined by Apriori can be used to determine association 
 *	rules which highlight general trends in the database: this has applications in domains such as 
 *	market basket analysis.
 *
 *  Date (last edit): 01/07/2013
 *  Source code version: 2.1.2.0
 *  Uses only standard C++ libraries and supports command-line use only.
 */

#include <string>
#include <iostream>

#include "functions.h"
#include "linkedList.cpp"

using namespace std;

void main()
{
	run();
}