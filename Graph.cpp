#include"Graph.h"

using namespace std;

Graph::Graph(int V_) {
	this->V = V_; 
	this->g = new vector<pair<int, Bus_Line*> >[V_]; 
}

void Graph::addEdge(int u, int v, Bus_Line* B, Network_Display* N) {
	g[u].push_back(make_pair(v, B)); 
	g[v].push_back(make_pair(u, B)); 
	cout << N->all_stops[u]->name << " " << N->all_stops[v]->name << " " << B->line_label << endl;
}

void Graph::setupGraph(Network_Display* N) {
	for (int i = 0; i < N->lines.size(); i++) {
		for (int j = 0; j < N->lines[i]->stops.size() - 1; j++) {
			//addEdge(N->getCompressedFromNumber(N->lines[i]->stops[j]), N->getCompressedFromNumber(N->lines[i]->stops[j + 1]), N->lines[i]->)
			addEdge(N->getCompressedFromNumber(N->lines[i]->stops[j]), N->getCompressedFromNumber(N->lines[i]->stops[j + 1]), N->lines[i], N);
			addEdge(N->getCompressedFromNumber(N->lines[i]->stops[j + 1]), N->getCompressedFromNumber(N->lines[i]->stops[j]), N->lines[i], N);
		}
	}
}