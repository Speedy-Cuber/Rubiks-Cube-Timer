#include <iostream>
#include <fstream>
#include <string>

void log(std::string log) {
	std::ofstream write("log.txt", std::ios::out|std::ios::app);
	write << log << std::endl;
	write.close();
}