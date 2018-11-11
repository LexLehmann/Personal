// Graph.cpp              Author : Alex Lehmann
// implements a graph data structure and 
// gives it some utility


#include "Graph.h"

// constructor
Graph::Graph() {			// constructor
	vertexList = new VertexNode[1];
	vertexList = NULL;
	edgeList = new EdgeNode[1];
	edgeList = NULL;
	connections = new int[1];
	connections[0] = NULL;
	numVertices = 0;
	numEdges = 0;
	edgeArraySize = 1;
	vertexArraySize = 1;
}

// deconstructor
Graph::~Graph() {
	delete[] vertexList;
	delete[] edgeList;
	delete[] connections;
}


//adds a new vertex to the graph and expands the 2d array and vertex array if need be
void Graph::addVertex(char n) {
	bool Exists = false;
	for (int i = 0; i < numVertices; i++) {
		if (n == vertexList[i].name) {
			Exists = true;
		}
	}
	if (Exists == false) {
		VertexNode* newNode = new VertexNode;
		newNode->name = n;
		newNode->pos = numVertices;
		numVertices++;
		if (numVertices == vertexArraySize) {
			VertexNode* temp = vertexList;
			vertexList = new VertexNode[vertexArraySize * 2];
			for (int i = 0; i < numVertices - 1; i++) {
				vertexList[i] = temp[i];
			}
			int* tempArray = connections;
			int newArraySize = vertexArraySize * vertexArraySize * 4;
			connections = new int[newArraySize];
			for (int i = 0; i < vertexArraySize - 1; i++) {
				for (int j = 0; j < vertexArraySize - 1; j++) {
					connections[i*vertexArraySize * 2 + j] = INT_MIN;
				}
			}
			for (int i = 0; i < numVertices - 1; i++) {
				for (int j = 0; j < numVertices - 1; j++) {
					connections[i*vertexArraySize * 2 + j] = tempArray[i * vertexArraySize + j];
				}
			}
			delete[] tempArray;
			delete[] temp;
			vertexArraySize = vertexArraySize * 2;
		}
		vertexList[numVertices - 1] = *newNode;
	}
	else {
		cout << n << "already exists " << endl;
	}
}

// Adds a new edge to the graph if give the two endpoints and the weights
void Graph::addEdge(char o, char t, int weight) {
	EdgeNode* newNode = new EdgeNode;
	bool firstDone = false;
	for (int i = 0; i < numVertices; i++) {
		if (vertexList[i].name == o || vertexList[i].name == t) {
			if (firstDone == false) {
				newNode->one = &vertexList[i];
				firstDone = true;
			}
			else {
				newNode->two = &vertexList[i];
			}
		}
	}
	newNode->weight = weight;
	numEdges++;
	if (numEdges == edgeArraySize) {
		EdgeNode* temp = edgeList;
		edgeList = new EdgeNode[edgeArraySize * 2];
		for (int i = 0; i < edgeArraySize - 1; i++) {
			edgeList[i] = temp[i];
		}
		delete[] temp;
		edgeArraySize = edgeArraySize * 2;
	}
	edgeList[numEdges - 1] = *newNode;

	connections[edgeList[numEdges - 1].one->pos * vertexArraySize + edgeList[numEdges - 1].two->pos] = numEdges - 1;
	connections[edgeList[numEdges - 1].two->pos * vertexArraySize + edgeList[numEdges - 1].one->pos] = numEdges - 1;
}

