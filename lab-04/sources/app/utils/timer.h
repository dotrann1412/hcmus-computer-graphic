#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <chrono>

using namespace std::chrono;

class Timer
{
private:
	high_resolution_clock::time_point offset;

public:
	void start();
	double stop();

};

#endif