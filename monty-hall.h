#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <time.h>
#include <cmath>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include <thread>
#include <cstdint>

using namespace std;

struct Results { //A struct for holding all the data in the statisics of the results of the simulation.
	double timesPlayerShldStuck = 0;
	double timesPlayerShldSwitch = 0;
	double timesPlayerStuck_wins = 0;
	double timesPlayerStuck_loses = 0;
	double timesPlayerSwitch_wins = 0;
	double timesPlayerSwitch_loses = 0;
	unsigned long timesPlayerSwitch = 0;
	unsigned long timesPlayerStuck = 0;
};

Results run_monty_hall_problem (unsigned long runs, unsigned long doors, unsigned int seed);
string invalid_input_message(string input);
double calculate_percentage(double relative_value, unsigned long reference_value);