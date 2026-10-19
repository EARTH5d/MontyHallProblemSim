#include <iostream>
#include <stdexcept>
#include <time.h>
#include <limits>

using namespace std;

int main() {

	int runs = 0;
	int car = 0;
	int playerPick = 0;
	int openDoor = 0;

	bool isInputValid = false;

	double timesThePlayerShouldStick = 0;
	double timesThePlayerShouldSwitch = 0;
	int timesThePlayerStick = 0;
	double timesThePlayerStick_wins = 0;
	double timesThePlayerStick_loses = 0;
	int timesThePlayerSwitch = 0;
	double timesThePlayerSwitch_wins = 0;
	double timesThePlayerSwitch_loses = 0;
	
	string badInput;

	srand(time(0));

	while (!isInputValid){
		cout << "How many runs do you want want to do: ";
		cin >> runs;
		if(cin.fail()){ //Checks for type mismacth.
			
			cin.clear(); //Clear the failbit.
			cin >> badInput; //Exract the bad input.
			if (badInput == "default") { //Check to see if it is default.
				runs = 100000000;
			} else {
				cerr << "Sorry, but " << badInput << " is an invalid input. Must enter a postive intger." << endl;
				cout << "Please try agian and enter a postive intger (A whole number greater than 0)." << endl;
        	}
			
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore the remianing inputs.
		}
		if (runs <= 0){
			cout << "Sorry. " << runs << " is not a postive intger. Thus it is impossible to do " << runs << " runs of the simulation. " << endl
			<< "Please try agian and enter a postive intger (A whole number greater than 0)." << endl;
		} else {
			isInputValid = true;
		}
	}

	for (int i = 0; i < runs; i++){
		car = rand() % 3;
		playerPick = rand() % 3;
		do {
			openDoor = rand() % 3;
		}  while ((openDoor == playerPick) || (openDoor == car));

		//cout << "the Player picker is door #" << playerPick + 1 << ". The host opened door #" << openDoor + 1 << ". ";
		if (playerPick == car){
			//cout << "The player intially picked the car!!!" << endl;
			timesThePlayerShouldStick++;
		} else {
			//cout << "The player intially picked a goat" << endl;
			timesThePlayerShouldSwitch++;
		}
		if (rand() % 2 == 0){
			int j = 0;
			while((j == playerPick) || (j == openDoor)){
				j++;
			}
			playerPick = j;
			//cout << "The player switched" << endl;
			timesThePlayerSwitch++;
			playerPick == car ? timesThePlayerSwitch_wins++ : timesThePlayerSwitch_loses++;
		} else {
			//cout << "The player sticked" << endl;
			timesThePlayerStick++;
			playerPick == car ? timesThePlayerStick_wins++ : timesThePlayerStick_loses++;
		}
	}

	cout << endl << "The player should have stick to their door " << ((timesThePlayerShouldStick * 100)/ runs) << "% of the time." << endl;
	cout << "The player should have switch " << ((timesThePlayerShouldSwitch * 100)/ runs) << "% of the time." << endl;
	
	cout << "Out of " << runs << " runs of the simluation the player... " << endl;
	cout << "\tSwitched " << (((timesThePlayerSwitch_wins + timesThePlayerSwitch_loses) * 100) / runs) << " of the time, and... " << endl;  
	cout << "\t\tWon:" << endl;
	cout << "\t\t\t" << ((timesThePlayerSwitch_wins * 100) / timesThePlayerSwitch) << "% of the times they choosed to switch." << endl;
	cout << "\t\t\t" << ((timesThePlayerSwitch_wins * 100) / runs) << "% of the runs of the simulation." << endl;
	cout << "\t\tLosed:"  << endl;
	cout << "\t\t\t" << ((timesThePlayerSwitch_loses * 100) / timesThePlayerSwitch) << "% of the times  they choosed to switch." << endl;
	cout << "\t\t\t" << ((timesThePlayerSwitch_loses * 100) / runs) << "% of the runs of the simulation." << endl;
	cout << "\tStuck: " << (((timesThePlayerStick_wins + timesThePlayerStick_loses) * 100) / runs) << " of the time, and... " << endl;
	cout << "\t\tWon: " << endl;
	cout << "\t\t\t" <<  ((timesThePlayerStick_wins * 100) / timesThePlayerStick) << "% of the times they stuck thier initial pick." << endl;
	cout << "\t\t\t" <<  ((timesThePlayerStick_wins * 100) / runs) << "% of the runs of the simulation." << endl;
	cout << "\t\tLosed: " << endl;
	cout << "\t\t\t" << ((timesThePlayerStick_loses * 100) / timesThePlayerStick) << "% of the times they stuck thier initial pick." << endl;
	cout << "\t\t\t" <<  ((timesThePlayerStick_loses * 100) / runs) << "% of the runs of the simulation." << endl;
	cout << "\tIn total the Player won in " << (((timesThePlayerSwitch_wins + timesThePlayerStick_wins) * 100) / runs) << "% of the runs, ";
	cout << "And losed in " << (((timesThePlayerSwitch_loses + timesThePlayerStick_loses) * 100) / runs) << "% of them" << endl;

	return 0;
}