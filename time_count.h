//time_count.h
// Class counts the time in microseconds between start() nad stop()
// It also counts the number of counts, sum of the time counts max and min time
// This examle display info about function() execution time:
//
// TimeCount tc;
// for(int i=0; i<10; i++) {
//    tc.start();
//    function();
//    tc.stop();
//    std::cout << "execution time" << i << ": " << tc.last() << std::endl;
// }
// std::cout << "sum of the execution times: " << tc.sum() << std::endl;
// std::cout << "mean of the excecution times: " << tc.mean() << std::endl;
// std::cout << "maximum execution time: " << tc.max() << std::endl;
// std::cout << "minimum execution time: " << tc.min() << std::endl;
// std::cout << "number of counts: " << tc.counts() << std::endl;
//

#ifndef TIME_COUNT_H
#define TIME_COUNT_H

#include <chrono>
#include <limits>

class TimeCount {

	private:
	double last_time{0}; // all time values in miroseconds
	double time_sum{0};
	double time_max{0};
	double time_min{ std::numeric_limits<double>::max() };

	int num_counts{0};
	bool running_{false};

	std::chrono::time_point<std::chrono::system_clock> start_point, end_point;
	std::chrono::duration<double, std::ratio<1,1000000> > time_duration;
	// ratio<1,1000000> - microseconds

	public:

	// Method does not check if counter is running.
	// If counter has been already started method restarts current count.
	void start();

	// If counter has not been started method does nothing
	void stop();

	// If counter is running method interrupts current count
	// and resets all variables to initial state
	void reset();

	bool running() const { return running_; }
	int counts() const { return num_counts; }
	double last() const { return last_time; }
	double sum() const { return time_sum; }
	double max() const { return time_max; }
	double min() const { return num_counts ? time_min : 0; }
	double mean() const { return num_counts ? time_sum/num_counts : 0; }
};

#endif