// removes a vertex from the graph
void Graph::removeVertex(char toRemove) {
	int pos = INT_MIN;
	for (int i = 0; i < numVertices; i++) {
		if (vertexList[i].name == toRemove) {
			pos = i;
		}
	}
	if (pos != INT_MIN) {
		for (int i = 0; i < numEdges; i++) {
			if (edgeList[i].one->pos > pos) {
				edgeList[i].one = &vertexList[edgeList[i].one->pos - 1];
			}
			if (edgeList[i].two->pos > pos) {
				edgeList[i].two = &vertexList[edgeList[i].two->pos - 1];
			}
		}
		for (int i = pos; i < numVertices - 1; i++) {
			vertexList[i] = vertexList[i + 1];
			vertexList[i].pos = vertexList[i].pos - 1;
		}
		for (int i = 0; i < numVertices; i++) {
			if (connections[pos*vertexArraySize + i] >= 0) {
				removeEdge(connections[pos*vertexArraySize + i]);
			}
		}
		numVertices--;
		for (int i = 0; i < numVertices; i++) {
			for (int j = 0; j < numVertices; j++) {
				if (j >= pos && i < pos) {
					connections[i * vertexArraySize + j] = connections[i * vertexArraySize + j + 1];
					connections[i * vertexArraySize + j + 1] = INT_MIN;
				}
				if (i >= pos && j < pos) {
					connections[i * vertexArraySize + j] = connections[(i + 1) * vertexArraySize + j];
					connections[(i + 1) * vertexArraySize + j] = INT_MIN;
				}
				if (i >= pos && j >= pos) {
					connections[i * vertexArraySize + j] = connections[(i + 1) * vertexArraySize + j + 1];
					connections[(i + 1) * vertexArraySize + j + 1];
				}
			}
		}
	}
	else {
		cout << "that vertex doesn't exist" << endl;
	}
}

// removes an edge from the graph by vertices it connects
void Graph::removeEdge(char one, char two) {
	int vertexOne, vertexTwo, posToRemove;
	bool firstDone = false;
	for (int i = 0; i < numVertices; i++) {
		if (vertexList[i].name == one || vertexList[i].name == two) {
			if (firstDone == false) {
				vertexOne = vertexList[i].pos;
				firstDone = true;
			}
			else {
				vertexTwo = vertexList[i].pos;
			}
		}
	}
	posToRemove = connections[vertexOne * vertexArraySize + vertexTwo];
	connections[vertexOne * vertexArraySize + vertexTwo] = INT_MIN;
	connections[vertexTwo * vertexArraySize + vertexOne] = INT_MIN;
	numEdges--;
	for (int i = posToRemove; i < numEdges; i++) {
		edgeList[i] = edgeList[i + 1];
	}
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			if (connections[i * vertexArraySize + j] > posToRemove) {
				connections[i * vertexArraySize + j] = connections[i * vertexArraySize + j] - 1;
			}
		}
	}
}

// removes an edge from the graph based on pos in edge list
void Graph::removeEdge(int pos) {
	int posToRemove = pos;
	connections[edgeList[posToRemove].one->pos * vertexArraySize + edgeList[posToRemove].two->pos] = INT_MIN;
	connections[edgeList[posToRemove].two->pos * vertexArraySize + edgeList[posToRemove].one->pos] = INT_MIN;
	numEdges--;
	for (int i = posToRemove; i < numEdges; i++) {
		edgeList[i] = edgeList[i + 1];
	}
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			if (connections[i * vertexArraySize + j] > posToRemove) {
				connections[i * vertexArraySize + j] = connections[i * vertexArraySize + j] - 1;
			}
		}
	}
}

