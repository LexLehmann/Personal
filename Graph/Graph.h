// LinkedBinaryTree.cpp       Author : Alex Lehmann
// This defines a Linked Binary Tree

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <list>
#include <functional>
#include <iostream>

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
	};
public:
	Graph();					// constructor
	~Graph();					// deconstuctor
	void addVertex(char name);  // add a new vertex
	void addEdge(char one, char two, int weight);
	void removeVertex(char one);
	void removeEdge(char one, char two);
	void removeEdge(int pos);
	string shortestPath(char from, char to);
	string minSpanningTree();
	string travelingSalesman(char start);
	string connectedNodes(char node);
	void test();

protected: 						// local utilities
	int minSpanH(VertexNode* unvisited);
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
