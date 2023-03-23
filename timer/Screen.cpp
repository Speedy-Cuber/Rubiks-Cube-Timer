#include <iostream>
#include <string>
#include <chrono>
#include "function header.h"
#include <thread>

#define space 32
#define key_two 50
#define key_three 51
#define key_four 52
#define key_five 53
#define key_OH 111

void DefaultScreen() {
	system("cls");
	std::cout << GetScramble() << "\n";
	std::cout << "                                                                                            "  << "\n";
	std::cout << "Last solve:	";
	secondstodisplay(GetTime());
	std::cout << "\n";
	printinfotoscreen();
	std::cout << "Total number of solves in session:	" << CurrentSessionSize() -1 << "\n";
}

void MessageScreen(std::string Message) {
	system("cls");
	std::cout << Message;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}