#include "Clock_Time.h"

using namespace std;

Clock_Time::Clock_Time() {
	this->hour = -1;
	this->minute = -1;
}

Clock_Time::Clock_Time(int minute_, int hour_) {
	this->minute = minute_;
	this->hour = hour_;
}

int Clock_Time::getMinute() {
	return this->minute;
}

int Clock_Time::getHour() {
	return this->hour;
}

bool operator<=(const Clock_Time& C1, const Clock_Time& C2) {
	if (C1.hour < C2.hour || (C1.hour == C2.hour && C1.minute <= C2.minute)) return true;
	return false;
}

void Clock_Time::read(string s) {
	// 05:30
	this->hour = 10 * (s[0] - '0') + s[1] - '0'; 
	this->minute = 10 * (s[3] - '0') + s[4] - '0';
}

void Clock_Time::addMinutes(int min) {
	this->minute += min;
	int add_to_hour = this->minute / 60; 
	this->hour += add_to_hour;
	this->hour = this->hour % 24;
	this->minute = this->minute % 60; 
}
