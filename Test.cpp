#include "Network_Display.h"
#include "Exceptions.h"
#include <fstream>

#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <vector>
#include<locale.h>
using namespace std;

int main() {
	Network_Display* N = new Network_Display;
	try {
		setlocale(LC_CTYPE, "srb");
		cout << "Dobrodo�li u simulator mre�e gradskog prevoza. Molimo vas, odaberite opciju:" << endl;
		cout << "1. U�itavanje podataka o mre�i gradskog prevoza" << endl;
		cout << "0. Kraj rada" << endl;
		int x; cin >> x;
		if (x == 1) {
				string f1, f2;
				cout << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza:" << endl; cin >> f1;
				cout << "Molimo Vas, unesite putanju do fajla sa stajali�tima:" << endl; cin >> f2;
				N->setupNetwork(f1, f2);
				cout << "Mre�a gradskog prevoza je uspe�no u�itana. Molimo Vas, odaberite opciju:" << endl;

				cout << "1. Prikaz informacija o stajali�tu" << endl;
				cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
				cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
				cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
				cout << "0. Kraj rada" << endl;

				while (1) {
					int y; cin >> y;
					try {
						if (y == 1) {
							cout << "Molimo vas, unesite �ifru stajali�ta �ije informacije �elite da prika�ete: " << endl;
							int z; cin >> z;
							N->displayBusStop(z);
							cout << "Generisan je fajl stajaliste_" << z << ".txt sa osnovnim informacijama o stajali�tu " << z << "." << endl;
							cout << "1. Prikaz informacija o stajali�tu" << endl;
							cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
							cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
							cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
							cout << "0. Kraj rada" << endl;
						}
						else if (y == 2) {
							cout << "Molimo vas, unesite oznaku linije �ije informacije �elite da prika�ete: " << endl;
							string s; cin >> s;
							N->displayBusLine(s);
							cout << "Generisan je fajl linija_" << s << ".txt sa osnovnim informacijama o stajali�tu " << s << "." << endl;
							cout << "1. Prikaz informacija o stajali�tu" << endl;
							cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
							cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
							cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
							cout << "0. Kraj rada" << endl;
						}
						else if (y == 3) {
							cout << "Molimo vas, unesite oznaku linije �ije statisti�ke informacije �elite da prika�ete:" << endl;
							string s; cin >> s;
							N->displayBusLineStatistics(s);
							cout << "Generisan je fajl statistika_" << s << ".txt sa osnovnim statisti�kim informacijama o stajali�tu " << s << "." << endl;
							cout << "1. Prikaz informacija o stajali�tu" << endl;
							cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
							cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
							cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
							cout << "0. Kraj rada" << endl;
						}
						else if (y == 4) {
							cout << "Molimo vas, unesite �ifru po�etnog stajali�ta: " << endl;
							int f; cin >> f;
							N->checkBusStop(f);
							cout << "Molimo vas, unesite �ifru krajnjeg stajali�ta: " << endl;
							int l; cin >> l;
							N->checkBusStop(l); 
							cout << "Molimo vas, unesite va�e vreme dolaska na po�etno stajali�te (u formatu hh:mm):" << endl;
							string s; cin >> s;
							try {
								if (s.size() != 5) throw new TimeError(s);
							    if (s.size()>2 && s[2] != ':') throw new TimeError(s);
								for (int i = 0; i < s.size(); i++) {
									if (i != 2) {
										if (s[i] < '0' || s[i]>'9') {
											throw new TimeError(s); break;
										}
									}
								}
							}
							catch (TimeError* e) {
								e->what();
								delete e;
								cout << "1. Prikaz informacija o stajali�tu" << endl;
								cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
								cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
								cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
								cout << "0. Kraj rada" << endl;
								continue;
							}
							
							cout << "Odaberite kakvu putanju �elite da program ispi�e: " << endl;
							cout << "1. Proizvoljna putanja" << endl;
							cout << "2. Vremenski najbr�a putanja" << endl;
							cout << "3. Putanja koja koristi najmanje presedanja" << endl;

							try {
								int x; cin >> x;
								if (x == 1) N->displayAnyPath(f, l);
								else if (x == 2) N->displayFastestPath(f, l, s);
								else if (x == 3) N->displayMostComfortable(f, l);
								else {
									throw new TypeError(x);
								}
							}
							catch (TypeError* e) {
								e->what();
								delete e;
								cout << "1. Prikaz informacija o stajali�tu" << endl;
								cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
								cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
								cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
								cout << "0. Kraj rada" << endl;
								continue;
							}
							catch (PathError* e) {
								e->what();
								delete e;
								cout << "1. Prikaz informacija o stajali�tu" << endl;
								cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
								cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
								cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
								cout << "0. Kraj rada" << endl;
								continue;
							}

							cout << "Generisan je fajl putanja_" << f << "_" << l << ".txt koji sadr�i tra�enu putanju." << endl;
							cout << "1. Prikaz informacija o stajali�tu" << endl;
							cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
							cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
							cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
							cout << "0. Kraj rada" << endl;
						}
						else if (y == 0) {
							cout << "Program se zavr�io." << endl;
							break;
						}
						else {
							throw new TypeError(y);
						}
					}
					catch (TypeError* e) {
						e->what();
						delete e;
						cout << "1. Prikaz informacija o stajali�tu" << endl;
						cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
						cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
						cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
						cout << "0. Kraj rada" << endl;
						continue;
					}
					catch (BusStopError* e) {
						e->what();
						delete e;
						cout << "1. Prikaz informacija o stajali�tu" << endl;
						cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
						cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
						cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
						cout << "0. Kraj rada" << endl;
						continue;
					}
					catch (BusLineError* e) {
						e->what();
						delete e;
						cout << "1. Prikaz informacija o stajali�tu" << endl;
						cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
						cout << "3. Prikaz statisti�kih informacija o liniji gradskog prevoza" << endl;
						cout << "4. Pronalazak putanje izme�u dva stajali�ta" << endl;
						cout << "0. Kraj rada" << endl;
						continue;
					}
				}
			}


			//N->displayBusStop(422);
			//N->displayBusLine("12");
			//N->displayBusLineStatistics("12");
			//N->displayAnyPath(1, 23); 
			//N->displayFastestPath(123, 1221, "07:00");
			//N->displayMostComfortable(99, 4);
			//N->displayMostComfortable(422, 111);
			//N->displayMostComfortable(1221, 312);
		
		else if (x == 0) {
			cout << "Program se zavr�io." << endl;
		}
		else {
			throw new TypeError(x); 
		}

	}
	
	catch (FileError* e) {
		e->what();
		delete e;
		//return 0;
	}
	catch (TypeError* e) {
		e->what();
		delete e;
		//return 0;
	}
	delete N;
	_CrtDumpMemoryLeaks();
	return 0;
}