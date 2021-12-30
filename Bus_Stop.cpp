#include "Bus_Stop.h"

using namespace std;

Bus_Stop::Bus_Stop() {
	this->name = "";
	this->number = -1;
}

Bus_Stop::Bus_Stop(string name_, int number_) {
	this->name = name_;
	this->number = number_; 
}

string Bus_Stop::getName() {
	return this->name;
}

int Bus_Stop::getNumber() {
	return this->number;
}

void Bus_Stop::readFromString(string s) {
	int i = 0; 
	string tmp = ""; 
	while (s[i] != ' ') tmp += s[i++]; 
	this->number = stoi(tmp);
	i++;
	tmp = "";
	while (i < s.size()) tmp += s[i++]; 
	this->name = tmp;
}

