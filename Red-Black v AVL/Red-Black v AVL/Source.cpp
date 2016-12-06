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
	
	/*rb.insert(10);
	rb.insert(20);
	rb.insert(5);
	rb.insert(16);
	rb.insert(35);
	rb.insert(100);
	rb.insert(40);
	rb.insert(2);*/

	outfile << "Nathan Durst" << endl << endl;
	/*outfile << "the tree data in order is:" << endl;
	rb.inOrder(rb.root, outfile);
	outfile << endl << endl;*/

	//rb.GraphVizOut(outfile);
	outfile << endl << endl;
	
	outfile<< "With " << insertCounter << " nodes inserted\n";
	outfile<< "and " << removeCounter << " nodes removed\n";
	outfile << "There are a total of ";
	outfile<< rb.getNumComparisons() << " comparisons.";

	outfile.close();
}