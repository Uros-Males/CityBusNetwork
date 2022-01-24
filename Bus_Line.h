#ifndef BUS_LINE_H
#define BUS_LINE_H

#include <iostream>
#include <string>
#include <vector> 
#include "Bus_Stop.h"
#include "Clock_Time.h"

using namespace std;

class Bus_Line {
public:
	Bus_Line();
	Bus_Line(Bus_Line* x);
	~Bus_Line(); 
	void readFromString(string s);
	friend class Network_Display;
	friend class Graph;
	friend class Bus_Stop;
private:
	string line_label; 
	vector<Clock_Time> departures;
	vector<int> stops; 
	vector<Bus_Stop*> stops_better;
	vector<Bus_Stop*> stops_better_reversed;
};

#endif
