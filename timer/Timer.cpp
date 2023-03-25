#include <iostream>
#include <cmath>
#include <chrono>
#include "function header.h"
#include <conio.h>
#include <stdio.h>
#include <thread>

#define space 32

float RoundMil_f(float& time) {	//Round numbers to the nearest thousandth
	time = time * 1000;
	time = std::round(time);
	time = time / 1000;
	return time;
}

static bool On = true;

//display seconds elapsed on screen
void TimeOut() {
	float OnScreenTime = 0;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::ratio<1, 1>> duration;
	while (On) {
		system("cls");
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		OnScreenTime = duration.count();
		secondstodisplay(RoundMil_f(OnScreenTime));
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}
	On = true;
}

//Record the official time of the solve
void Timer(int layer_number) {
	float time = 0;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float, std::ratio<1, 1>> duration;
	start = std::chrono::high_resolution_clock::now();
	int ch = 0;
	std::thread ostimer(TimeOut);
	ch = _getch();
	end = std::chrono::high_resolution_clock::now();
	On = false;
	ostimer.join();
	duration = end - start;
	time = duration.count();
	SetTime(RoundMil_f(time));
}