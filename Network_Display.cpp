#include "Network_Display.h"
#include "Graph.h"

using namespace std;

void Network_Display::setupNetwork(const string &filepath, const string &filepath2) {
	ifstream input(filepath); 
	string s;
	while (getline(input, s)) {
		Bus_Line* tmp = new Bus_Line; 
		tmp->readFromString(s); 
		this->lines.push_back(tmp); 
	}
	/*for (int i = 0; i < this->lines.size(); i++) {
		cout << this->lines[i]->line_label<<endl;
		for (int j = 0; j < this->lines[i]->departures.size(); j++) {
			cout << this->lines[i]->departures[j].hour << " " << this->lines[i]->departures[j].minute << endl;
		}
		for (int j = 0; j < this->lines[i]->stops.size(); j++) cout << this->lines[i]->stops[j] << " ";
	}*/
	input.close(); 
	ifstream input2(filepath2); 
	while (getline(input2, s)) {
		Bus_Stop* tmp = new Bus_Stop; 
		tmp->readFromString(s); 
		this->all_stops.push_back(tmp); 
		//cout << tmp->name << " " << tmp->number << endl;
	}
	insertBusStops();
}

void Network_Display::displayBusStop(int code) {
	vector<string> all; 
	string name; 
	for (int i = 0; i < this->all_stops.size(); i++) if (this->all_stops[i]->number == code) name = this->all_stops[i]->name; 
	for (int i = 0; i < this->lines.size(); i++) {
		if (count(this->lines[i]->stops.begin(), this->lines[i]->stops.end(), code)) all.push_back(this->lines[i]->line_label); 
	}
	cout << code << " " << name << " ["; 
	for (int i = 0; i < all.size(); i++) {
		if (i != all.size() - 1) cout << all[i] << " ";
		else cout << all[i];
	}
	cout << "]" << endl;
}

string Network_Display::getNameFromNumber(int code) {
	for (int i = 0; i < this->all_stops.size(); i++) if (this->all_stops[i]->number == code) return this->all_stops[i]->name;
}

int Network_Display::getCompressedFromNumber(int code) {
	for (int i = 0; i < this->all_stops.size(); i++) if (this->all_stops[i]->number == code) return i;
}

int Network_Display::findLine(string code) {
	for (int i = 0; i < this->lines.size(); i++) if (this->lines[i]->line_label == code) { return i; }
}

void Network_Display::displayBusLine(string code) {
	int id = this->findLine(code); 
	cout << code << " " << this->lines[id]->stops_better[0]->name << "->" << this->lines[id]->stops_better[this->lines[id]->stops_better.size() - 1]->name << endl;
	//cout << code << " " << getNameFromNumber(this->lines[id]->stops[0]) << "->" << getNameFromNumber(this->lines[id]->stops[this->lines[id]->stops.size() - 1]) << endl;
	for (int i = 0; i < this->lines[id]->stops.size(); i++) {
		cout << this->lines[id]->stops_better[i]->number << " " << this->lines[id]->stops_better[i]->name << endl;
		//cout << this->lines[id]->stops[i] << " " << getNameFromNumber(this->lines[id]->stops[i]) << endl;
		// vidi za /n na kraju
	}
}

void Network_Display::insertBusStops() {
	for (int i = 0; i < this->lines.size(); i++) {
		for (int j = 0; j < this->lines[i]->stops.size(); j++) {
			for (int k = 0; k < this->all_stops.size(); k++) {
				if (this->all_stops[k]->number == this->lines[i]->stops[j]) {
					this->lines[i]->stops_better.push_back(this->all_stops[k]);
				}
			}
		}
	}
}

void Network_Display::displayBusLineStatistics(string code) {
	cout << code << endl;
	int id = this->findLine(code);
	vector<string> common; 
	for (int i = 0; i < this->lines.size(); i++) {
		if (i == id) continue;
		for (int j = 0; j < this->lines[i]->stops.size(); j++) {
			int fnd = 0;
			for (int k = 0; k < this->lines[id]->stops.size(); k++) {
				if (this->lines[i]->stops[j] == this->lines[id]->stops[k]) {
					common.push_back(this->lines[i]->line_label);
					fnd = 1;
					break; 
				}
			}
			if (fnd == 1) break; 
		}
	}
	for (int i = 0; i < common.size(); i++) cout << common[i] << " ";
	cout << endl;
	cout << this->lines[id]->departures.size() << endl;
	// proveri /n
}

void Network_Display::compressBusStops() {
	for (int i = 0; i < this->all_stops.size(); i++) this->all_stops[i]->compressed_number = i;  
}

void Network_Display::displayAnyPath() {
	Graph* G = new Graph(this->all_stops.size());
	G->setupGraph(this);
}

void Network_Display::displayFastestPath() {

}

void Network_Display::displayMostComfortable() {

}