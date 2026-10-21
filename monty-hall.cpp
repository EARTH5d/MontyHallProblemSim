#include <iostream>
#include <stdexcept>
#include <string>
#include <time.h>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <cstdint>

using namespace std;

struct Results {
	/* data */
	double timesPlayerShldStuck = 0;
	double timesPlayerShldSwitch = 0;
	double timesPlayerStuck_wins = 0;
	double timesPlayerStuck_loses = 0;
	double timesPlayerSwitch_wins = 0;
	double timesPlayerSwitch_loses = 0;
	unsigned long timesPlayerSwitch = 0;
	unsigned long timesPlayerStuck = 0;
};

Results run_monty_hall_problem (unsigned long runs, unsigned int seed);
double calculate_percentage(double relative_value, unsigned long reference_value);

int main() {

	bool isInputValid = false;

	unsigned int threadCount = std::thread::hardware_concurrency();

	unsigned long runs = 0;
	unsigned long runPerThd_base = 0;
	unsigned long runPerThd_remainder = 0;
	unsigned int seed = time(nullptr); //Seed for the threats.

	Results totalStats;
	
	string input;
	size_t pos = 0;

	while (!isInputValid){
		cout << "How many runs do you want want to do: ";
		try {
			getline(cin, input, '\n');
			if (input.at(0) == '-'){
				throw out_of_range("Negative numbers are out of range.");
			}
			runs = stoul(input, &pos);
		
			if (pos != input.length()){ //Check to see if it is a decimal instead of an intger.
				cerr << "Invalid Input, decimal." << endl;
				std::cout << "Sorry, but " << input << " is not a postive intger. Thus it is impossible to do " << input << " runs of the simulation. " << endl;
				std::cout << "Please try agian and enter a postive intger in the range of 1 and 4,294,967,295." << endl;
				continue;
			}

			if (runs == 0){
				throw out_of_range("The number zero (0) is out of range.");
			}

		} catch (invalid_argument const& e){ //If there is a type mismacthed.
			string temp = input;
			transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			if (temp == "default") { //Check to see if it is "default" and check runs to the default number of 100,000,000.
				runs = 100000000;
			} else { //Otherwises it is an invalid type.
				cerr << "Invalid Input, not a number. \"" << e.what() <<"\"" << endl;
				std::cout << "Sorry, but " << input << " is not a postive intger. Thus it is impossible to do " << input << " runs of the simulation. " << endl;
				std::cout << "Please try agian and enter a postive intger bewteen 1 and 4,294,967,295." << endl;
				continue;
			}
		} catch (out_of_range const& e){
			cerr << "Invalid Input, out of range. \"" << e.what() <<"\"" << endl;
			std::cout << "Sorry, but " << input << " is out of the range of 1 and 4,294,967,295." << endl;
			std::cout << "Please try agian and enter a postive intger within that range." << endl;
			continue;
		}

		isInputValid = true;
	}

	cout << endl << "Runing " << runs << " simulations of the Monty hall problem." << endl;

	if ((threadCount > 1) && (runs > 50)) {
		if (runs < threadCount){
			threadCount = runs;
		}
		vector<Results> threadStats(threadCount); //Vector to contain the results of each thread.
		vector<thread> threads;

		runPerThd_base = runs / threadCount;
		runPerThd_remainder = runs % threadCount;

		for (unsigned long i = 0; i < threadCount; i++) {
			unsigned long runPerThd = runPerThd_base + (i < runPerThd_remainder ? 1 : 0); //Assigned the remainder to certian threads.
			
			threads.emplace_back([&, i, runPerThd]() {threadStats[i] = run_monty_hall_problem(runPerThd, seed + i);}); //Create the threads.
		}
		
		for (auto& t : threads) { // Wait for all threads to finish.
			t.join();
		}

		for (const auto& t : threadStats) { //Add the results of each to the total statistics.
			totalStats.timesPlayerShldSwitch += t.timesPlayerShldSwitch;
			totalStats.timesPlayerShldStuck += t.timesPlayerShldStuck;
			totalStats.timesPlayerStuck_wins += t.timesPlayerStuck_wins;
			totalStats.timesPlayerStuck_loses += t.timesPlayerStuck_loses;
			totalStats.timesPlayerSwitch_wins += t.timesPlayerSwitch_wins;
			totalStats.timesPlayerSwitch_loses += t.timesPlayerSwitch_loses;
			
			totalStats.timesPlayerSwitch += t.timesPlayerSwitch;
			totalStats.timesPlayerStuck += t.timesPlayerStuck;
		}

	} else {
		totalStats = run_monty_hall_problem(runs, seed);
	}

	std::cout << endl; 
	std::cout << "The player should have stuck with their choosen door " << ((totalStats.timesPlayerShldStuck * 100)/ runs) << "% of the time." << endl;
	std::cout << "The player should have switched over to the other door " << ((totalStats.timesPlayerShldSwitch * 100)/ runs) << "% of the time." << endl;
	
	std::cout << "Out of " << runs << " runs of the simluation the player... " << endl;
	std::cout << "\tSwitched " << calculate_percentage((totalStats.timesPlayerSwitch_wins + totalStats.timesPlayerSwitch_loses), runs) << "% of the time, and... " << endl;  
	std::cout << "\t\tWon:" << endl;
	std::cout << "\t\t\t" << calculate_percentage(totalStats.timesPlayerSwitch_wins,totalStats.timesPlayerSwitch) << "% of the times they choosed to switch." << endl;
	std::cout << "\t\t\t" << calculate_percentage(totalStats.timesPlayerSwitch_wins,runs) << "% of the runs of the simulation." << endl;
	std::cout << "\t\tLosed:"  << endl;
	std::cout << "\t\t\t" << calculate_percentage(totalStats.timesPlayerSwitch_loses, totalStats.timesPlayerSwitch) << "% of the times  they choosed to switch." << endl;
	std::cout << "\t\t\t" << calculate_percentage(totalStats.timesPlayerSwitch_loses, runs) << "% of the runs of the simulation." << endl;
	std::cout << "\tStuck " << calculate_percentage((totalStats.timesPlayerStuck_wins + totalStats.timesPlayerStuck_loses), runs) << "% of the time, and... " << endl;
	std::cout << "\t\tWon: " << endl;
	std::cout << "\t\t\t" <<  calculate_percentage(totalStats.timesPlayerStuck_wins, totalStats.timesPlayerStuck) << "% of the times they stuck thier initial pick." << endl;
	std::cout << "\t\t\t" <<  calculate_percentage(totalStats.timesPlayerStuck_wins, runs) << "% of the runs of the simulation." << endl;
	std::cout << "\t\tLosed: " << endl;
	std::cout << "\t\t\t" << calculate_percentage(totalStats.timesPlayerStuck_loses, totalStats.timesPlayerStuck) << "% of the times they stuck thier initial pick." << endl;
	std::cout << "\t\t\t" << calculate_percentage(totalStats.timesPlayerStuck_loses, runs) << "% of the runs of the simulation." << endl;
	std::cout << "In total they won in " << calculate_percentage((totalStats.timesPlayerSwitch_wins + totalStats.timesPlayerStuck_wins), runs) << "% of the runs, " << endl;
	std::cout << "And they losed in " << calculate_percentage((totalStats.timesPlayerSwitch_loses + totalStats.timesPlayerStuck_loses), runs) << "% of them" << endl;

	return 0;
}

