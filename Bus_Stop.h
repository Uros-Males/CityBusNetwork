#ifndef BUS_STOP_H
#define BUS_STOP_H

#include <iostream>
#include <vector> 
#include <string>

using namespace std;

class Bus_Stop {
public:
	Bus_Stop();
	Bus_Stop(string name_, int number_); 

	string getName();
	int getNumber();

	void readFromString(string s); 

	friend class Bus_Line;
	friend class Network_Display;
	friend class Graph;

private:
	string name; 
	int number; 
	int compressed_number;
};

#endif 
