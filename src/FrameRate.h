/*
 * FrameRate.h
 *
 *  Created on: Dec 21, 2014
 *      Author: domahony
 */

#ifndef FRAMERATE_H_
#define FRAMERATE_H_
#include <ctime>
#include <iostream>

namespace app {

class FrameRate {
public:
	FrameRate() : starttime(clock()), tickcount(0) {

	}

	virtual ~FrameRate() {

	}

	void operator()() {
        tickcount++;
        std::cout.precision(5);
        double total = static_cast<double>(clock() - starttime) / CLOCKS_PER_SEC;
        double frate = static_cast<double>(tickcount) / total;

        std::cout << total << " ";
        std::cout << tickcount << " ";
        std::cout << frate << std::endl;
	}

private:
	clock_t starttime;
	int tickcount;
};

} /* namespace app */

#endif /* FRAMERATE_H_ */
