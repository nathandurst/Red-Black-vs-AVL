#include "RedBlack.h"
#include<iostream>
#include<fstream>
#include<random>
#include<ctime>
using namespace std;

void main()
{
	ofstream outfile;
	outfile.open("output.txt");

	RedBlack rb;
	Node * rootParent = NULL;
	int insertCounter = 0;
	int removeCounter = 0;
	int treeSize = 10000;

	srand(101);
	for (int i = 0; i < treeSize; i++)
	{
		insertCounter++;
		int value = rand() % 100;
		rb.insert(value);
	}

	outfile << "Nathan Durst" << endl << endl;
	outfile << endl << endl;
	
	outfile<< "With " << insertCounter << " nodes inserted\n";
	outfile<< "and " << removeCounter << " nodes removed\n";
	outfile << "There are a total of ";
	outfile<< rb.getNumComparisons() << " comparisons.";

	outfile.close();
}
