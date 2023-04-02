#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

struct timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float, std::ratio<1, 1>> duration;
	std::string LogMessage;

	void LogTime(std::string log, float time) {
		std::ofstream write("LogTime.txt", std::ios::out | std::ios::app);
		write << log << time << std::endl;
		write.close();
	}
public:


	timer(std::string Log) {
		LogMessage = Log;
		start = std::chrono::high_resolution_clock::now();
	}

	~timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		LogTime(LogMessage, duration.count());
		
	}
};