// finds the path that is the shortest distince between
// two nodes then returns a string with the path
string Graph::shortestPath(char from, char to) {
	struct ListNode {
		VertexNode* one;
		ListNode* next;
		ListNode* prev;
		char linkedBy;
		int distinceTo;
	};
	ListNode* start, *cur, *end;
	EdgeNode* edgesToUse = new EdgeNode[edgeArraySize];
	int startPos;
	string value = "";

	for (int i = 0; i < numVertices; i++) {
		if (from == vertexList[i].name) {
			startPos = i;
		}
	}
	start = new ListNode;
	start->one = &vertexList[startPos];
	start->linkedBy = '0';
	start->distinceTo = 0;
	start->next = NULL;
	start->prev = NULL;
	cur = start;
	end = start;
	for (int i = 0; i < numEdges; i++) {
		edgesToUse[i] = edgeList[i];
	}

	while (end->one->name != to) {
		EdgeNode* shortestEdge = &edgeList[0];
		VertexNode* linkedFrom = &vertexList[0];
		VertexNode* linkedTo = &vertexList[0];
		cur = start;
		int shortestDis = INT_MAX;

		while (cur != NULL) {
			for (int i = 0; i < numVertices; i++) {
				if (connections[cur->one->pos * vertexArraySize + i] >= 0) {
					if (edgesToUse[connections[cur->one->pos * vertexArraySize + i]].weight + cur->distinceTo < shortestDis) {
						ListNode* check = start;
						while (check != NULL) {
							if (check->one == &vertexList[i]) {
								edgesToUse[connections[cur->one->pos * vertexArraySize + i]].weight = INT_MIN;
							}
							check = check->next;
						}
						if (edgesToUse[connections[cur->one->pos * vertexArraySize + i]].weight != INT_MIN) {
							shortestEdge = &edgesToUse[connections[cur->one->pos * vertexArraySize + i]];
							shortestDis = edgesToUse[connections[cur->one->pos * vertexArraySize + i]].weight + cur->distinceTo;
							linkedFrom = cur->one;
							linkedTo = &vertexList[i];
						}
					}
				}
			}
			cur = cur->next;
		}

		// Failure state
		if (shortestDis == INT_MAX) {
			return "No path";
		}

		ListNode *nextNode = new ListNode;
		nextNode->one = linkedTo;
		nextNode->linkedBy = linkedFrom->name;
		nextNode->prev = end;
		nextNode->next = NULL;
		end->next = nextNode;
		end = nextNode;
		cur = end;
		while (cur->one != linkedFrom) {
			cur = cur->prev;
		}
		nextNode->distinceTo = cur->distinceTo + shortestEdge->weight;
		shortestEdge->weight = INT_MIN;
	}

	cur = end;
	while (cur != start) {
		while (cur->prev->one->name != cur->linkedBy) {
			ListNode* toDestroy = cur->prev;
			cur->prev = toDestroy->prev;
			toDestroy->prev->next = cur;
			delete toDestroy;
		}
		cur = cur->prev;
	}

	cur = start;
	while (cur != end) {
		value = value + " " + cur->one->name + " to";
		cur = cur->next;
	}
	value = value + " " + cur->one->name;

	cur = end;
	while (cur != NULL) {
		ListNode* toDestroy = cur;
		cur = cur->prev;
	}

	return value;
}

// returns a string that has all of the edges
// in the minmium spanning tree
string Graph::minSpanningTree() {
	struct VertexCluster {
		VertexNode* ver;
		int cluster = -1;
	};

	EdgeNode* edgesToUse = new EdgeNode[edgeArraySize];
	VertexCluster* vertices = new VertexCluster[vertexArraySize];
	bool done = false;
	string value;
	int counter = 0;

	for (int i = 0; i < numEdges; i++) {
		edgesToUse[i] = edgeList[i];
	}

	for (int i = 0; i < numVertices; i++) {
		vertices[i].ver = &vertexList[i];
		vertices[i].cluster = -1;
	}

	while (!done) {
		EdgeNode* shortestEdge = &edgesToUse[0];
		VertexCluster* one = NULL;
		VertexCluster* two = NULL;
		for (int i = 1; i < numEdges; i++) {
			if (edgesToUse[i].weight != INT_MIN && edgesToUse[i].weight < shortestEdge->weight) {
				shortestEdge = &edgesToUse[i];
			}
		}

		for (int i = 0; i < numVertices; i++) {
			if (shortestEdge->one == vertices[i].ver) {
				one = &vertices[i];
			}
			if (shortestEdge->two == vertices[i].ver) {
				two = &vertices[i];
			}
		}

		if (one->cluster == -1 && two->cluster == -1) {
			one->cluster = counter;
			two->cluster = counter;
			counter++;
			value = value + one->ver->name + " to " + two->ver->name + "\n";
		}
		else if (one->cluster != -1 && two->cluster == -1) {
			two->cluster = one->cluster;
			value = value + one->ver->name + " to " + two->ver->name + "\n";
		}
		else if (one->cluster == -1 && two->cluster != -1) {
			one->cluster = two->cluster;
			value = value + one->ver->name + " to " + two->ver->name + "\n";
		}
		else if (one->cluster == two->cluster) {

		}
		else if (one->cluster != -1 && two->cluster != -1) {
			int temp = two->cluster;
			two->cluster = one->cluster;
			value = value + one->ver->name + " to " + two->ver->name + "\n";
			for (int i = 0; i < numVertices; i++) {
				if (vertices[i].cluster == two->cluster) {
					vertices[i].cluster = one->cluster;
				}
			}
		}
		shortestEdge->weight = INT_MAX;
		int clusterNum = vertices[0].cluster;
		done = true;
		int j = 1;
		while (j < numVertices && done == true) {
			if (vertices[j].cluster != clusterNum) {
				done = false;
			}
			j++;
		}
	}
	return value;
}

