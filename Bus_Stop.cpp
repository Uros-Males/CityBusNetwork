#include "Bus_Stop.h"

#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;

Bus_Stop::~Bus_Stop(){
	//for (pair<Bus_Stop*, string> B : this->reachable) delete B.first;
}

Bus_Stop::Bus_Stop() {
	this->name = "";
	this->number = -1;
	this->reachable = {};
}

Bus_Stop::Bus_Stop(string name_, int number_) {
	this->name = name_;
	this->number = number_; 
	this->reachable = {}; 
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

