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

	void displayAnyPath(int code1, int code2); 
	void displayFastestPath(int code1, int code2, string s); 
	void displayMostComfortable(int code1, int code2);

	string getNameFromNumber(int code); 
	Bus_Line* getLineFromString(string s);
	int findLine(string code); 
	int getCompressedFromNumber(int code);

	void insertBusStops(); 
	void compressBusStops();

	void getReachables(); 

	friend class Graph;
	
private:
	vector<Bus_Line*> lines;
	vector<Bus_Stop*> all_stops;
};

#endif
