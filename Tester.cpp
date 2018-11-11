//Tester.cpp      Author: Alex Lehmann
// runs the main method that takes the file
// and feeds the words into the tree. It then
// prints the results to a file and deletes the tree.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <functional>

#include "LinkedBinaryTree.h"

using namespace std;

int main(int argv, char *argc[])
{

	string word("Test."), lastword("");
	LinkedBinaryTree* tree = new LinkedBinaryTree;

	(*tree).addRoot();

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
			(*tree).insert(word);
		}
	}
	cout << "Done inserting";

	LinkedBinaryTree::PositionList plist = (*tree).inpositions();
	ofstream output("WordCount.txt");
	if (!output)
		cout << "Cannot open output file" << endl;
	else
	{
		cout << "Writing the tree to a file ... " << endl;
		for (list<LinkedBinaryTree::Position>::iterator i = plist.begin(); i != plist.end(); ) {
			output << (*i).count() << "  :  " << **i;
			i++;
			if (i != plist.end()) output << "\n";
		}
		output << "there were " << (*tree).size() << " unique words" << endl;
	}

	delete tree;

	system("pause");

	return 0;
}