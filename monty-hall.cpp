#include <iostream>
#include <time.h>

using namespace std;

int main() {

	int runs = 0; //100000000
	int car = 0;
	int playerPick = 0;
	int openDoor = 0;

	double timesThePlayerShouldStick = 0;
	double timesThePlayerShouldSwitch = 0;
	int timesThePlayerStick = 0;
	double timesThePlayerStick_wins = 0;
	double timesThePlayerStick_loses = 0;
	int timesThePlayerSwitch = 0;
	double timesThePlayerSwitch_wins = 0;
	double timesThePlayerSwitch_loses = 0;
	

	srand(time(0));

	while (runs <= 0){
		std::cout << "How many runs do you want want to do: ";
		std::cin >> runs;
		if (runs <= 0){
			cout << "Sorry. " << runs << " is not a postive intger. Thus it is impossible to do " << runs << "runs of the simulation. " << endl
			<< "Please try agian and enter a postive intger (A whole number greater than 0)." << endl;
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

	std::cout << endl << "The player should stick to their door " << ((timesThePlayerShouldStick * 100)/ runs) << "% of the time." << endl;
	std::cout << "The player should switch " << ((timesThePlayerShouldSwitch * 100)/ runs) << "% of the time." << endl;
	std::cout << "Perctage that the player: " << endl;
	std::cout << "switched and won: "  << ((timesThePlayerSwitch_wins * 100) / timesThePlayerSwitch) << ":" << ((timesThePlayerSwitch_wins * 100) / runs) << endl;
	std::cout << "switched and lose: " << ((timesThePlayerSwitch_loses * 100) / timesThePlayerSwitch) << ":" << ((timesThePlayerSwitch_loses * 100) / runs) << endl;
	std::cout << "stick and won: " << ((timesThePlayerStick_wins * 100) / timesThePlayerStick) << ":" << ((timesThePlayerStick_wins * 100) / runs) << endl;
	std::cout << "stick and lose: " << ((timesThePlayerStick_loses * 100) / timesThePlayerStick) << ":" << ((timesThePlayerStick_loses * 100) / runs) << endl;
	std::cout << (((timesThePlayerSwitch_wins + timesThePlayerStick_wins) * 100) / runs) << " : " << (((timesThePlayerSwitch_loses + timesThePlayerStick_loses) * 100) / runs) << endl;

	return 0;
}