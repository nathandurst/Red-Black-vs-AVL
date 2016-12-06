//Nathan Ho
//Nathan Durst
//Mason Ellis
//RedBlack Definitions

#include "RedBlack.h"
#include<iostream>
#include<fstream>
using namespace std;

//initializes variables and creates empty tree
/////////////////////////////////////////////////
RedBlack::RedBlack()
{
	root = NULL;
	counter = 0;
}

//Determines whether the node is red or not
/////////////////////////////////////////////
bool RedBlack::isRed(Node *& n)
{
	++counter;	//increment counter for comparison
	if (n == NULL) return false;	//not red if NULL
	return n->color == RED;			//return true if red
}

//Checks to see if the tree is empty by looking at its root
////////////////////////////////////////////////////////////
bool RedBlack::isEmpty()
{
	++counter;				//incr counter for comparison
	return root == NULL;	//if root is empty, so is tree
}

//inserts the node into the tree, left if less than or equal to
// current node data, right if greater than current data
////////////////////////////////////////////////////////
void RedBlack::insert(int val)
{
	Node *current, *parent;
	Node *temp = new Node;
	temp->data = val;
	temp->left = NULL;
	temp->right = NULL;
	temp->color = RED;
	current = root;
	parent = NULL;
	if (++counter && root == NULL)
	{
		root = temp;
		temp->parent = NULL;
	}
	else
	{
		while (++counter && current != NULL)
		{
			parent = current;
			if (++counter && current->data < temp->data)
				current = current->right;
			else
				current = current->left;
		}
		temp->parent = parent;
		if (++counter && parent->data < temp->data)
			parent->right = temp;
		else
			parent->left = temp;
	}
	balance(temp);
}

//Rotates the node provided to the left, balancing part of the tree
//////////////////////////////////////////////////////////////////
void RedBlack::rotateLeft(Node *n)
{
	//wont rotate if nothing on the right
	if (++counter && n->right == NULL)
		return;
	else
	{	//if something on the left, make the right of n point to it
		Node *temp = n->right;
		if (++counter && temp->left != NULL)
		{
			n->right = temp->left;
			temp->left->parent = n;
		}
		else
			n->right = NULL;
		if (++counter && n->parent != NULL)
			temp->parent = n->parent;
		if (++counter && n->parent == NULL)
			root = temp;
		else
		{	//if n is on left, point that to the left
			if (++counter && n == n->parent->left)
				n->parent->left = temp;
			else
				n->parent->right = temp;
		}
		//node is on left of temp and temp becomes parent
		temp->left = n;
		n->parent = temp;
	}
}

//Rotates the node provided to the right, balancing part of the tree
/////////////////////////////////////////////////////////////
void RedBlack::rotateRight(Node *n)
{
	// wont rotate if nothing on the left
	if (++counter && n->left == NULL)
		return;
	else
	{	//if something on the right, make the left of n point to it
		Node *temp = n->left;
		if (++counter && temp->right != NULL)
		{
			n->left = temp->right;
			temp->right->parent = n;
		}
		else
			n->left = NULL;
		if (++counter && n->parent != NULL)
			temp->parent = n->parent;
		if (++counter && n->parent == NULL)
			root = temp;
		else
		{	//if n is on the left, point that to temp
			if (++counter && n == n->parent->left)
				n->parent->left = temp;
			else
				n->parent->right = temp;
		}
		//node is on right of temp and temp becomes parent
		temp->right = n;
		n->parent = temp;
	}
}

//swaps the color booleans of node and its children
///////////////////////////////////////////////////
void RedBlack::swapColors(Node *& n)
{	//swap colors of n and its children
	n->color = !n->color;
	n->left->color = !n->left->color;
	n->right->color = !n->right->color;
}

