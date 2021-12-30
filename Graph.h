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
	void addEdge(int u, int v, Bus_Line* B, Network_Display* N);


private:
	int V;
    vector < pair<int, Bus_Line*> >  *g;
};

#endif