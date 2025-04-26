#include "PlayerController.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <thread>

using namespace std;

string playerRoomString;
int iplayerCharLine = 0;
string playerName;
string playerSavePath;
char playerNameDestination[10];
string playerInput;
bool gameStarted = false;
int playerRoom;
// Read/Write/Create playerSave File
fstream playerSave;
// Has player moved
bool playerMoved = false;
PlayerController* globalPlayerController = nullptr;

bool getPlayerInput(string &input) {
	if (input == "help") {
		cout << "This is a list of basic commands: " << endl;
		return true;
	}
		else if (input == "quit") {
			cout << "Quitting" << endl;
			exit(0);
	}
		else {
			return false;
		}
}

// Room Logic
class Room {
public:
	int getRoom1Input() {
		std::cin >> playerInput;
		if (getPlayerInput(playerInput)) {
			return 3;
		}
			bool validInput = false;
			if (playerInput == "north") {
				cout << "Moving North" << endl;
				playerRoom = 2;
				playerMoved = true;
				validInput = true;
			}
			if (validInput == false) {
				cout << "NOT A VALID COMMAND. WHO HIRED YOU, ANYWAYS?\n";
				cout << playerName << ": ";
			}
		return 3;
	}

	int room1() {
		playerRoom = 1;
		cout << playerName << ": AAGH! What is that stench?" << endl;
		cout << playerName << ": ";
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
			return 3;
		}

		bool validInput = false;
		if (playerInput == "south") {
				cout << "Moving South" << endl;
				playerRoom = 1;
				playerMoved = true;
				validInput = true;
			}
			if (validInput == false) {
                                cout << "NOT A VALID COMMAND. WHO HIRED YOU, ANYWAYS?\n";
                                cout << playerName << ": ";
                        }

		return 3;
	}

	int room2() {
		playerRoom = 2;
		cout << playerName << ": This isn't too much worse, smell wise" << endl;
		cout << playerName << ": ";

		while (true && gameStarted == true) {
			if(getRoom2Input() == 3) {
				break;
			}
		}
		return 3;
	}

	// Room Map
	using roomFunction = function<int()>;
	int room() {
		map<int, roomFunction> roomMap = {{1, std::bind(&Room::room1, this)},
										  {2, std::bind(&Room::room2, this)}};

		auto it = roomMap.find(playerRoom);
		if (it != roomMap.end()) {
			return it->second();
		}

		return 2;
	}
};

// Move Player
void onPlayerMove() {
	while (true) {
		if (playerMoved == true) {
			Room currentRoom;
			globalPlayerController->playerCurrentRoom = playerRoom;
			playerMoved = false;
			currentRoom.room();
		}
	}
}

int main() {
	// Start
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
		rooms.room();
		thread playerMoveThread(onPlayerMove);
		playerMoveThread.join();
	}
	return 0;
}
