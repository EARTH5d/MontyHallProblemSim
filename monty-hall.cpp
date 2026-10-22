#include "monty-hall.h"

int main() {

	bool isInputValid = false;

	unsigned int threadCount = thread::hardware_concurrency();

	unsigned long runs = 0;
	unsigned long runPerThd_base = 0;
	unsigned long runPerThd_remainder = 0;
	unsigned int seed = time(nullptr); //Seed for the threads.

	Results totalStats;
	string input;
	string temp;
	size_t pos = 0;

	bool isNegNumber = true;

	while (!isInputValid){
		std::cout << "How many runs do you want want to do: ";
		getline(cin, input, '\n');
		
		temp = input;
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		if (temp == "default") { //Check to see if it is "default" and check runs to the default number of 100,000,000.
			runs = 100000000;
			isInputValid = true;
			break;
		}

		if (input.empty()){
			std::cout << "Sorry, it appear you did not enter anything at all. Please try agian." << endl;
			continue;
		}

		if (input.at(0) == '-'){
			
			if (all_of(next(input.begin()), input.end(), ::isdigit))
				std::cout << "Sorry, but " << input << " is a negative number.";
			else 
				std::cout << "Sorry, but " << input << " is a not an not a intger number.";
			
			std::cout << invalid_input_message(input);
			continue;
		}

		try {
			runs = stoul(input, &pos);

			if (pos != input.length()){ //Check to see if the user really did enter an only a string of digits.
				std::cout << "Sorry, but " << input << " is a not an not a intger number." << invalid_input_message(input);
				continue;
			}
			if (runs == 0){
				std::cout << "Sorry, but 0 runs equal no runs." << invalid_input_message(input);
				continue;
			}
			isInputValid = true;

		} catch (invalid_argument const& e){ //If the input is of type mismacthed type.
			std::cout << "Sorry, but " << input << " is not a postive intger." << invalid_input_message(input);
		} catch (out_of_range const& e){ //If the input is out of range.
			std::cout << "Sorry, but " << input << " greater than 4,294,967,295." << endl;
			std::cout << "Please try agian and enter a postive intger that is bewteen 1 and 4,294,967,295." << endl;
		}

		
	}

	std::cout << endl << "Runing " << runs << " simulations of the Monty hall problem." << endl;

	if ((threadCount > 1) && (runs > 50)) {
		if (runs < threadCount){ //Just in cases.
			threadCount = runs;
		}
		vector<Results> threadStats(threadCount); //Vector to contain the results of each thread.
		vector<thread> threads;

		runPerThd_base = runs / threadCount;
		runPerThd_remainder = runs % threadCount;

		for (unsigned long i = 0; i < threadCount; i++) {
			unsigned long runPerThd = runPerThd_base + (i < runPerThd_remainder ? 1 : 0); //Assigned the remainder to certian threads.
			
			threads.emplace_back([&, i, runPerThd]() {threadStats[i] = run_monty_hall_problem(runPerThd, 4, seed + i);}); //Create the threads.
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
		totalStats = run_monty_hall_problem(runs, 4, seed);
	}

	std::cout << endl; 
	std::cout << "The player should have stuck with their choosen door " << ((totalStats.timesPlayerShldStuck * 100)/ runs) << "% of the time." << endl;
	std::cout << "The player should have switched over to the other door " << ((totalStats.timesPlayerShldSwitch * 100)/ runs) << "% of the time." << endl;
	
	std::cout << "Out of " << runs << " runs of the simluation the player... " << endl;
	std::cout << "\tSwitched " << calculate_percentage((totalStats.timesPlayerSwitch_wins + totalStats.timesPlayerSwitch_loses), runs) << "% of the time, and... " << endl;  
	std::cout << "\t\tWon:" << endl;
	std::cout << "\t\t\t" << calculate_percentage(totalStats.timesPlayerSwitch_wins, totalStats.timesPlayerSwitch) << "% of the times they choosed to switch." << endl;
	std::cout << "\t\t\t" << calculate_percentage(totalStats.timesPlayerSwitch_wins, runs) << "% of the runs of the simulation." << endl;
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

Results run_monty_hall_problem (unsigned long runs, unsigned long doors, unsigned int seed) {
	
	Results stats;

	mt19937 rng(seed);
    uniform_int_distribution<unsigned long> door(0, doors - 1);
    bernoulli_distribution coin(0.5);
	
	unsigned long car = 0;
	unsigned long closedDoor = -1;
	unsigned long playerPick = 0;
	unsigned long openDoor = 0;
	//set<unsigned long> closedDoors = {};
	set<unsigned long> openDoors = {};

	bool wasOpen = false;
	
	for (unsigned long i = 0; i < runs; i++){
		car = door(rng);
		playerPick = door(rng);
		
		if (playerPick != car){
			closedDoor = car;
		} else {
			do {
				closedDoor = door(rng);
			}  while ((closedDoor == playerPick) || (closedDoor == car));
		}

		for (int i = 0; i < doors - 2; i++)
			do {
				openDoor = door(rng);
				if ((openDoor == playerPick) || (openDoor == closedDoor))
					wasOpen = false;
				else
					wasOpen = openDoors.insert(openDoor).second;
			}  while (wasOpen == false);
		/*} else {
			do {
				openDoor = door(rng);
			}  while ((openDoor == playerPick) || (openDoor == car));
		}*/
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
			while((j == playerPick) || (openDoors.contains(j))){
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

		openDoors.clear();
	}

	return stats;
}

string invalid_input_message(string input){
	return " Thus it is impossible to do " + input + " runs of the simulation. \n Please try agian and enter a postive intger that is bewteen 1 and 4,294,967,295. \n";
}

double calculate_percentage(double relative_value, unsigned long reference_value){
	double percentage = (relative_value / reference_value) * 100;
	return isnan(percentage) ? 0.0 : percentage;
}