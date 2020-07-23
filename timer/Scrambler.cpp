#include <iostream>
#include <vector>
#include <ctime>
#include "function header.h"

int rannum_f(int maxnum) {
	return (rand() % maxnum);
}

std::string twoandthree(int scramble_length, int gen) {
	const std::string moves[18] = { "F ", "F' ", "F2 ", "B ", "B' ", "B2 ", "U ", "U' ", "U2 ", "D ", "D' ", "D2 ", "L ", "L' ", "L2 ", "R ", "R' ", "R2 " };
	std::string scramble = "";
	int y = rannum_f(3);
	int x = rannum_f(gen);
	int xarray[25] = { 0 };

	scramble = moves[3 * x + y];
	int i = 0;
	xarray[i] = x;
	i++;

	while (i < 2) {
		x = rannum_f(gen);
		y = rannum_f(3);
		if (x != xarray[0]) {
			xarray[i] = x;
			scramble = scramble + moves[3 * x + y];
			i++;
		}
	}
	while (i < scramble_length) {
		x = rannum_f(gen);
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

std::string fourandfive(int scramble_length) {
	const std::string moves[36] = { "F ", "F' ", "F2 ", "Fw ", "Fw' ", "Fw2 ", "B ", "B' ", "B2 ", "Bw ", "Bw' ", "Bw2 ", "U ", "U' ", "U2 ", "Uw ", "Uw' ", "Uw2 ", "D ", "D' ", "D2 ", "Dw ", "Dw' ", "Dw2 ", "L ", "L' ", "L2 ", "Lw ", "Lw' ", "Lw2 ", "R ", "R' ", "R2 ", "Rw ", "Rw' ", "Rw2 " };
	std::string scramble = "";
	int x = rannum_f(6);
	int y = rannum_f(3);
	int xarray[60] = { 0 };

	scramble = scramble + moves[6 * x + y];
	int i = 0;
	xarray[i] = x;
	i++;

	while (i < 2) {
		x = rannum_f(6);
		y = rannum_f(3);
		if (x != xarray[0]) {
			xarray[i] = x;
			scramble = scramble + moves[6 * x + y];
			i++;
		}
	}
	while (i < scramble_length/2) {
		x = rannum_f(6);
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
	scramble = scramble + "\n";
	int yarray[60] = { 0 };
	while (i < scramble_length) {
		x = rannum_f(6);
		y = rannum_f(6);
		if (xarray[i - 1] != x) {
			if (xarray[i - 2] == x) {
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
			if (xarray[i - 2] == x) {
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

std::string scramble_f(int layer_number) {
	switch (layer_number) {
	case 0:
		return twoandthree(9, 3);
		break;
	case 1:
		return twoandthree(25, 6);
		break;
	case 2:
		return fourandfive(50);
		break;
	case 3:
		return fourandfive(60);
		break;
	default:
		return 0;
	}
}