// finds the shortest path where you visit every node and
// return to the start node
// uses the A* algoritum
string Graph::travelingSalesman(char start) {
	struct PathNode {
		VertexNode here;
		int disFromStart, f;
		PathNode* pre;
		PathNode* next;
		VertexNode* unvisited;


		bool operator <(const PathNode& rhs) const {
			return f < rhs.f;
		};
		bool operator >(const PathNode& rhs) const {
			return f > rhs.f;
		};
	};

	priority_queue<PathNode, vector<PathNode>, greater<PathNode>> nextPath;
	PathNode* startNode = new PathNode;
	PathNode* newNode = new PathNode;
	PathNode* finished = NULL;
	string value = "";

	startNode->unvisited = new VertexNode[vertexArraySize];

	for (int i = 0; i < numVertices; i++) {
		startNode->unvisited[i] = vertexList[i];
		if (startNode->unvisited[i].name == start) {
			startNode->here = vertexList[i];
			startNode->unvisited[i].name = '*';
		}
	}

	startNode->disFromStart = 0;
	startNode->f = 0;
	startNode->pre = NULL;
	startNode->next = NULL;

	nextPath.push(*startNode);

	while (finished == NULL) {
		// chooses the next path to expand
		PathNode choiceHolder;
		PathNode* choice;
		bool allVisited;
		choiceHolder = nextPath.top();
		nextPath.pop();

		choice = new PathNode;
		choice->disFromStart = choiceHolder.disFromStart;
		choice->here = choiceHolder.here;
		choice->pre = choiceHolder.pre;
		choice->unvisited = new VertexNode[vertexArraySize];
		choice->next = startNode->next;
		startNode->next = choice;
		for (int i = 0; i < numVertices; i++) {
			choice->unvisited[i] = choiceHolder.unvisited[i];
		}

		// add the connections to the heap
		for (int i = 0; i < numVertices; i++) {
			if (connections[choice->here.pos * vertexArraySize + i] >= 0) {
				newNode = new PathNode;
				newNode->here = vertexList[i];
				newNode->disFromStart = choice->disFromStart + edgeList[connections[choice->here.pos * vertexArraySize + i]].weight;
				newNode->pre = choice;
				newNode->next = NULL;

				newNode->unvisited = new VertexNode[vertexArraySize];
				for (int j = 0; j < numVertices; j++) {
					newNode->unvisited[j] = choice->unvisited[j];
				}

				newNode->unvisited[i].name = '*';
				newNode->f = newNode->disFromStart + minSpanH(startNode->here.pos, i, newNode->unvisited);

				allVisited = true;
				for (int j = 0; j < numVertices; j++) {
					if (newNode->unvisited[j].name != '*') {
						allVisited = false;
					}
				}

				nextPath.emplace(*newNode);
				if (allVisited && finished == NULL) {
					finished = newNode;
				}
			}
		}
	}
	
	// builds the string of the path

	value = shortestPath(startNode->here.name, finished->here.name);

	while (finished->pre != NULL) {
		finished = finished->pre;
		value = value + " to " + finished->here.name;
	}

	finished = startNode;
	while (finished != NULL) {
		PathNode* toDestroy = finished;
		finished = finished->next;
		delete toDestroy;
	}

	return value;
}

