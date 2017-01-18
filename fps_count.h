//fps_count.h
// Class counts the time in microseconds between 2 consecutive calls of the
// interval() method. First call of interval() returns time from the last call
// of the setFirstPoint(). Constructor implicitly calls the setFirstPoint().

#ifndef FPS_COUNT_H
#define FPS_COUNT_H

#include <chrono>

class FpsCount {

	private:

	std::chrono::time_point<std::chrono::system_clock> prev_time_point, now;
	std::chrono::duration<double, std::ratio<1,1000000> > interval_duration;
	// ratio<1,1000000> - microseconds

	public:

	FpsCount(){ setFirstPoint(); }

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
