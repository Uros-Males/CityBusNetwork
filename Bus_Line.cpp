#include "Bus_Line.h"

using namespace std;

void Bus_Line::readFromString(string s) {
	//EKO1[05:30 - 23 : 30#30] 654 585 583 190
	int i = 0; 
	string tmp; 
	while (s[i] != ' ') tmp += s[i++]; 
	i++; 
	i++; 
	this->line_label = tmp; 
	tmp = ""; 
	while (s[i] != '-') tmp += s[i++];
	Clock_Time t1;
	t1.read(tmp); 
	tmp = ""; 
	i++;
	while (s[i] != '#') tmp += s[i++]; 
	Clock_Time t2;
	t2.read(tmp);
	i++;
	tmp = ""; 
	while (s[i] != ']') tmp += s[i++]; 
	int step = stoi(tmp); 
	Clock_Time go; 
	go = t1; 
	while (go <= t2) {
		Clock_Time tmp;
		tmp = go; 
		this->departures.push_back(tmp); 
		go.addMinutes(step);
	}
	i++;
	i++;
	while (i<s.size()) {
		tmp = "";
		while (s[i] != ' ' && i<s.size()) {
			tmp += s[i++];
		}
		i++;
		this->stops.push_back(stoi(tmp)); 
	}
	return;
}
