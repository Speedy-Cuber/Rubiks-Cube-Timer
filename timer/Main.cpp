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
	DataManager(current_type, session, newsess);
	DefaultScreen();
	while (ch != key_x) {
		ch = _getch();
		switch (ch) {
		case space:
			Timer(session);
			DataManager(current_type, session, newsess);
			log("time saved");
			DefaultScreen();
			break;
		case key_two:
			MessageScreen("switched to 2x2 session");
			newsess = two;
			current_type = new_session;
			DataManager(current_type, session, newsess);
			DefaultScreen();
			break;
		case key_three:
			MessageScreen("switched to 3x3 session");
			newsess = three;
			current_type = new_session;
			DataManager(current_type, session, newsess);
			DefaultScreen();
			break;
		case key_four:
			MessageScreen("switched to 4x4 session");
			newsess = four;
			current_type = new_session;
			DataManager(current_type, session, newsess);
			DefaultScreen();
 			break;
		case key_five:
			MessageScreen("switched to 5x5 session");
			newsess = five;
			current_type = new_session;
			DataManager(current_type, session, newsess);
			DefaultScreen();
			break;
		case key_OH:
			MessageScreen("switched to OH session");
			newsess = OH;
			current_type = new_session;
			DataManager(current_type, session, newsess);
			DefaultScreen();
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
	DataManager(current_type, session, newsess);
}

void TypeSwitch(int swtch) {
	current_type = swtch;
	log("switched current_type");
}

void SessionSwitch(int swtch) {
	session = swtch;
	log("switched session");
}