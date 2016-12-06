// Nathan Ho
// Nathan Durst
// Mason Ellis
// RedBlack Declarations
#pragma once
#include<iostream>
using namespace std;

struct Node
{
	int data;		//value
	Node * parent;	//pointer to parent Node
	Node * right;	//pointer to right subtree
	Node * left;	//pointer to left subtree
	bool color;		//color of Node
};


class RedBlack
{
  public:
	//public data variable. Root (top node) of the tree
	Node* root;

	//CONSTRUCTOR
	RedBlack();

	//OBSERVOR METHODS
	bool isRed(Node*&);
	bool isEmpty();

	//MUTATOR METHODS
	void insert(int);
	void remove();
	void insertfix(Node *);
	void rotateRight(Node*);
	void rotateLeft(Node*);
	void swapColors(Node*&);
	void balance(Node*);

	//ACCESSOR METHODS
	void inOrder(Node*, ofstream&);
	void GraphVizMakeConnections(Node*, ofstream&);
	void GraphVizOut(ofstream&);
	int getNumComparisons();

	//DESTRUCTOR
	~RedBlack();

  private:
	int counter;
	bool const RED = true;
	bool const BLACK = false;
};

