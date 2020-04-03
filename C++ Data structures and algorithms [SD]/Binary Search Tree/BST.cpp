#include <iostream>
#include <fstream>
#include <conio.h>
#include <assert.h>

using std::ifstream;
using std::cout;
using std::endl;

class Node{
private:
	int info;
	Node* left, *right;
public:
	Node() : left(NULL), right(NULL) {}
	Node(int x) : info(x), left(nullptr), right(nullptr) {}
	Node* getLeft() { return(this->left); }
	Node* getRight() { return(this->right); }
	int getInfo() { return(this->info); }
	void setRight(Node* newRight) { this->right = newRight; }
	void setLeft(Node* newLeft) { this->left = newLeft; }
	void setInfo(int newInfo) { this->info = newInfo; }
	friend class BST;
};

class BST {
	Node *root;
public:
	BST() : root(NULL) {};
	BST(int x) {
		root = new Node;
		this->root->setInfo(x);
	}
	Node* getRoot(BST) { return this->root; };
	Node* insertNode(Node*, int);
	Node* findMin(Node*);
	void insert(int);
	Node* deleteNode(Node*, int);
	void del(int);
	void makeBST(int[100], int);
	void displaySRD(Node* root);
	void displaySDR(Node* root);
	void displayRSD(Node* root);
	bool has(Node*,int);
};

Node* BST::insertNode(Node* root,int x) {
	 if (root == NULL)
	 {
	 	    root = new Node;
	    	root -> setInfo(x);
			root->setLeft(NULL);
			root->setRight(NULL);
	 }
	 else
	 {
		 if (root->getInfo() >= x)
			 root->setLeft(insertNode(root->getLeft(), x));
		 else
	 		 root->setRight(insertNode(root->getRight(), x));
	 }
	 return root;
}
void BST::insert(int x) {
	root = insertNode(root, x);
}
void BST::displaySRD(Node* root) {
	if (root == NULL)
		return;
	displaySRD(root->getLeft());
	cout << root->getInfo() <<' ';
	displaySRD(root->getRight());
}
void BST::displaySDR(Node* root) {
	if (root == NULL)
		return;
	displaySDR(root->getLeft());
	displaySDR(root->getRight());
	cout << root->getInfo() << ' ';
}
void BST::displayRSD(Node* root) {
	if (root == NULL)
		return;
	cout << root->getInfo() << ' ';
	displayRSD(root->getLeft());
	displayRSD(root->getRight());
}
void BST::makeBST(int arr[100], int n) {
	for (int i = 0; i < n; i++)
		this->insert(arr[i]);
}
bool BST::has(Node* root, int x) {
		if (root == NULL)
			return false;
		if (root->getInfo() == x)
			return true;
		if (root->getInfo() < x)
			return has(root->getRight(), x);
		return has(root->getLeft(), x);
}
Node* BST::findMin(Node* root) {
	if (root == NULL)
		return NULL;
	if (root->getLeft() == NULL)
		return root;
	return findMin(root);
}
Node* BST::deleteNode(Node* root,int x) {
	Node* aux;
	if (root == NULL)
		return NULL;
	else if (x < root->getInfo())
		root->setLeft(deleteNode(root->getLeft(), x));
	else if (x > root->getInfo())
		root->setRight(deleteNode(root->getRight(), x));
	else if (root->getLeft() && root->getRight())
	{
		aux = findMin(root->getRight());
		root->setInfo(aux->getInfo());
		root->setRight(deleteNode(root->getRight(),root->getInfo()));
	}
	else
	{
		aux = root;
		if (root->getLeft() == NULL)
			root = root->getRight();
		else if (root->getRight() == NULL)
			root = root->getLeft();
		delete aux;
	}
	return root;
}
void BST::del(int x) {
	this->root = deleteNode(this->root, x);
}

void read(int arr[100], int& n)
{
	ifstream fin("BST.in");
	int i = 0;
	while (fin)
	{
		fin >> arr[i++];
	}
	i--;
	n = i;
}

int main()
{
	int arr[100], n = 0;
	read(arr, n); // 6 4 9 2 1 5 3 7 8
	BST Tree;
	Tree.makeBST(arr, n);
	cout << "(SRD):";
	Tree.displaySRD(Tree.getRoot(Tree));
	cout << endl;
	cout << "(SDR):";
	Tree.displaySDR(Tree.getRoot(Tree));
	cout << endl;
	cout << "(RSD):";
	Tree.displayRSD(Tree.getRoot(Tree));
	cout << endl << endl;
	assert(Tree.has(Tree.getRoot(Tree), 8) == true);
	assert((Tree.has(Tree.getRoot(Tree), 10)) == false);
	
	
	// Delete: 1(leaf) ; 7(one son);  4(two sons)
	Tree.del(1);
	Tree.del(7);
	Tree.del(4);
	cout <<endl<<endl<< "After del(1), del(7), del(4) we have (SRD):";
	Tree.displaySRD(Tree.getRoot(Tree));
	_getch();
	return 0;
}