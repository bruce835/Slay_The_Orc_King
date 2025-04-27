#include "PlayerController.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <thread>

using namespace std;

string playerName;
string playerInput;
bool gameStarted = false;
int playerRoom;
bool playerMoved = false;
PlayerController* globalPlayerController = nullptr;

int pIn() {
	cout << playerName << ": ";
	return 0;
}

bool getPlayerInput(string &input) {
	if (input == "help") {
		cout << "This is a list of basic commands: " << endl;
		cout << "quit: save and quit game.\n";
		cout << "north/southwest/east, etc.: move from room to room.\n";
		pIn();
		return true;
	}
		else if (input == "quit") {
			cout << endl;
			globalPlayerController->save();
			cout << "SAFE TRAVELS, ADVENTURER.\n";
			exit(0);
	}
		else {
			return false;
		}
}

class Room {
public:
	int getRoom1Input() {
		std::cin >> playerInput;
		if (getPlayerInput(playerInput)) {
			return 1;
		}
		while (true) {
			if (playerInput == "north") {
				cout << "Moving North" << endl;
				playerRoom = 2;
				playerMoved = true;
				return 3;
			}
			else  {
				cout << "NOT A VALID COMMAND. WHO HIRED YOU, ANYWAYS?\n";
				pIn();
				break;
			}
		}
		return 1;
	}

	int room1() {
		playerRoom = 1;
		cout << playerName << ": AAGH! What is that stench?" << endl;
		pIn();
		while (true && gameStarted == true) {
			if(getRoom1Input() == 3) {
				break;
			}
		}
		return 3;
	}

	int getRoom2Input() {
		std::cin >> playerInput;
		if (getPlayerInput(playerInput)) {
			return 1;
		}

		while (true) {
		if (playerInput == "south") {
				cout << "Moving South" << endl;
				playerRoom = 1;
				playerMoved = true;
				return 3;
			}
		else  {
                                cout << "NOT A VALID COMMAND. WHO HIRED YOU, ANYWAYS?\n";
				pIn();
				break;
                        }
		}
		return 1;
	}

	int room2() {
		playerRoom = 2;
		cout << playerName << ": This isn't too much better, smell wise" << endl;
		pIn();

		while (true && gameStarted == true) {
			if(getRoom2Input() == 3) {
				break;
			}
		}
		return 3;
	}

	using roomFunction = function<int()>;
	int setRoom() {
		map<int, roomFunction> roomMap = {{1, std::bind(&Room::room1, this)},
										  {2, std::bind(&Room::room2, this)}};

		auto it = roomMap.find(playerRoom);
		if (it != roomMap.end()) {
			return it->second();
		}

		return 2;
	}
};

void onPlayerMove() {
	while (true) {
		if (playerMoved == true) {
			Room currentRoom;
			globalPlayerController->playerCurrentRoom = playerRoom;
			playerMoved = false;
			currentRoom.setRoom();
		}
	}
}

int main() {
	cout << "Welcome To SLAY THE ORC KING" << endl;
	cout << "..." << endl;
	cout << "What is your name, adventurer?" << endl;
	cout << "Adventurer: ";
	cin >> playerName;

	cout << endl;
	cout << "INITIALIZING...\n";
	PlayerController playerController(playerName);
	playerController.player = playerName;
	globalPlayerController = &playerController;

	if (globalPlayerController->stage > 1) {
	cout << "Greetings, " << playerName << "." << endl;
	cout << "Now, where were we?\n\n";
	}
		else {
			cout << "In the faraway world of Edoc-Dab, people are dying.\n";
			cout << "The orc king Gromulech has gone mad after reigning\n";
			cout << "for three hundred years. His paranoia has grown,\n";
			cout << "and he believes humans will destroy the peace between the two peoples.\n";
			cout << "Ruling with an iron fist, he began opressing the humans.\n";
			cout << "They were helplessly made captive by the orcs' overwhelming might.\n";
			cout << "But some can still stand. Some can still lead this fallen people\n";
			cout << "from the terror of the orc king. WHO WILL RISE? WHO WILL FIGHT?\n";
			cout << "WHO CAN DEFY THE WILL OF AN MADMAN COMMANDING LEGIONS OF OX-STRONG ORCS?\n";
			cout << "...\n";
			cout << "Who will SLAY THE ORC KING?\n\n";
			globalPlayerController->stage++;
		}
	gameStarted = true;
	Room rooms;
	playerRoom = playerController.playerCurrentRoom;

	if (gameStarted == true) {
		rooms.setRoom();
		thread playerMoveThread(onPlayerMove);
		playerMoveThread.join();
	}
	return 0;
}
