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
	void readFromString(string s);
	friend class Network_Display;
	friend class Graph;
private:
	string line_label; 
	vector<Clock_Time> departures;
	vector<int> stops; 
	vector<Bus_Stop*> stops_better;
};

#endif
