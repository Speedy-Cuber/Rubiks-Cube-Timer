#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include <conio.h>
#include "function header.h"

struct solve {
	double time;
	std::string scramble;
	bool plustwo;
	solve(std::string in) {
		scramble = in;
		time = 0;
		plustwo = false;
		log("scramble added");
	}
	solve(double in, std::string inw, bool inb) {
		time = in;
		scramble = inw;
		plustwo = inb;
		log("solve read");
	}
};

std::vector<solve> solves;

int num_of_solves(int layer_number) {
	int number[4] = { 0 };
	int x = 0;
	int i = 0;
	std::ifstream read;
	read.open("session_size.txt");
	if (!read.is_open()) {
		read.close();
		std::ofstream write("session_size.txt");
		write.close();
		read.open("session_size.txt");
		log("session_size.txt created");
	}
	while (read >> x) {
		number[i] = x;
		i++;
	}
	read.close();
	log("session_size read");
	return number[layer_number];
}

void numsolveswrite(int layer_number) {
	unsigned int number[4];
	for (int i = 0; i < 4; i++) {
		number[i] = num_of_solves(i);
	}
	number[layer_number] = std::size(solves);
	std::ofstream write;
	write.open("session_size.txt");
	for (int i = 0; i < 4; i++) {
		write << number[i] << ' ';
	}
	write.close();
	log("wrote to session_size");
}

bool stringtobool(std::string in) {
	if (in == "true") {
		return 1;
	}
	else {
		return 0;
	}
}

void read(int layer_number) {
	std::string filename[4] = { "twobytwo.txt", "threebythree.txt", "fourbyfour.txt", "fivebyfive.txt" };
	std::ifstream read;
	read.open(filename[layer_number]);
	if (!read.is_open()) {
		read.close();
		std::ofstream write(filename[layer_number]);
		write.close();
		log("Created session");
		read.open(filename[layer_number]);
	}
	solves.reserve(num_of_solves(layer_number));
	std::string all;
	std::string in;
	std::string intime;
	std::string plustwo;
	bool plus_two = false;
	double time;
	while (std::getline(read, all)) {
		std::stringstream ss(all);
		std::getline(ss, intime, ',');
		time = std::stod(intime);
		std::getline(ss, in, ',');
		std::getline(ss, plustwo, ',');
		plus_two = stringtobool(plustwo);
		solves.emplace_back(time, in, plus_two);
	}
	read.close();
	log("session file read");
}

std::string booltostring(bool in) {
	if (in) {
		return "true";
	}
	else {
		return "false";
	}
}

void write(int layer_number) {
	std::string filename[4] = { "twobytwo.txt", "threebythree.txt", "fourbyfour.txt", "fivebyfive.txt" };
	std::ofstream write;
	write.open(filename[layer_number]);
	for (unsigned int i = 0; i < std::size(solves); i++) {
		write << solves[i].time << ',';
		write << solves[i].scramble << ',';
		write << booltostring(solves[i].plustwo) << std::endl;
	}
	write.close();
	log("wrote to session");
}

void data_manager_f(int casenum, int layer_number, int layer_number_new) {
	switch (casenum) {
	case 0:
		{int size = solves.size() % 100;
		if (size == 0) {
			solves.reserve(100);
			write(layer_number);
			numsolveswrite(layer_number);
			log("reserved solves");
		}
		solves.emplace_back(scramble_f(layer_number));
		log("created new solve;");
		break;
		}
	case 1:
		read(layer_number);
		solves.reserve(100);
		solves.emplace_back(scramble_f(layer_number));
		typeswtch_f(0);
		log("initiated new session;");
		break;
	case 2:
		solves.erase(solves.end() - 1);
		write(layer_number);
		numsolveswrite(layer_number);
		solves.clear();
		solves.reserve(num_of_solves(layer_number));
		read(layer_number_new);
		solves.reserve(100);
		solves.emplace_back(scramble_f(layer_number_new));
		log("created new solve");
		sessionswtch_f(layer_number_new);
		typeswtch_f(0);
		log("session switched;");
		break;
	case 3:
		solves.erase(solves.end() - 1);
		write(layer_number);
		numsolveswrite(layer_number);
		log("close complete");
		break;
	}
}

std::string get_scramble_f() {
	return solves[solves.size() - 1].scramble;
}

void set_time_f(double time) {
	solves[solves.size() - 1].time = time;
}

double get_time() {
	int size = solves.size() - 1;
	if (size != 0) {
		return solves[solves.size() - 2].time;
	}
	else {
		return 0;
	}
}

double get_average_f(unsigned int averagenumber) {
	if (solves.size() > averagenumber) {
		double total = 0;
		double timearray[100] = { 0 };
		for (unsigned int i = 0; i < (averagenumber); i++) {
			timearray[i] = solves[solves.size() - 2 - i].time;
		}
		double worsttime = timearray[0];
		for (unsigned int i = 0; i < averagenumber; i++) {
			if (timearray[i] > worsttime) {
				worsttime = timearray[i];
			}
		}
		double besttime = timearray[0];
		for (unsigned int i = 0; i < averagenumber; i++) {
			if (timearray[i] < besttime) {
				besttime = timearray[i];
			}
		}
		for (unsigned int i = 0; i < averagenumber; i++) {
			total = total + timearray[i];
		}
		total = total - worsttime;
		total = total - besttime;
		int divisor = averagenumber - 2;
		return truncate_f(total / divisor);
	}
	else {
		return 0;
	}
}

double get_average_total_f() {
	if (solves.size() > 1) {
		double total = 0;
		for (unsigned int i = 0; i < (solves.size() - 1); i++) {
			total = total + solves[i].time;
		}
		return truncate_f(total / (solves.size() - 1));
	}
	else {
		return 0;
	}
}

int currentsessionsize_f() {
	return solves.size();
}

void deletesolve_f(bool deletespecificsolve) {
	if(deletespecificsolve){
		for (int i = 0; i < solves.size() - 1; i++) {
			std::cout << "Solve " << i + 1 << ":	" << solves[i].time << "\n";
		}
		std::cout << "Enter solve number to delete: ";
		int solvetodelete = 0;
		std::cin >> solvetodelete;
		solvetodelete = solvetodelete - 1;
		if (solvetodelete < solves.size() - 1) {
			solves.erase(solves.begin() + solvetodelete);
			std::cout << "Deleted solve " << solvetodelete + 1;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			screen_f(0);
		}
		else {
			std::cout << "Solve number does not exist";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			screen_f(0);
		}
	}
	else if (solves.size() > 1) {
		solves.erase(solves.end() - 2);
		std::cout << "Deleted last solve";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		screen_f(0);
	}
	else {
		std::cout << "No solves to delete.";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		screen_f(0);
	}
}

void plustwo_f() {
	if (solves.size() > 1) {
		if (solves[solves.size() - 2].plustwo == false) {
			solves[solves.size() - 2].time = solves[solves.size() - 2].time + 2.0;
			solves[solves.size() - 2].plustwo = true;
			std::cout << "Gave +2";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			screen_f(0);
		}
		else {
			solves[solves.size() - 2].time = solves[solves.size() - 2].time - 2.0;
			solves[solves.size() - 2].plustwo = false;
			std::cout << "Removed +2";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			screen_f(0);
		}
	
	}
	else {
		std::cout << "No solves to give a +2 to.";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		screen_f(0);
	}
}

void print_times_f() {
	system("cls");
	for (int i = 0; i < solves.size() - 1; i++) {
		std::cout << "Solve " << i + 1 << ":	" << solves[i].time << "\n";
	}
	int ch;
	ch = _getch();
	screen_f(0);
}