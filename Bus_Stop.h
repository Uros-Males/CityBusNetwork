#ifndef BUS_STOP_H
#define BUS_STOP_H

#include <iostream>
#include <vector> 
#include <string>
#include "Bus_Line.h"
using namespace std;

class Bus_Stop {
public:
	~Bus_Stop(); 
	Bus_Stop();
	Bus_Stop(string name_, int number_); 

	string getName();
	int getNumber();

	void readFromString(string s); 

	friend class Network_Display;
	friend class Graph;
	friend class Bus_Line;

private:
	string name; 
	int number; 
	int compressed_number;
	vector<pair<Bus_Stop*, string> > reachable; 
};

#endif 
