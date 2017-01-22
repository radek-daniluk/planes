//time_loop.h
// Class counts time in seconds between 2 consecutive calls of the
// interval() method. First call of interval() returns time from the last call
// of the setFirstPoint(). Constructor implicitly calls the setFirstPoint().

#ifndef TIME_LOOP_H
#define TIME_LOOP_H

#include <chrono>

class TimeLoop {

	private:

	std::chrono::time_point<std::chrono::system_clock> prev_time_point, now;
	std::chrono::duration<double, std::ratio<1,1> > interval_duration;
	// ratio<1,1> - seconds

	public:

	TimeLoop(){ setFirstPoint(); }

	double interval() {
		now = std::chrono::system_clock::now();
		interval_duration = now - prev_time_point;
		prev_time_point = now;

		return interval_duration.count();
	}

	void setFirstPoint() {
		prev_time_point = std::chrono::system_clock::now();
	}
};

#endif