Results run_monty_hall_problem (unsigned long runs, unsigned int seed) {
	
	Results stats;

	mt19937 rng(seed);
    uniform_int_distribution<unsigned long> door(0, 2);
    bernoulli_distribution coin(0.5);
	
	int car = 0;
	int playerPick = 0;
	int openDoor = 0;
	

	for (unsigned long i = 0; i < runs; i++){
		car = door(rng);
		playerPick = door(rng);
		do {
			openDoor = door(rng);
		}  while ((openDoor == playerPick) || (openDoor == car));

		//std::cout << "the Player picker is door #" << playerPick + 1 << ". The host opened door #" << openDoor + 1 << ". ";
		if (playerPick == car){
			//std::cout << "The player intially picked the car!!!" << endl;
			stats.timesPlayerShldStuck++;
		} else {
			//std::cout << "The player intially picked a goat" << endl;
			stats.timesPlayerShldSwitch++;
		}
		if (coin(rng)){
			int j = 0;
			while((j == playerPick) || (j == openDoor)){
				j++;
			}
			playerPick = j;
			//std::cout << "The player switched" << endl;
			stats.timesPlayerSwitch++;
			playerPick == car ? stats.timesPlayerSwitch_wins++ : stats.timesPlayerSwitch_loses++;
		} else {
			//std::cout << "The player sticked" << endl;
			stats.timesPlayerStuck++;
			playerPick == car ? stats.timesPlayerStuck_wins++ : stats.timesPlayerStuck_loses++;
		}
	}

	return stats;
}

double calculate_percentage(double relative_value, unsigned long reference_value){
	double percentage = (relative_value / reference_value) * 100;
	return isnan(percentage) ? 0.0 : percentage;
}