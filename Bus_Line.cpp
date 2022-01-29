#include "Bus_Line.h"
#include<set>
#include<map>

#include<iostream>

using namespace std;

set<Bus_Stop*> Bus_Line::m = {}; 

Bus_Line::Bus_Line() {
	this->line_label = ""; 
	this->departures = {};
	this->stops = {};
	this->stops_better = {};
	this->stops_better_reversed = {}; 
}

/*Bus_Line::Bus_Line(Bus_Line* x) {
	this->line_label = x->line_label;
	this->departures = x->departures;
	this->stops = x->stops;

	for (int i = 0; i < x->stops_better.size(); i++) {
		Bus_Stop* B = new Bus_Stop; 
	}

	this->stops_better = x->stops_better; 
	this->stops_better_reversed = x->stops_better_reversed;
}*/

void Bus_Line::addToSet() {
	for (int i = 0; i < this->stops_better.size(); i++) m.insert(this->stops_better[i]);
	//for (Bus_Stop* B : m) cout << B->name << endl;
}

Bus_Line::~Bus_Line(){
	//cout << "free";
	set<Bus_Stop*> s;
	for (int i = 0; i < this->stops_better.size(); i++) s.insert(this->stops_better[i]);
	//cout << s.size() << endl;
	for (Bus_Stop* B : s) {
		if (m.find(B) != m.end()) {
			m.erase(B);
			delete B;
		}
	}
	//for (int i = 0; i < this->stops_better_reversed.size(); i++) delete this->stops_better_reversed[i];
}

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
