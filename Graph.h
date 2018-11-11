// Graph.cpp              Author : Alex Lehmann
// defines a graph data structure

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <functional>
#include <iostream>
#include <queue> 

using namespace std;

class Graph {
public:
	struct VertexNode {
		char name;
		int  pos;
		VertexNode() : name(' ') { } // constructor
	};
	struct EdgeNode {
		VertexNode*  one;
		VertexNode*  two;
		int weight;
		~EdgeNode() {one = NULL; two = NULL;}
	};
public:
	// constructor
	Graph();
	// deconstuctor
	~Graph();	
	// add a new vertex
	void addVertex(char name); 
	// Adds a new edge to the graph if give the two endpoints and the weights
	void addEdge(char one, char two, int weight);
	// removes a vertex from the graph
	void removeVertex(char one);
	// removes an edge from the graph by vertices it connects
	void removeEdge(char one, char two);
	// removes an edge from the graph based on pos in edge list
	void removeEdge(int pos);
	// finds the path that is the shortest distince between
	// two nodes then returns a string with the path
	string shortestPath(char from, char to);
	// returns a string that has all of the edges
	// in the minmium spanning tree
	string minSpanningTree();
	// finds the shortest path where you visit every node and
	// return to the start node
	// uses the A* algoritum
	string travelingSalesman(char start);

	//string connectedNodes(char node);
	//void test();

protected: 						// local utilities
	// finds the minimum spanning tree of a subset of the
	// vertices in the graph and returns the total edge wieght
	// a helper function of the traveling salesmans fuction
	int minSpanH(int startOfPath, int endOfPath, VertexNode* unvisited);
	// finds the shortest distince between a set of nodes and specified node
	// returns the total distince between them
	// a helper function of the traveling salesmans fuction
	int shortestDis(int startPos, VertexNode* unvisited);
private:
	int* connections;
	EdgeNode* edgeList;
	VertexNode* vertexList;
	int numVertices;
	int numEdges;
	int edgeArraySize;
	int vertexArraySize;
};


#endif
#pragma once
