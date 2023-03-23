#pragma once
//Scrambler.cpp
std::string Scrambler(int& layer_number);

void DataManager(int casenum, int layer_number, int layer_number_new);
std::string GetScramble();
void SetTime(float time);
float GetTime();

void log(std::string log);
void TypeSwitch(int swtch);
void SessionSwitch(int swtch);
//Screen.cpp
void DefaultScreen();
void MessageScreen(std::string);
//Timer.cpp
void Timer(int layer_number);
float RoundMil_f(float& time);
//Solve Storage.cpp
float GetTotalAverage();
int CurrentSessionSize();
void deletesolve_f(bool deletespecificsolve);
void plustwo_f();
void print_times_f();
void printinfotoscreen();
void secondstodisplay(float time);