// Graph.cpp              Author : Alex Lehmann
// the test program for the graph

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
		Graphy.addVertex(line[i * 2]);
	}

	getline(input, line);

	while (getline(input, line)) {
		int weight = stoi(line.substr(5, line.size() - 1));
		Graphy.addEdge(line[1], line[3], weight);
	}

	system("pause");

	string choice;

	do {
		std::cout << "To run Dijkstra's shortest paths algoritum enter '1'" << std::endl;
		std::cout << "To create a minimum spanning tree enter '2'" << std::endl;
		std::cout << "To create run the a* traveling salesman solution enter '3'" << std::endl;
		std::cout << "To close the program enter '0' :";
		getline(std::cin, choice);

		if (choice == "1") {
			char start, end;
			std::string temp;
			std::cout << "From what vertex? ";
			getline(std::cin, temp);
			start = temp[0];
			std::cout << "To what vertex? ";
			getline(std::cin, temp);
			end = temp[0];

			cout << Graphy.shortestPath(start, end) << endl << endl;
		}

		if (choice == "2") {
			cout << Graphy.minSpanningTree() << endl << endl;
		}

		if (choice == "3") {
			char start;
			std::string temp;
			std::cout << "From what vertex? ";
			getline(std::cin, temp);
			start = temp[0];
			
			cout << Graphy.travelingSalesman(start) << endl << endl;
		}

	} while (choice != "0");

	Graphy.~Graphy();

	system("pause");

	return 0;
}
