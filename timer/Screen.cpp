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
	std::cout << get_time() << "\n";
 	std::cout << "avg:" << get_average_total_f() << "\n";
	std::cout << "ao5:" << get_average_f(5) << "\n";
	std::cout << "ao12:" << get_average_f(12) << "\n";
	std::cout << "ao100:" << get_average_f(100) << "\n";
	std::cout << "solve number " << currentsessionsize_f() << "\n";
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