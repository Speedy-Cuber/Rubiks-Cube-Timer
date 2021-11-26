#include <iostream>
#include <cmath>
#include <chrono>
#include "function_header.h"
#include "getch.hpp"
#include <stdio.h>
#include <thread>

#define space 32

double truncate_f(double time) {
	time = time * 1000;
	time = std::trunc(time);
	time = time / 1000;
	return time;
}

static bool isoff = false;

void timerout() {
	double onscreentime = 0;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::ratio<1, 1>> duration;
	while (!isoff) {
		system("clear");
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		secondstodisplay(truncate_f(duration.count()));
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}
	isoff = false;
}

void timer_f(int layer_number) {
	double time = 0;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double, std::ratio<1, 1>> duration;
	start = std::chrono::high_resolution_clock::now();
	int ch = 0;
	std::thread ostimer(timerout);
	ch = _getch();
	end = std::chrono::high_resolution_clock::now();
	isoff = true;
	ostimer.join();
	duration = end - start;
	time = truncate_f(duration.count());
	set_time_f(time);
}
