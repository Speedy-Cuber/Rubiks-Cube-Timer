#include <iostream>
#include <vector>
#include <ctime>
#include "function header.h"

int RandNum(int maxnum) {
	return (rand() % maxnum);
}

std::string Scrambler(int& layer_number) {
	int ScrambleLengthOne = 0;
	int ScrambleLength = 0;
	int gen = 0;
	if (layer_number == 0) {
		std::string Moves[9] = { "R ", "R' ", "R2 ", "U ", "U' ", "U2 ", "F ", "F' ", "F2 " };
		std::string Scramble = "";
		int x = RandNum(3);
		int y = RandNum(3);
		int XArray[60] = { 0 };
		Scramble = Moves[3 * x + y];
		int i = 0;
		XArray[i] = x;
		i++;
		while (i < 2) {
			x = RandNum(3);
			y = RandNum(3);
			if (x != XArray[0]) {
				XArray[i] = x;
				Scramble = Scramble + Moves[3 * x + y];
				i++;
			}
		}
		while (i < 9) {
			x = RandNum(3);
			y = RandNum(3);
			if (XArray[i - 1] != x) {
				if (XArray[i - 2] == x) {
					if ((x + XArray[i - 1]) != 1 && (x + XArray[i - 1]) != 5 && (x + XArray[i - 1]) != 9) {
						XArray[i] = x;
						Scramble = Scramble + Moves[3 * x + y];
						i++;
					}
				}
				else {
					XArray[i] = x;
					Scramble = Scramble + Moves[3 * x + y];
					i++;
				}
			}
		}
		return Scramble;
	}
	else if (layer_number == 1||layer_number == 4) {
		gen = 6;
		ScrambleLengthOne = 25;
		ScrambleLength = 0;
	}
	else if (layer_number == 2) {
		gen = 6;
		ScrambleLengthOne = 25;
		ScrambleLength = 50;
	}
	else if (layer_number == 3) {
		gen = 6;
		ScrambleLengthOne = 30;
		ScrambleLength = 60;
	}
	else {
		log("Error in Scramble");
	}
	std::string Moves[36] = { "F  ", "F' ", "F2 ", "Fw ", "Fw' ", "Fw2 ", "B  ", "B' ", "B2 ", "Bw ", "Bw' ", "Bw2 ", "U  ", "U' ", "U2 ", "Uw ", "Uw' ", "Uw2 ", "D  ", "D' ", "D2 ", "Dw ", "Dw' ", "Dw2 ", "L  ", "L' ", "L2 ", "Lw ", "Lw' ", "Lw2 ", "R  ", "R' ", "R2 ", "Rw ", "Rw' ", "Rw2 " };
	std::string Scramble = "";
	int x = RandNum(gen);
	int y = RandNum(3);
	int XArray[60] = { 0 };
	Scramble = Scramble + Moves[6 * x + y];
	int i = 0;
	XArray[i] = x;
	i++;
	while (i < 2) {
		x = RandNum(gen);
		y = RandNum(3);
		if (x != XArray[0]) {
			XArray[i] = x;
			Scramble = Scramble + Moves[6 * x + y];
			i++;
		}
	}
	while (i < ScrambleLengthOne) {
		x = RandNum(gen);
		y = RandNum(3);
		if (XArray[i - 1] != x) {
			if (XArray[i - 2] == x) {
				if ((x + XArray[i - 1]) != 1 && (x + XArray[i - 1]) != 5 && (x + XArray[i - 1]) != 9) {
					XArray[i] = x;
					Scramble = Scramble + Moves[6 * x + y];
					i++;
				}
			}
			else {
				XArray[i] = x;
				Scramble = Scramble + Moves[6 * x + y];
				i++;
			}
		}
	}
	if (ScrambleLength == 50) {
		Scramble = Scramble + "						 ";
	}
	else if (ScrambleLength == 60) {
		Scramble = Scramble + "					";

	}
	int YArray[60] = { 0 };
	while (i < ScrambleLength) {
		x = RandNum(6);
		y = RandNum(6);
		if (XArray[i - 1] != x) {
			if (XArray[i - 2] == x) {
				if ((x + XArray[i - 1]) != 1 && (x + XArray[i - 1]) != 5 && (x + XArray[i - 1]) != 9) {
					XArray[i] = x;
					YArray[i] = y;
					Scramble = Scramble + Moves[6 * x + y];
					i++;
				}
			}
			else if ((x + XArray[i - 1]) != 1 && (x + XArray[i - 1]) != 5 && (x + XArray[i - 1]) != 9) {
					XArray[i] = x;
					YArray[i] = y;
					Scramble = Scramble + Moves[6 * x + y];
					i++;
			}
		}
		else if ((YArray[i - 1] > 2 && y < 3) || (YArray[i - 1] < 3 && y > 2)) {
			if (XArray[i - 2] == x && XArray[i - 1] != x) {
				if ((x + XArray[i - 1]) != 1 && (x + XArray[i - 1]) != 5 && (x + XArray[i - 1]) != 9) {
					XArray[i] = x;
					YArray[i] = y;
					Scramble = Scramble + Moves[6 * x + y];
					i++;
				}
			}
		}
	}
	return Scramble;
}