// finds the minimum spanning tree of a subset of the
// vertices in the graph and returns the total edge wieght
// plus the distince from the start to that spanning tree
// and the distince from a specified node (that is at the end of the new path) to that tree 
// a helper function of the traveling salesmans fuction
int Graph::minSpanH(int startOfPath, int endOfPath, VertexNode* unvisit) {
	struct VertexNodeCluster{
		VertexNode* here;
		int cluster;
	};
	EdgeNode* EdgeInMinTree = new EdgeNode[numEdges];
	int numEdgesInMinTree = 0;
	int numClusters = 0;
	int i = 0;
	int unvisitedNodes = 0;
	bool test = true;
	VertexNode* minSpanningTree = new VertexNode[vertexArraySize];
	int value = 0;

	VertexNodeCluster *VerticesToUse = new VertexNodeCluster[numVertices];

	// checks if it has to build a tree (if there is more than 1 node unvisited)
	for (int j = 0; j < numVertices; j++) {
		VerticesToUse[j].here = &vertexList[j];
		VerticesToUse[j].cluster = -1;
		minSpanningTree[j] = unvisit[j];
		if (unvisit[j].name != '*') {
			unvisitedNodes++;
		}
	}

	if (unvisitedNodes > 1) {
		// chooses a node that is unvisited and connects it to 
		// the closest node to it's cluster that is unvisited and not in it's cluster
		// then adds the edges and vertices that connect them to the minspanning tree
		// updates the cluster of all of the newly connected nodes													// kinda a mixture of prim's algoritum and krustal's 
		while (test) {																								// was the best way I could figure out to make a min spanning
			if (unvisit[i].name != '*') {																			// tree with a subset of the nodes
				struct ListNode {
					VertexNode* one;
					ListNode* next;
					ListNode* prev;
					char linkedBy;
					int distinceTo;
				};
				ListNode* start, *cur, *end;
				EdgeNode* edgesToUse = new EdgeNode[edgeArraySize];
				int startPos = i;
				int newCluster = -1;

				start = new ListNode;
				start->one = &vertexList[startPos];
				start->linkedBy = '0';
				start->distinceTo = 0;
				start->next = NULL;
				start->prev = NULL;
				cur = start;
				end = start;

				for (int j = 0; j < numEdges; j++) {
					edgesToUse[j] = edgeList[j];
				}

				if (VerticesToUse[start->one->pos].cluster != -1) {
					for (int j = 0; j < numVertices; j++) {
						if (VerticesToUse[start->one->pos].cluster == VerticesToUse[j].cluster && start->one->pos != j) {
							ListNode *nextNode = new ListNode;
							nextNode->one = VerticesToUse[j].here;
							nextNode->linkedBy = '0';
							nextNode->prev = end;
							nextNode->next = NULL;
							nextNode->distinceTo = 0;
							end->next = nextNode;
							end = nextNode;
						}
					}
				}

				do {
					EdgeNode* shortestEdge = &edgeList[0];
					VertexNode* linkedFrom = &vertexList[0];
					VertexNode* linkedTo = &vertexList[0];
					cur = start;
					int shortestDis = INT_MAX;

					while (cur != NULL) {
						for (int j = 0; j < numVertices; j++) {
							if (connections[cur->one->pos * vertexArraySize + j] >= 0) {
								if (edgesToUse[connections[cur->one->pos * vertexArraySize + j]].weight + cur->distinceTo < shortestDis) {

									ListNode* check = start;
									while (check != NULL) {
										if (check->one == &vertexList[j]) {
											edgesToUse[connections[cur->one->pos * vertexArraySize + j]].weight = INT_MIN;
										}
										check = check->next;
									}
									if (edgesToUse[connections[cur->one->pos * vertexArraySize + j]].weight != INT_MIN) {
										shortestEdge = &edgesToUse[connections[cur->one->pos * vertexArraySize + j]];
										shortestDis = edgesToUse[connections[cur->one->pos * vertexArraySize + j]].weight + cur->distinceTo;
										linkedFrom = cur->one;
										linkedTo = &vertexList[j];
									}
								}
							}
						}
						cur = cur->next;
					}

					ListNode *nextNode = new ListNode;
					nextNode->one = linkedTo;
					nextNode->linkedBy = linkedFrom->name;
					nextNode->prev = end;
					nextNode->next = NULL;
					end->next = nextNode;
					end = nextNode;
					cur = end;
					while (cur->one != linkedFrom) {
						cur = cur->prev;
					}
					nextNode->distinceTo = cur->distinceTo + shortestEdge->weight;
					shortestEdge->weight = INT_MIN;

				} while (VerticesToUse[end->one->pos].cluster == -1 && unvisit[end->one->pos].name == '*');

				cur = end;

				while (cur != NULL) {
					if (cur != start) {
						if (cur->distinceTo != 0) {
							while (cur->prev->one->name != cur->linkedBy) {
								ListNode* toDestroy = cur->prev;
								cur->prev = toDestroy->prev;
								toDestroy->prev->next = cur;
								delete toDestroy;
							}
						}
						else {
							while (cur->prev != NULL) {
								ListNode* toDestroy = cur->prev;
								cur->prev = toDestroy->prev;
								if (cur->prev != NULL) {
									toDestroy->prev->next = cur;
								}
								delete toDestroy;
							}
							start = cur;
						}
					}

					if (VerticesToUse[cur->one->pos].cluster != -1) {
						newCluster = VerticesToUse[cur->one->pos].cluster;
					}
					if (cur != start) {
						EdgeInMinTree[numEdgesInMinTree] = edgeList[connections[cur->one->pos * vertexArraySize + cur->prev->one->pos]];
						numEdgesInMinTree++;
					}
					cur = cur->prev;
				}

				if (newCluster == -1) {
					newCluster = numClusters;
					numClusters++;
				}

				cur = start;

				while (cur != NULL) {
					if (VerticesToUse[cur->one->pos].cluster != -1) {
						for (int l = 0; l < numVertices; l++) {
							if (VerticesToUse[l].cluster == VerticesToUse[cur->one->pos].cluster) {
								VerticesToUse[l].cluster = newCluster;
							}
						}
					}
					VerticesToUse[cur->one->pos].cluster = newCluster;
					cur = cur->next;
				}

				test = false;
				for (int j = 0; j < numVertices; j++) {
					if (unvisit[j].name != '*' && VerticesToUse[j].cluster != newCluster) {
						test = true;
					}
				}
			}
			i++;
		}

		for (int i = 0; i < numVertices; i++) {
			minSpanningTree[i] = unvisit[i];
		}

		for (int i = 0; i < numEdgesInMinTree; i++) {
			value = value + EdgeInMinTree[i].weight;
			minSpanningTree[EdgeInMinTree[i].one->pos] = vertexList[EdgeInMinTree[i].one->pos];
			minSpanningTree[EdgeInMinTree[i].two->pos] = vertexList[EdgeInMinTree[i].two->pos];
		}
	}

	if (unvisitedNodes > 0) {

		value = value + shortestDis(startOfPath, minSpanningTree);

		value = value + shortestDis(endOfPath, minSpanningTree);
	}

	delete[] EdgeInMinTree;
	delete[] minSpanningTree;

	return value;
}

