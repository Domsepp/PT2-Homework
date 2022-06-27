#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>
#include <assert.h>

struct Interval
{
	size_t index;
	size_t start;
	size_t end;
};

constexpr size_t MaxEnd = 74;
constexpr size_t MaxDuration = 10;

std::ostream& operator<<(std::ostream& os, const std::vector<Interval>& intervals)
{
	// TODO 5.3: Implement a nice print function
	return os;
}

// creates random data
std::vector<Interval> createRandomeIntervals(size_t item_count)
{
	std::vector<Interval> intervals;
	intervals.resize(item_count);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> durationDistrib(0, MaxDuration + 1);

	for (size_t i = 0; i < intervals.size(); ++i)
	{
		auto duration = durationDistrib(gen);
		std::uniform_int_distribution<size_t> startDistrib(0, MaxEnd - duration + 2);

		auto& interval = intervals[i];
		interval.index = i;
		interval.start = startDistrib(gen);
		interval.end = interval.start + duration - 1;
	}

	return intervals;
}

// TODO 5.3: Sort intervals
std::vector<Interval> sortIntervals(std::vector<Interval> intervals){
	std::vector<Interval> sorted;
	int min_end_time = 1000;
	Interval nextInterval;
	int iterator = -1;
	while (intervals.size() > 0)
	{
		iterator = -1;
		min_end_time = 1000;
		for (int i = 0; i < intervals.size(); i++)
		{
			if(intervals[i].end < min_end_time){
				min_end_time = intervals[i].end;
				nextInterval = intervals[i];
				iterator = i;
			}
		}
		sorted.push_back(nextInterval);
		assert(iterator >= 0);
		intervals.erase(intervals.begin()+iterator);
	}
	
	return sorted;
}

void schedule(const std::vector<Interval>& intervals)
{
	std::cout << std::endl << "Intervals (randomized):\n" << intervals;

	std::vector<Interval> sorted = sortIntervals(intervals);

	std::cout << std::endl << "Intervals (sorted):\n" << sorted;

	// TODO 5.3: Implement greedy scheduling
	std::vector<Interval> scheduled;

	std::cout << "\nIntervals (scheduled, " << scheduled.size() << " of " << sorted.size() << " possible)\n"
			  << scheduled;
}

int main()
{
	constexpr size_t item_count = 20;
	auto intervals = createRandomeIntervals(item_count);
	schedule(intervals);

	return 0;
}
