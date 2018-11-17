#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Graph.h"

int main(int argv, char *argc[])
{
	Graph Graphy;
	for (int i = 0; i < argv; i++)
		std::cout << argc[i] << std::endl;
	if (argv < 2) {
		std::cerr << "no input file specified" << std::endl;
		system("pause");
		exit(1);
	}

	std::string line;

	std::ifstream input(argc[1]);
	if (!input) {
		std::cerr << "Cannot open input file" << std::endl;
		system("pause");
		exit(1);
	}
	std::cout << "file opened" << std::endl;


	getline(input, line);
	getline(input, line);


	for (int i = 0; i < (line.size() / 2) + 1; i++) {
		Graphy.addVertex(line[i*2]);
	}

	getline(input, line);

	while (getline(input, line)) {
		int weight = stoi(line.substr(5, line.size() - 1));
		Graphy.addEdge(line[1], line[3], weight);
	}

	system("pause");

	string vertex;
	getline(cin, vertex);

	Graphy.test();

	system("pause");

	Graphy.~Graphy();
	return 0;
}
