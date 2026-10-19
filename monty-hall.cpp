#include <iostream>
#include <stdexcept>
#include <string>
#include <time.h>
#include <algorithm>

using namespace std;

int main() {

	unsigned long runs = 0;
	unsigned long car = 0;
	unsigned long playerPick = 0;
	unsigned long openDoor = 0;

	bool isInputValid = false;

	double timesThePlayerShouldStick = 0;
	double timesThePlayerShouldSwitch = 0;
	unsigned long timesThePlayerStick = 0;
	double timesThePlayerStick_wins = 0;
	double timesThePlayerStick_loses = 0;
	unsigned long timesThePlayerSwitch = 0;
	double timesThePlayerSwitch_wins = 0;
	double timesThePlayerSwitch_loses = 0;
	
	string input;
	std::size_t pos = 0;

	srand(time(0));

	while (!isInputValid){
		std::cout << "How many runs do you want want to do: ";

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
				cerr << e.what() << endl;
				cerr << "Invalid Input, not a number." << endl;
				std::cout << "Sorry, but " << input << " is not a postive intger. Thus it is impossible to do " << input << " runs of the simulation. " << endl;
				std::cout << "Please try agian and enter a postive intger in the range of 1 and 4,294,967,295." << endl;
				continue;
        	}
		} catch (out_of_range const& e){
			cerr << e.what() << endl;
			cerr << "Invalid Input, out of range." << endl;
			std::cout << "Sorry, but " << input << " is out of the range of 1 and 4,294,967,295." << endl;
			std::cout << "Please try agian and enter a postive intger bewteen 1 and 4,294,967,295." << endl;
		}

		if (runs > 0){
			isInputValid = true;
		}
	}

	for (int i = 0; i < runs; i++){
		car = rand() % 3;
		playerPick = rand() % 3;
		do {
			openDoor = rand() % 3;
		}  while ((openDoor == playerPick) || (openDoor == car));

		//std::cout << "the Player picker is door #" << playerPick + 1 << ". The host opened door #" << openDoor + 1 << ". ";
		if (playerPick == car){
			//std::cout << "The player intially picked the car!!!" << endl;
			timesThePlayerShouldStick++;
		} else {
			//std::cout << "The player intially picked a goat" << endl;
			timesThePlayerShouldSwitch++;
		}
		if (rand() % 2 == 0){
			int j = 0;
			while((j == playerPick) || (j == openDoor)){
				j++;
			}
			playerPick = j;
			//std::cout << "The player switched" << endl;
			timesThePlayerSwitch++;
			playerPick == car ? timesThePlayerSwitch_wins++ : timesThePlayerSwitch_loses++;
		} else {
			//std::cout << "The player sticked" << endl;
			timesThePlayerStick++;
			playerPick == car ? timesThePlayerStick_wins++ : timesThePlayerStick_loses++;
		}
	}

	std::cout << endl; 
	std::cout << "The player should have stuck with their choosen door " << ((timesThePlayerShouldStick * 100)/ runs) << "% of the time." << endl;
	std::cout << "The player should have switched over to the other door " << ((timesThePlayerShouldSwitch * 100)/ runs) << "% of the time." << endl;
	
	std::cout << "Out of " << runs << " runs of the simluation the player... " << endl;
	std::cout << "\tSwitched " << (((timesThePlayerSwitch_wins + timesThePlayerSwitch_loses) * 100) / runs) << "% of the time, and... " << endl;  
	std::cout << "\t\tWon:" << endl;
	std::cout << "\t\t\t" << ((timesThePlayerSwitch_wins * 100) / timesThePlayerSwitch) << "% of the times they choosed to switch." << endl;
	std::cout << "\t\t\t" << ((timesThePlayerSwitch_wins * 100) / runs) << "% of the runs of the simulation." << endl;
	std::cout << "\t\tLosed:"  << endl;
	std::cout << "\t\t\t" << ((timesThePlayerSwitch_loses * 100) / timesThePlayerSwitch) << "% of the times  they choosed to switch." << endl;
	std::cout << "\t\t\t" << ((timesThePlayerSwitch_loses * 100) / runs) << "% of the runs of the simulation." << endl;
	std::cout << "\tStuck " << (((timesThePlayerStick_wins + timesThePlayerStick_loses) * 100) / runs) << "% of the time, and... " << endl;
	std::cout << "\t\tWon: " << endl;
	std::cout << "\t\t\t" <<  ((timesThePlayerStick_wins * 100) / timesThePlayerStick) << "% of the times they stuck thier initial pick." << endl;
	std::cout << "\t\t\t" <<  ((timesThePlayerStick_wins * 100) / runs) << "% of the runs of the simulation." << endl;
	std::cout << "\t\tLosed: " << endl;
	std::cout << "\t\t\t" << ((timesThePlayerStick_loses * 100) / timesThePlayerStick) << "% of the times they stuck thier initial pick." << endl;
	std::cout << "\t\t\t" <<  ((timesThePlayerStick_loses * 100) / runs) << "% of the runs of the simulation." << endl;
	std::cout << "In total they won in " << (((timesThePlayerSwitch_wins + timesThePlayerStick_wins) * 100) / runs) << "% of the runs, " << endl;
	std::cout << "And they losed in " << (((timesThePlayerSwitch_loses + timesThePlayerStick_loses) * 100) / runs) << "% of them" << endl;

	return 0;
}