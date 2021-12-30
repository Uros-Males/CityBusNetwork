#ifndef NETWORK_DISPLAY_H
#define NETWORK_DISPLAY_H

#include <iostream>
#include <string> 
#include <fstream>
#include <vector>
#include "Bus_Line.h"

using namespace std;

class Network_Display {
public:
	void setupNetwork(const string &filepath, const string &filepath2); 
	void displayBusStop(int code);
	void displayBusLine(string code);
	void displayBusLineStatistics(string code); 

	void displayAnyPath(); 
	void displayFastestPath(); 
	void displayMostComfortable(); 

	string getNameFromNumber(int code); 
	int findLine(string code); 
	int getCompressedFromNumber(int code);

	void insertBusStops(); 
	void compressBusStops();

	friend class Graph;
	
private:
	vector<Bus_Line*> lines;
	vector<Bus_Stop*> all_stops;
};

#endif