// finds the shortest distince between a set of nodes and specified node
// returns the total distince between them
// a helper function of the minSpanH fuction
int Graph::shortestDis(int startPos, VertexNode* unvisited) {
	struct Nodes {
		VertexNode* here;
		int distinceTo;
	};

	Nodes* visited = new Nodes[vertexArraySize];
	EdgeNode* edgesToUse = new EdgeNode[edgeArraySize];
	int lastFound = startPos;

	for (int i = 0; i < numVertices; i++) {
		visited[i].here = &vertexList[i];
		visited[i].distinceTo = INT_MAX;
	}

	for (int i = 0; i < numEdges; i++) {
		edgesToUse[i] = edgeList[i];
	}

	// builds a dikstra's shotest path out until
	// it hits any of the nodes that are unvisited

	visited[startPos].distinceTo = 0;
	if (unvisited[startPos].name == '*') {
		do {
			EdgeNode* shortestEdge = &edgeList[0];
			int shortestDis = INT_MAX;
			for (int i = 0; i < numVertices; i++) {
				if (visited[i].distinceTo < INT_MAX) {
					for (int j = 0; j < numVertices; j++) {
						if (connections[i * vertexArraySize + j] >= 0) {
							if (edgesToUse[connections[i * vertexArraySize + j]].weight + visited[i].distinceTo < shortestDis) {
								if (visited[j].distinceTo != INT_MAX) {
									edgesToUse[connections[i * vertexArraySize + j]].weight = INT_MIN;
								}

								if (edgesToUse[connections[i * vertexArraySize + j]].weight != INT_MIN) {
									shortestEdge = &edgesToUse[connections[i * vertexArraySize + j]];
									shortestDis = shortestEdge->weight + visited[i].distinceTo;
								}
							}
						}
					}
				}
			}
			shortestEdge->weight = INT_MIN;
			if (visited[shortestEdge->one->pos].distinceTo == INT_MAX) {
				lastFound = shortestEdge->one->pos;
				visited[lastFound].distinceTo = shortestDis;
			}
			else {
				lastFound = shortestEdge->two->pos;
				visited[lastFound].distinceTo = shortestDis;
			}
		} while (unvisited[lastFound].name == '*');
	}

	int value = visited[lastFound].distinceTo;
	delete[] visited;

	return value;
}

