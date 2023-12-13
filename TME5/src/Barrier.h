/*
 * Barrier.h
 *
 *  Created on: 18 oct. 2023
 *      Author: 21304302
 */

#pragma once

#include <mutex>
#include <condition_variable>

class Barrier {
	int counter;
	const int max_;
	std::mutex m;
	std::condition_variable cv;

public:
	Barrier(int max): max_(max), counter(0) {}

	void done(){
		std::unique_lock<std::mutex> ul(m);
		counter++;
		if(counter == max_){
			cv.notify_all();
		}
	}

	void waitFor(){
		std::unique_lock<std::mutex> ul(m);
		while(counter != max_){
			cv.wait(ul);
		}
	}

	virtual ~Barrier();
};
