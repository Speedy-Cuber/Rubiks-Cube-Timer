#include <iostream>
#include <vector>
#include <ctime>
#include "function header.h"

int rannum_f(int maxnum) {
	return (rand() % maxnum);
}

std::string twobytwo(){
	std::string moves[9] = { "R ", "R' ", "R2 ", "U ", "U' ", "U2 ", "F ", "F' ", "F2 " };
	std::string scramble = "";
	int x = rannum_f(3);
	int y = rannum_f(3);
	int xarray[60] = { 0 };
	scramble = moves[3 * x + y];
	int i = 0;
	xarray[i] = x;
	i++;
	while (i < 2) {
		x = rannum_f(3);
		y = rannum_f(3);
		if (x != xarray[0]) {
			xarray[i] = x;
			scramble = scramble + moves[3 * x + y];
			i++;
		}
	}
	while (i < 9) {
		x = rannum_f(3);
		y = rannum_f(3);
		if (xarray[i - 1] != x) {
			if (xarray[i - 2] == x) {
				if ((x + xarray[i - 1]) != 1 && (x + xarray[i - 1]) != 5 && (x + xarray[i - 1]) != 9) {
					xarray[i] = x;
					scramble = scramble + moves[3 * x + y];
					i++;
				}
			}
			else {
				xarray[i] = x;
				scramble = scramble + moves[3 * x + y];
				i++;
			}
		}
	}
	return scramble;
}

std::string scramble_f(int layer_number) {
	int scramble_length_one = 0;
	int scramble_length = 0;
	std::string moves[36] = { "F  ", "F' ", "F2 ", "Fw ", "Fw' ", "Fw2 ", "B  ", "B' ", "B2 ", "Bw ", "Bw' ", "Bw2 ", "U  ", "U' ", "U2 ", "Uw ", "Uw' ", "Uw2 ", "D  ", "D' ", "D2 ", "Dw ", "Dw' ", "Dw2 ", "L  ", "L' ", "L2 ", "Lw ", "Lw' ", "Lw2 ", "R  ", "R' ", "R2 ", "Rw ", "Rw' ", "Rw2 " };
	int gen = 0;
	if (layer_number == 0) {
		return twobytwo();
	}
	else if (layer_number == 1) {
		gen = 6;
		scramble_length_one = 25;
		scramble_length = 0;
	}
	else if (layer_number == 2) {
		gen = 6;
		scramble_length_one = 25;
		scramble_length = 50;
	}
	else if (layer_number == 3) {
		gen = 6;
		scramble_length_one = 30;
		scramble_length = 60;
	}
	else {
		log("Error in scramble");
	}
	std::string scramble = "";
	int x = rannum_f(gen);
	int y = rannum_f(3);
	int xarray[60] = { 0 };
	scramble = scramble + moves[6 * x + y];
	int i = 0;
	xarray[i] = x;
	i++;
	while (i < 2) {
		x = rannum_f(gen);
		y = rannum_f(3);
		if (x != xarray[0]) {
			xarray[i] = x;
			scramble = scramble + moves[6 * x + y];
			i++;
		}
	}
	while (i < scramble_length_one) {
		x = rannum_f(gen);
		y = rannum_f(3);
		if (xarray[i - 1] != x) {
			if (xarray[i - 2] == x) {
				if ((x + xarray[i - 1]) != 1 && (x + xarray[i - 1]) != 5 && (x + xarray[i - 1]) != 9) {
					xarray[i] = x;
					scramble = scramble + moves[6 * x + y];
					i++;
				}
			}
			else {
				xarray[i] = x;
				scramble = scramble + moves[6 * x + y];
				i++;
			}
		}
	}
	if (scramble_length == 50) {
		scramble = scramble + "						 ";
	}
	else if (scramble_length == 60) {
		scramble = scramble + "					";

	}
	int yarray[60] = { 0 };
	while (i < scramble_length) {
		x = rannum_f(6);
		y = rannum_f(6);
		if (xarray[i - 1] != x) {
			if (xarray[i - 2] == x || scramble_length == 50) {
				if ((x + xarray[i - 1]) != 1 && (x + xarray[i - 1]) != 5 && (x + xarray[i - 1]) != 9) {
					xarray[i] = x;
					yarray[i] = y;
					scramble = scramble + moves[6 * x + y];
					i++;
				}
			}
			else {
				xarray[i] = x;
				scramble = scramble + moves[6 * x + y];
				i++;
			}
		}
		else if ((yarray[i - 1] > 3 && y < 4) || (yarray[i - 1] < 4 && y > 3)) {
			if (xarray[i - 2] == x || scramble_length ==50) {
				if ((x + xarray[i - 1]) != 1 && (x + xarray[i - 1]) != 5 && (x + xarray[i - 1]) != 9) {
					xarray[i] = x;
					yarray[i] = y;
					scramble = scramble + moves[6 * x + y];
					i++;
				}
			}
			else {
				xarray[i] = x;
				scramble = scramble + moves[6 * x + y];
				i++;
			}
		}
	}
	return scramble;
}