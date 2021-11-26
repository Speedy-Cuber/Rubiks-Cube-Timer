#include <iostream>
#include <string>
#include <chrono>
#include "function_header.h"

#define space 32
#define key_two 50
#define key_three 51
#define key_four 52
#define key_five 53
#define key_OH 111

void defaultscreen() {
	system("clear");
	std::cout << get_scramble_f() << "\n";
	std::cout << "                                                                                            "  << "\n";
	std::cout << "Last solve:	";
	secondstodisplay(get_time());
	std::cout << "\n";
	printinfotoscreen();
	std::cout << "Total number of solves in session:	" << currentsessionsize_f() -1 << "\n";
}

void screen_f(int keypressed) {
	switch (keypressed) {
	case key_two:
		system("clear");
		std::cout << "switched to 2x2 session";
		break;
	case key_three:
		system("clear");
		std::cout << "switched to 3x3 session";
		break;
	case key_four:
		system("clear");
		std::cout << "switched to 4x4 session";
		break;
	case key_five:
		system("clear");
		std::cout << "switched to 5x5 session";
		break;
	case key_OH:
		system("clear");
		std::cout << "switched to OH session";
		break;
	case 0:
		defaultscreen();
		break;
	}
}
