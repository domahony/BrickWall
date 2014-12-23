/*
 * FrameRateController.h
 *
 *  Created on: Dec 22, 2014
 *      Author: domahony
 */

#ifndef FRAMERATECONTROLLER_H_
#define FRAMERATECONTROLLER_H_

#include <ctime>

namespace app {

class FrameRateController {
public:
	FrameRateController(double fps) : fps(fps), control_rate(1./fps), last_tick(clock()), frame_time(0.) {

	}

	bool tick() {

        auto cur_tick = clock();
        auto delta = static_cast<double>(cur_tick - last_tick) / CLOCKS_PER_SEC;

        frame_time += delta;
        last_tick = cur_tick;

        if (frame_time < control_rate) {
        	return false;
        }

        frame_time -= control_rate;

        return true;
	}

	virtual ~FrameRateController() {

	}

private:

	double fps;
    double control_rate = 1./fps;
    clock_t last_tick = clock();
    double frame_time = 0.;

};

} /* namespace app */

#endif /* FRAMERATECONTROLLER_H_ */
