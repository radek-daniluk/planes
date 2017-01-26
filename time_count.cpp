// time_count.cpp
#include "time_count.h"

// Method does not check if counter is running.
// If counter has been already started method restarts current count.
void TimeCount::start() {
	running_ = true;
	start_point = std::chrono::system_clock::now();
}

// If counter has not been started method does nothing
void TimeCount::stop() {
	if( running_) {
		end_point = std::chrono::system_clock::now();
		time_duration = end_point - start_point;

		last_time = ( (std::chrono::duration<double, std::ratio<1,1000000> >)
							time_duration ).count();
		running_ = false;
		++num_counts;

		time_sum += last_time;
		time_max = (time_max > last_time) ? time_max : last_time;
		time_min = (time_min < last_time) ? time_min : last_time;
	}
}

// If counter is running method interrupts current count
// and resets all variables to initial state
void TimeCount::reset() {
	running_ = false;
	num_counts = 0;
	last_time = time_sum = time_max = 0;
	time_min = std::numeric_limits<double>::max();
}
