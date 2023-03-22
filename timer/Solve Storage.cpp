#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include <conio.h>
#include "function header.h"
#include <limits>

void RecountBestTimes();
void CheckBest();

double BestTime;
double bao5;
double bao12;
double bao100;

struct solve {
	double Time;
	std::string scramble;
	bool plustwo;
	solve(std::string in) {
		scramble = in;
		Time = 0;
		plustwo = false;
		log("scramble added");
	}
	solve(double in, std::string inw, bool inb) {
		Time = in;
		scramble = inw;
		plustwo = inb;
		log("solve read");
	}
};

std::vector<solve> solves;

//Read size of session to be read from file
int ReadSessionInfo(int layer_number) {
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

void NumSolvesWrite(int layer_number) {
	unsigned int number[5];
	for (int i = 0; i < 5; i++) {
		number[i] = ReadSessionInfo(i);
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
	solves.reserve(ReadSessionInfo(layer_number));
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

//Record a solves in a session. Add ability to add different sessions, use vector to store session names in the session_size.size file, maybe change to Session.info
void write(int layer_number) {
	std::string filename[5] = { "twobytwo.ses", "threebythree.ses", "fourbyfour.ses", "fivebyfive.ses", "3x3OH.ses" };
	std::ofstream write;
	write.open(filename[layer_number]);
	for (unsigned int i = 0; i < std::size(solves); i++) {
		write << solves[i].Time << ',';
		write << solves[i].scramble << ',';
		write << booltostring(solves[i].plustwo) << std::endl;
	}
	write.close();
	log("wrote to session");
}

//instead of switch and case statement, make functions that do the individual parts of the entire data_manager_f() function and call those individually in the main function.

void InitializeSession() {

}

void CloseSession() {

}



void data_manager_f(int casenum, int layer_number, int layer_number_new) {
	switch (casenum) {
	case 0:
		{int size = solves.size() % 100;
		if (size == 0) {
			solves.reserve(100);
			write(layer_number);
			NumSolvesWrite(layer_number);
			log("reserved solves");
		}
		solves.emplace_back(scramble_f(layer_number));
		CheckBest();
		log("created new solve;");
		break;
		}
	case 1:
		read(layer_number);
		solves.reserve(100);
		solves.emplace_back(scramble_f(layer_number));
		typeswtch_f(0);
		RecountBestTimes();
		log("initiated new session;");
		break;
	case 2:
		solves.erase(solves.end() - 1);
		write(layer_number);
		NumSolvesWrite(layer_number);
		solves.clear();
		solves.reserve(ReadSessionInfo(layer_number));
		read(layer_number_new);
		solves.reserve(100);
		solves.emplace_back(scramble_f(layer_number_new));
		log("created new solve");
		sessionswtch_f(layer_number_new);
		typeswtch_f(0);
		RecountBestTimes();
		log("session switched;");
		break;
	case 3:
		solves.erase(solves.end() - 1);
		write(layer_number);
		NumSolvesWrite(layer_number);
		log("close complete");
		break;
	}
}

//This function takes a time in seconds and displays it nicely in minutes and seconds.
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

std::string GetScramble() {
	return solves[solves.size() - 1].scramble;
}

void set_time_f(double time) {
	solves[solves.size() - 1].Time = time;
}

double GetTime() {
	int size = solves.size() - 1;
	if (size != 0) {
		return solves[solves.size() - 2].Time;
	}
	else {
		return 0;
	}
}

double get_average_f(double averagenumber) {
	if (solves.size() > averagenumber) {
		double total = 0;
		double timearray[100] = { 0 };
		for (int i = 0; i < (averagenumber); i++) {
			timearray[i] = solves[solves.size() - 2 - i].Time;
		}
		double worsttime = timearray[0];
		for (int i = 0; i < averagenumber; i++) {
			if (timearray[i] > worsttime) {
				worsttime = timearray[i];
			}
		}
		double BestTime = timearray[0];
		for (int i = 0; i < averagenumber; i++) {
			if (timearray[i] < BestTime) {
				BestTime = timearray[i];
			}
		}
		for (int i = 0; i < averagenumber; i++) {
			total = total + timearray[i];
		}
		total = total - worsttime - BestTime;
		double average = total / (averagenumber - 2);
		return RoundMil_f(average);
	}
	else {
		return 0;
	}
}

void CheckBest() {
	if (BestTime == 0) {
		BestTime = solves[solves.size() - 2].Time;
	}
	else if (solves[solves.size() - 2].Time < BestTime) {
		BestTime = solves[solves.size() - 2].Time;
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
		for (int i = 0; i < (solves.size() - 1); i++) {
			total = total + solves[i].Time;
		}
		total = total / (solves.size() - 1);
		return RoundMil_f(total);
	}
	else {
		return 0;
	}
}

int CurrentSessionSize() {
	return solves.size();
}

void deletesolve_f(bool deletespecificsolve) {
	if(deletespecificsolve){
		for (int i = 0; i < solves.size() - 1; i++) {
			std::cout << "Solve " << i + 1 << ":	" << solves[i].Time << "\n";
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
	RecountBestTimes();
	Screen(0);
}

void plustwo_f() {
	if (solves.size() > 1) {
		if (solves[solves.size() - 2].plustwo == false) {
			solves[solves.size() - 2].Time = solves[solves.size() - 2].Time + 2.0;
			solves[solves.size() - 2].plustwo = true;
			std::cout << "Gave +2";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else {
			solves[solves.size() - 2].Time = solves[solves.size() - 2].Time - 2.0;
			solves[solves.size() - 2].plustwo = false;
			std::cout << "Removed +2";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	
	}
	else {
		std::cout << "No solves to give a +2 to.";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	RecountBestTimes();
	Screen(0);
}

void print_times_f() {
	system("cls");
	for (int i = 0; i < solves.size() - 1; i++) {
		std::cout << "Solve " << i + 1 << " time:	";
		secondstodisplay(solves[i].Time);
		std::cout << "\n";
		std::cout << "Scramble " << i + 1 << ":	" << "\n" << solves[i].scramble << "\n\n";
	}
	int ch;
	ch = _getch();
	Screen(0);
}

//iterate through instances of solve class to find best average. Called in function RecountBestTimes()
double GetBestAvg(int AoLength) {
	if (AoLength > solves.size()) {
		return 0;
	}
	double ao[100] = { 0 };
	double average = 0;
	double bao = 0;
	for (int i = 0; i < solves.size() - AoLength; i++) {
		double total = 0;
		double BestInAverage = std::numeric_limits<float>::max();;
		double WorstInAverage = 0;
		for (int j = 0; j < AoLength; j++) {
			ao[j] = solves[i + j].Time;
			total = total + ao[j];
			if (BestInAverage > ao[j]) {
				BestInAverage = ao[j];
			}
			if (WorstInAverage < ao[j]) {
				WorstInAverage = ao[j];
			}
		}
		total = total - (BestInAverage + WorstInAverage);
		double average = total / (AoLength - 2);
		if (bao == 0) {
			bao = average;
		}
		if (average < bao) {
			bao = average;
		}
	}
	return RoundMil_f(bao);
}

//iterate through instances of solve class and find best times and averages. Called when opening a new .sess file at aplication start or when switching sessions.
void RecountBestTimes() {
	BestTime = 0;
	bao5 = 0;
	bao12 = 0;
	bao100 = 0;
	for (int i = 0; i < solves.size() - 1; i++) {
		if (BestTime == 0) {
			BestTime = solves[0].Time;
		}
		if (solves[i].Time < BestTime) {
			BestTime = solves[i].Time;
		}
	}
	bao5 = GetBestAvg(5);
	bao12 = GetBestAvg(12);
	bao100 = GetBestAvg(10);
}

void printinfotoscreen() {
	std::cout << "Best time:	";
	secondstodisplay(BestTime);
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