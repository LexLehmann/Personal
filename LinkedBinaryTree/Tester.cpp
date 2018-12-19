#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <functional>

#include "LinkedBinaryTree.h"

using namespace std;

int main(int argv, char *argc[])
{

	string word("Test."), lastword("");
	LinkedBinaryTree tree;

	tree.addRoot();

	cout << word;

	for (int i = 0; i < argv; i++)
		cout << argc[i] << endl;
	if (argv < 2) {
		cerr << "no input file specified" << endl;
		system("pause");
		exit(1);
	}

	for (int count = 1; count < argv; count++)
	{
		ifstream input(argc[count]);
		if (!input) {
			cerr << "Cannot open input file" << argc[count] << endl;
			system("pause");
			exit(1);
		}
		cout << "file opened" << endl;
		while (input >> word)
		{
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			word.erase(remove_if(word.begin(), word.end(), ispunct));
			tree.insert(word);
			//cout << "word inserted" << endl;
		}
	}
	cout << "Done inserting";

	LinkedBinaryTree::PositionList plist = tree.inpositions();
	cout << "" << endl;
	for (list<LinkedBinaryTree::Position>::iterator i = plist.begin(); i != plist.end(); i++)
		cout << (*i).count() <<  "  :  " << **i << endl;

	//tree.~LinkedBinaryTree();

	system("pause");

	return 0;

}