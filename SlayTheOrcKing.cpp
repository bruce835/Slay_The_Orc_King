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
PlayerController playerController;
// Has player moved
bool playerMoved = false;
// Non-Room-Specific Input
bool generalInput = false;

bool getPlayerInput(
	/*ifstream& iplayerChar, ofstream& saveGame*/ string &input) {
	if (input == "help") {
		cout << "This is a list of basic commands: " << endl;
		return true;
	} else if (input == "quit") {
		cout << "Quitting"
			 << endl; /*TODO: Implement save functionality (probably in a
						 function nested within getPlayerInput)*/
		// iplayerChar.close();
		// saveGame << "Player Name : " << playerName << ";" << endl;
		// saveGame << playerRoom;
		// cout << playerRoom << endl;
		exit(0);
	} else {
		return false;
	}
}

// Room Logic
class Room {
public:
	int room1() {
		playerRoom = 1;
		cout << playerName << ": AAGH! What is that stench?" << endl;
		cout << playerName << ": ";
		while (true && gameStarted == true) {
			std::cin >> playerInput;
			// Check general commands first
			if (!getPlayerInput(playerInput)) {
				if (playerInput == "north") {
					cout << "Moving North" << endl;
					playerRoom = 2;
					playerMoved = true;
					break;
				}
			}
		}
		return 3;
	}
	int room2() {
		playerRoom = 2;
		cout << playerName << ": This isn't too much worse, smell wise" << endl;
		cout << playerName << ": ";

		while (true && gameStarted == true) {
			std::cin >> playerInput;

			if (!getPlayerInput(playerInput)) {
				if (playerInput == "south") {
					cout << "Moving South" << endl;
					playerRoom = 1;
					playerMoved = true;
					break;
				}
			}
		}

		return 3;
	}

	// Room Map
	using roomFunction = function<int()>;
	int room() {
		map<int, roomFunction> roomMap = {{1, std::bind(&Room::room1, this)},
										  {2, std::bind(&Room::room2, this)}};

		auto it = roomMap.find(playerRoom); // Find the room by playerRoom
		if (it != roomMap.end()) {
			return it->second(); // Call the function associated with the room
		}

		return 2;
	}
};

// Move Player
void onPlayerMove() {
	while (true) {
		if (playerMoved == true) {
			Room currentRoom;
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

	// Check playerSave
	playerSavePath = "PlayerSaves/" + playerName + ".txt";
	ifstream checkPlayerSave;
	checkPlayerSave.open(playerSavePath);

	// Create New PlayerSave
	if (!checkPlayerSave) {
		playerSave.open(playerSavePath,
						fstream::in | fstream::out | fstream::trunc);
		playerSave << "Player Name: " << playerName << ";" << endl;
		playerSave << "1";
		playerSave.close();
	}

	// Ensure Player Room is valid
	else {
		iplayerCharLine = 0;
		checkPlayerSave.clear();
		while (!checkPlayerSave.eof()) {
			iplayerCharLine++;
			getline(checkPlayerSave, playerRoomString);
			if (iplayerCharLine == 2) {
				if (!playerRoomString.empty() &&
					all_of(playerRoomString.begin(), playerRoomString.end(),
						   ::isdigit)) {
					cout << endl;
					cout << "playerRoomString: " << playerRoomString << endl;
					playerRoom = stoi(playerRoomString);
				} else {
					playerRoom = 1;
					playerSave.open(playerSavePath, fstream::in | fstream::out |
														fstream::trunc);
					playerSave << "Player Name: " << playerName << ";" << endl;
					playerSave << "1";
					playerSave.close();
				}
				break;
			}
		}
	}

	checkPlayerSave.seekg(13, istream::beg);
	checkPlayerSave.getline(playerNameDestination, 10, ';');
	cout << "Greetings, ";
	cout << playerNameDestination << endl << endl;
	; /*TODO: Fix player name not printing*/
	gameStarted = true;

	cout << endl;
	cout << "Initializing..." << endl;
	cout << "---" << endl;
	// Close playerSave
	checkPlayerSave.close();
	if (!checkPlayerSave.is_open()) {
		cout << "playerSave Closed" << endl;
	}

	ifstream iplayerChar(playerSavePath);

	// Get Save State
	if (!iplayerChar) {
		cerr << "Error: STOK002 iplayerChar Failed to Open";
	} else {
		cout << "iplayerCharOpened";
		cout << endl;
	}

	iplayerCharLine = 0;
	iplayerChar.clear();
	while (!iplayerChar.eof()) {
		iplayerCharLine++;
		getline(iplayerChar, playerRoomString);
		if (iplayerCharLine == 2) {
			if (!playerRoomString.empty() &&
				all_of(playerRoomString.begin(), playerRoomString.end(),
					   ::isdigit)) {
				cout << endl;
				cout << "playerRoomString: " << playerRoomString << endl;
				playerRoom = stoi(playerRoomString);
			} else {
				cerr << "Error: STOK001 Invalid player room data in save file."
					 << endl;
				cout << endl;
				cout << "playerRoomString: " << "null or invalid" << endl;
			}
			break;
		}
	}
	// Load Complete

	cout << endl;
	cout << "---" << endl;
	cout << "Initialized" << endl;
	cout << "---" << endl;
	Room rooms;

	if (gameStarted == true) {
		ofstream saveGame(playerSavePath, ios::trunc);

		saveGame << "Player Name : " << playerName << ";" << endl;
		cout << playerRoom << endl;
		saveGame << playerRoom;
		/*saveGame << playerController.health;
		 saveGame << playerController.maxHealth;
		 saveGame << playerController.mana;
		 saveGame << playerController.maxMana;*/
		if (playerRoom <= 0) {
			cerr << "Error: STOK003 playerRoom is not set correctly." << endl;
			return 1;
			rooms.room();
		} else {
			rooms.room();
		}

		thread playerMoveThread(onPlayerMove);
		playerMoveThread.join();
		// getPlayerInput(iplayerChar, saveGame);
	}
	return 0;
}
