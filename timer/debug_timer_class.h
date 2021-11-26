#pragma once
#include <iostream>
#include <string>
#include <chrono>

struct timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float, std::ratio<1, 1>> duration;
public:
	timer() {
		start = std::chrono::high_resolution_clock::now();
	}

	~timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << duration.count();
		
	}
};