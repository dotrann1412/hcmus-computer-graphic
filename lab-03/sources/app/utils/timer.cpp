#include "timer.h"

void Timer::start() {
	offset = high_resolution_clock::now();
}

double Timer::stop() {
	duration<double> execution_time = duration_cast<duration<double>>(high_resolution_clock::now() - offset);
	return 1.0 * execution_time.count();
}