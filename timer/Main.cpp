#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <chrono>
#include <conio.h>
#include <stdio.h>
#include <thread>
#include <Windows.h>
#include "function header.h"
#include "debug timer class.h"

#define space 32
#define key_two 50
#define key_three 51
#define key_four 52
#define key_five 53
#define key_OH 111
#define key_x 120
#define backspace 8
#define plustwo 112
#define showsolves 97
#define deletespecificsolve 224

enum layers {
	two = 0, three = 1, four = 2, five = 3, OH = 4 
};
enum session_type {
	new_scramble, first_time, new_session, close
};
int session = three;
int current_type = first_time;
int newsess = four;

int main() {
	srand(time(NULL));
	int ch = 0;
	data_manager_f(current_type, session, newsess);
	Screen(0);
	while (ch != key_x) {
		ch = _getch();
		switch (ch) {
		case space:
			timer_f(session);
			data_manager_f(current_type, session, newsess);
			log("time saved");
			Screen(0);
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			break;
		case key_two:
			Screen(key_two);
			newsess = two;
			current_type = new_session;
			data_manager_f(current_type, session, newsess);
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			Screen(0);
			break;
		case key_three:
			Screen(key_three);
			newsess = three;
			current_type = new_session;
			data_manager_f(current_type, session, newsess);
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			Screen(0);
			break;
		case key_four:
			Screen(key_four);
			newsess = four;
			current_type = new_session;
			data_manager_f(current_type, session, newsess);
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			Screen(0);
 			break;
		case key_five:
			Screen(key_five);
			newsess = five;
			current_type = new_session;
			data_manager_f(current_type, session, newsess);
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			Screen(0);
			break;
		case key_OH:
			Screen(key_OH);
			newsess = OH;
			current_type = new_session;
			data_manager_f(current_type, session, newsess);
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			Screen(0);
			break;
		case backspace:
			deletesolve_f(false);
			break;
		case deletespecificsolve:
			deletesolve_f(true);
			break;
		case plustwo:
			plustwo_f();
			break;
		case showsolves:
			print_times_f();
		}
	}
	current_type = close;
	data_manager_f(current_type, session, newsess);
}

void typeswtch_f(int swtch) {
	current_type = swtch;
	log("switched current_type");
}

void sessionswtch_f(int swtch) {
	session = swtch;
	log("switched session");
}