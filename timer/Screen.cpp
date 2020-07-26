#include <iostream>
#include <string>
#include <chrono>
#include "function header.h"

#define space 32
#define key_two 50
#define key_three 51
#define key_four 52
#define key_five 53

void defaultscreen() {
	system("cls");
	std::cout << get_scramble_f() << "\n";
	std::cout << "                                                                                            "  << "\n";
	std::cout << "Last solve:	"<<get_time() << "\n";
	printinfotoscreen();
	std::cout << "Total number of solves in session:	" << currentsessionsize_f() -1 << "\n";
}

void screen_f(int keypressed) {
	switch (keypressed) {
	case key_two:
		system("cls");
		std::cout << "switched to 2x2 session";
		break;
	case key_three:
		system("cls");
		std::cout << "switched to 3x3 session";
		break;
	case key_four:
		system("cls");
		std::cout << "switched to 4x4 session";
		break;
	case key_five:
		system("cls");
		std::cout << "switched to 5x5 session";
		break;
	case 0:
		defaultscreen();
		break;
	}
}