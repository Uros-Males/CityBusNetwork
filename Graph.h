#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "Network_Display.h"

using namespace std;

class Graph {
public:
	Graph(int V_); 

	void setupGraph(Network_Display* N); 
	void addEdge(int u, int v, Bus_Line* B);
	
	void anyPath(int code1, int code2, Network_Display* N);
	void bestTimePath(int code1, int code2, string s, Network_Display* N);
	void mostComfortablePath(int code1, int code2, Network_Display* N);

	void printModifiedPath(pair<int, string>* par, int source, int target, Network_Display* N);
	void printPath(pair<int, Bus_Line*>* par, int source, int target, Network_Display* N);

private:
	int V;
    vector < pair<int, Bus_Line*> >  *g;
};

#endif