// These were just some fuctions I used to test different parts of the code

//string Graph::connectedNodes(char n) {
//	string value = "";
//	for (int i = 0; i < numVertices; i++) {
//		cout << vertexList[i].name << endl;
//	}
//	for (int i = 0; i < numEdges; i++) {
//		cout << edgeList[i].two->name << " ";
//		cout << edgeList[i].one->name << endl;
//	}
//	int vertexPos;
//	for (int i = 0; i < numVertices; i++) {
//		if (n == vertexList[i].name) {
//			vertexPos = i;
//		}
//	}
//	cout << "That vertex connects to" << endl;
//
//	//for (int i = 0; i < numVertices; i++) {
//	//	for (int j = 0; j < numVertices; j++) {
//	//		if (connections[i*vertexArraySize + j] >= 0) {
//	//			cout << connections[i*vertexArraySize + j] << " ";
//	//		}
//	//		else {
//	//			cout << "X" << " ";
//	//		}
//	//	}
//	//	cout << endl;
//	//}
//
//	for (int i = 0; i < numVertices; i++) {
//		if (connections[vertexPos * vertexArraySize + i] >= 0) {
//			if (edgeList[connections[vertexPos * vertexArraySize + i]].one->name == n) {
//				value = value + edgeList[connections[vertexPos * vertexArraySize + i]].two->name + " ";
//			}
//			else {
//				value = value + edgeList[connections[vertexPos * vertexArraySize + i]].one->name + " ";
//			}
//		}
//	}
//	return value;
//}
//
//void Graph::test() {
//	VertexNode* unvisited = new VertexNode[vertexArraySize];
//
//	for (int i = 0; i < numVertices; i++) {
//		unvisited[i] = vertexList[i];
//	}
//
//	unvisited[0].name = '*';
//	unvisited[1].name = '*';
//
//
//	cout << minSpanH(0, 0, unvisited) << endl;
//	system("pause");
//}