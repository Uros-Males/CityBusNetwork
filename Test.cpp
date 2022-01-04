#include "Network_Display.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	Network_Display* N = new Network_Display;
	N->setupNetwork("linije.txt", "stajalista.txt");
	N->displayBusStop(422);
	N->displayBusLine("12");
	N->displayBusLineStatistics("12");
	N->displayAnyPath(1, 23); 
	N->displayFastestPath(103, 12, "15:45");
	N->displayMostComfortable(99, 1024); 
	return 0;
}