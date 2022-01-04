#ifndef CLOCK_TIME_H
#define CLOCK_TIME_H

#include <iostream>
#include <string>

using namespace std;

class Clock_Time {
public:
	Clock_Time();
	Clock_Time(int minute_, int hour_); 

	friend bool operator<=(const Clock_Time&, const Clock_Time&); 
	friend int operator-(const Clock_Time&, const Clock_Time&);

	int getMinute();
	int getHour(); 
	void read(string s); 

	void addMinutes(int min); 

	friend class Bus_Line;
	friend class Network_Display;
	friend class Graph;

private:
	int minute;
	int hour; 
};

#endif
