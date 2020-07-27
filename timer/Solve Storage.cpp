#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include <conio.h>
#include "function header.h"

void recountbesttimes();
void checkbest();

double besttime;
double bao5;
double bao12;
double bao100;

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
	int number[5] = { 0 };
	int x = 0;
	int i = 0;
	std::ifstream read;
	read.open("session_size.size");
	if (!read.is_open()) {
		read.close();
		std::ofstream write("session_size.size");
		write.close();
		read.open("session_size.size");
		log("session_size.size created");
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
	unsigned int number[5];
	for (int i = 0; i < 5; i++) {
		number[i] = num_of_solves(i);
	}
	number[layer_number] = std::size(solves);
	std::ofstream write;
	write.open("session_size.size");
	for (int i = 0; i < 5; i++) {
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
	std::string filename[5] = { "twobytwo.ses", "threebythree.ses", "fourbyfour.ses", "fivebyfive.ses", "3x3OH.ses" };
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
	std::string filename[5] = { "twobytwo.ses", "threebythree.ses", "fourbyfour.ses", "fivebyfive.ses", "3x3OH.ses" };
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
		checkbest();
		log("created new solve;");
		break;
		}
	case 1:
		read(layer_number);
		solves.reserve(100);
		solves.emplace_back(scramble_f(layer_number));
		typeswtch_f(0);
		recountbesttimes();
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
		recountbesttimes();
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

void secondstodisplay(double time) {
	if (time > 60) {
		int minutes = trunc(time / 60);
		double seconds = fmod(time, 60);
		std::cout << minutes << ':' << seconds;
	}
	else if (time < 60 && time != 0) {
		std::cout << time;
	}
	else {
		std::cout << "0.0";
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

void checkbest() {
	if (besttime == 0) {
		besttime = solves[solves.size() - 2].time;
	}
	else if (solves[solves.size() - 2].time < besttime) {
		besttime = solves[solves.size() - 2].time;
	}
	if (bao5 == 0) {
		bao5 = get_average_f(5);
	}
	else if (get_average_f(5) < bao5) {
		bao5 = get_average_f(5);
	}
	if (bao12 == 0) {
		bao12 = get_average_f(12);
	}
	else if (get_average_f(12) < bao12) {
		bao12 = get_average_f(12);
	}
	if (bao100 == 0) {
		bao100 = get_average_f(100);
	}
	else if (get_average_f(100) < bao100) {
		bao100 = get_average_f(100);
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
		}
		else {
			std::cout << "Solve number does not exist";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	else if (solves.size() > 1) {
		solves.erase(solves.end() - 2);
		std::cout << "Deleted last solve";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else {
		std::cout << "No solves to delete.";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	recountbesttimes();
	screen_f(0);
}

void plustwo_f() {
	if (solves.size() > 1) {
		if (solves[solves.size() - 2].plustwo == false) {
			solves[solves.size() - 2].time = solves[solves.size() - 2].time + 2.0;
			solves[solves.size() - 2].plustwo = true;
			std::cout << "Gave +2";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else {
			solves[solves.size() - 2].time = solves[solves.size() - 2].time - 2.0;
			solves[solves.size() - 2].plustwo = false;
			std::cout << "Removed +2";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	
	}
	else {
		std::cout << "No solves to give a +2 to.";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	recountbesttimes();
	screen_f(0);
}

void print_times_f() {
	system("cls");
	for (int i = 0; i < solves.size() - 1; i++) {
		std::cout << "Solve " << i + 1 << ":	";
		secondstodisplay(solves[i].time);
		std::cout << "\n";
		std::cout << "Scramble " << i + 1 << ":	" << "\n" << solves[i].scramble;
	}
	int ch;
	ch = _getch();
	screen_f(0);
}

double ao[100] = { 0 };

double getbestworst(int ao_length, int i) {
	double best_solve_in_average = ao[0];
	double worst_solve_in_average = ao[0];
	for (int j = 1; j < ao_length; j++) {
		if (best_solve_in_average > ao[j]) {
			best_solve_in_average = ao[j];
		}
		if (worst_solve_in_average < ao[j]) {
			worst_solve_in_average = ao[j];
		}
	}
	return (best_solve_in_average + worst_solve_in_average);
}

double getbestavg(int ao_length) {
	double average = 0;
	double bao = 0;
	for (int i = 0; i < solves.size() - ao_length; i++) {
		double total = 0;
		for (int j = 0; j < ao_length; j++) {
			ao[j] = solves[i + j].time;
			total = total + ao[j];
		}
		total = total - getbestworst(ao_length, i);
		double average = total / (ao_length - 2);
		if (bao == 0) {
			bao = average;
		}
		if (average < bao) {
			bao = average;
		}
	}
	return bao;
}


void recountbesttimes() {
	besttime = 0;
	bao5 = 0;
	bao12 = 0;
	bao100 = 0;
	for (int i = 0; i < solves.size() - 1; i++) {
		if (besttime == 0) {
			besttime = solves[0].time;
		}
		if (solves[i].time < besttime) {
			besttime = solves[i].time;
		}
	}
	if (solves.size() - 1 > 4) {
		bao5 = truncate_f(getbestavg(5));
	}
	if (solves.size() - 1 > 11) {
		bao12 = truncate_f(getbestavg(12));
	}
	if (solves.size() - 1 > 99) {
		bao100 = truncate_f(getbestavg(100));
	}
}

void printinfotoscreen() {
	std::cout << "Best time:	";
	secondstodisplay(besttime);
	std::cout << "\n";
	std::cout << "avg:	";
	secondstodisplay(get_average_total_f());
	std::cout <<"\n";
	std::cout << "ao5:	";
	secondstodisplay(get_average_f(5));
	std::cout << "		Best ao5:	";
	secondstodisplay(bao5);
	std::cout << "\n";
	std::cout << "ao12:	"; 
	secondstodisplay(get_average_f(12));
	std::cout << "		Best ao12:	";
	secondstodisplay(bao12);
	std::cout << "\n";
	std::cout << "ao100:	";
	secondstodisplay(get_average_f(100));
	std::cout << "		Best ao100:	";
	secondstodisplay(bao100);
	std::cout << "\n";
}