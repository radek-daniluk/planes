//time_loop.h
// Class counts time in seconds between 2 consecutive calls of the
// interval() method. It is useful for measure frames per second.
// First call of interval() returns time from the last call
// of the setFirstPoint(). Constructor implicitly calls the setFirstPoint().

#ifndef TIME_LOOP_H
#define TIME_LOOP_H

#include <chrono>

class TimeLoop {

	private:

	std::chrono::time_point<std::chrono::system_clock> prev_time_point, now;
	std::chrono::system_clock::duration interval_duration;
	// ratio<1,1> - seconds

	public:

	TimeLoop(){ setFirstPoint(); }

	double interval() {
		now = std::chrono::system_clock::now();
		interval_duration = now - prev_time_point;
		prev_time_point = now;

		return (std::chrono::duration_cast<
					std::chrono::duration<double, std::ratio<1,1> > >)
				(interval_duration).count();
	}

	void setFirstPoint() {
		prev_time_point = std::chrono::system_clock::now();
	}

	void pause() {
		now = std::chrono::system_clock::now();
		interval_duration = now - prev_time_point;
	}

	void resume() {
		now = std::chrono::system_clock::now();
		prev_time_point = (now -= interval_duration);
	}
};

#endif