//Recieves the node after insertion and balances it within
// the tree, Returns nothing
///////////////////////////////////////////////////////
void RedBlack::balance(Node * n)
{
	//create pointer variables
	Node* grandparent = new Node();
	Node* parent = new Node();
	Node* uncle = new Node();

	//assign nodes granparent as long as parent isnt null
	if (++counter && n->parent == NULL)
		grandparent = NULL;
	else
		grandparent = n->parent->parent;

	//assign nodes parent
	parent = n->parent;

	//assign nodes uncle as long as grandparent isnt null
	if (++counter && grandparent == NULL)
		uncle = NULL;
	else
	{	//if parent is a left child, uncle is right child(vice versa)
		if (++counter && parent == grandparent->left)
			uncle = grandparent->right;
		else
			uncle = grandparent->left;
	}
	//CASE ONE: node is root, so it must be black
	if (++counter && n == root) {
		n->color = BLACK;
		return;
	}

	//CASE TWO: nodes parent is black, no changes are needed
	if (++counter && !isRed(parent))
		return;

	//CASE THREE: parent and uncle are red,
	// make grandparent red, its children(u & p) black
	// make sure grandparent being red doesnt violate property two
	// by calling balance on grandparent
	if (++counter && isRed(parent) && isRed(uncle))
	{
		parent->color = BLACK;
		uncle->color = BLACK;
		grandparent->color = RED;
		balance(grandparent);
	}
	//CASE FOUR & FIVE: parent is red, uncle is black
	if (++counter && isRed(parent) && !isRed(uncle))
	{
		//Left of grandparent (4 & 5)
		if (++counter && parent == grandparent->left)
		{
			//CASE FOUR: node is added to right of left
			// rotate parent and then perform next case.
			if (++counter && n == parent->right)
				rotateLeft(n->parent);
			parent = n;			//CASE FIVE: child is left of left
			parent->color = BLACK;		//swap colors, rotate GP
			grandparent->color = RED;
			rotateRight(grandparent);
		}
		//Right of grandparent (4 & 5)
		else if (++counter && parent == grandparent->right)
		{
			//CASE FOUR: node is added to left of right
			// rotate parent and then perform next case.
			if (++counter && n == parent->left)
				rotateRight(n->parent);
			parent = n;			//CASE FIVE: child is right of right
			parent->color = BLACK;		//swap colors, rotate GP
			grandparent->color = RED;
			rotateLeft(grandparent);
		}
	}
	root->color = BLACK;
}

//Recieves node to print and prints data and color in order
//Returns nothing
///////////////////////////////////////////////////////
void RedBlack::inOrder(Node* n, ofstream & out)
{
	if (n == NULL)
		return;
	inOrder(n->left, out);
	out << n->data;
	if (isRed(n))
		out << " (R), ";
	else
		out << " (B), ";
	inOrder(n->right, out);
}

// Credit to:  Terry Griffin
// This method writes out the edge connections.
//////////////////////////////////////////////////////////////////////
void RedBlack::GraphVizMakeConnections(Node *nodePtr, ofstream &VizOut){
	if (nodePtr){
		if (nodePtr->left)
			VizOut << nodePtr->data << "->" << nodePtr->left->data << ";\n";
		if (nodePtr->right)
			VizOut << nodePtr->data << "->" << nodePtr->right->data << ";\n";
		GraphVizMakeConnections(nodePtr->left, VizOut);
		GraphVizMakeConnections(nodePtr->right, VizOut);
	}
}

// Credit to:  Terry Griffin
// Recieves a filename to place the GraphViz data into.
// It then calls the above graphviz method to create a 
// data file that can be used to visualize your tree.
//////////////////////////////////////////////////////////////////////
void RedBlack::GraphVizOut(ofstream& VizOut)
{
	VizOut << "digraph { \n";
	VizOut << "name [label = \"Nathan Durst\\nCMPS 3013\", shape = box]; \n";
	GraphVizMakeConnections(root, VizOut);
	VizOut << "} \n";
}

int RedBlack::getNumComparisons()
{
	//returns the counter that keeps up with number
	// of comparisons
	return counter;
}

RedBlack::~RedBlack()
{

}