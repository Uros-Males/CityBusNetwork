#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>

using namespace std;

class FileError : public exception {
public:
	FileError(const string& name) {
		cout << "Greška. Fajl pod nazivom " << name << " ne postoji." << endl;
	}
};

class TypeError : public exception {
public:
	TypeError(int x) {
		cout << "Greška. Ne postoji opcija s rednim brojem " << x << "." << endl;
	}
};

class BusStopError : public exception {
public:
	BusStopError(int code) {
		cout << "Greška. Stajalište pod nazivom " << code << " ne postoji." << endl;
	}
};

class BusLineError : public exception {
public:
	BusLineError(const string& s) {
		cout << "Greška. Linija pod nazivom " << s << " ne postoji." << endl;
	}
};

class TimeError : public exception {
public:
	TimeError(const string& s) {
		cout << "Greška. " << s << " nije validan format vremena." << endl;
	}
};

class PathError : public exception {
public:
	PathError(int x, int y) {
		cout << "Nažalost, putanja od stajališta " << x << " do stajališta " << y << " ne postoji." << endl;
	}
};

#endif // ! EXCEPTIONS_H

