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

			if (playerInput == "north") {
				cout << "Moving North" << endl;
				playerRoom = 2;
				playerMoved = true;
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

			if (playerInput == "south") {
				cout << "Moving South" << endl;
				playerRoom = 1;
				playerMoved = true;
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
		cout << "room() ran\n";
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
void onPlayerMove(/*string& playerLastRoom*/) { // TODO: Set playerCurrentRoom to playerRoom : (playerController.playerCurrentRoom)
	while (true) {
		if (playerMoved == true) {
			Room currentRoom;
			//playerLastRoom = playerRoom;
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

	cout << "Greetings, " << playerName << "." << endl;
	cout << "Now, where were we?\n\n";
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
