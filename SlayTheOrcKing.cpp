#include "PlayerController.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;

string playerName;
string playerInput;
bool gameStarted = false;
int playerRoom;
bool playerMoved = false;
PlayerController* globalPlayerController = nullptr;
string outString;
int outputLength;
char output[80];

int pIn() {
	cout << playerName << ": ";
	return 0;
}

int out() {
	chrono::milliseconds writeTime{50};
	outputLength = outString.length();
	strcpy (output, outString.c_str());
	int i = 0;
	while (true) {
	if (i < outputLength) {
	cout << output[i] << flush;
	this_thread::sleep_for(writeTime);
	i++;
	}
	else {
		break;
	}
	}
	cout << endl;
	return 0;
}

		
bool getPlayerInput(string &input) {
	if (input == "help") {
		outString = "This is a list of basic commands: ";
		out();
		outString = "quit: save and quit game.";
		out();
		outString = "north/southwest/east, etc.: move from room to room.";
		out();
		pIn();
		return true;
	}
		else if (input == "save") {
			globalPlayerController->fetchAndSave();
			pIn();
			return true;
		}
		else if (input == "quit") {
			cout << endl;
			globalPlayerController->fetchAndSave();
			outString = "SAFE TRAVELS, ADVENTURER.";
			out();
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
				if(playerInput == "north") {
				outString = "MOVING NORTH";
				out();
				playerRoom = 2;
				playerMoved = true;
				return 3;
			}
			else  {
				outString = "NOT A VALID COMMAND. WHO HIRED YOU, ANYWAYS?";
				out();
				pIn();
			}
		
		return 1;
	}

	int room1() {
		playerRoom = 1;
		outString = playerName + ": AAGH! What is that stench?";
		out();
		outString = "Kohait: Werebat dung. The orcs gather it for medicinal purposes, believe it or not.";
		out();
		outString = playerName +  ": Fun. Okay, listen up!";
		out();
		pIn();
		while (true && getRoom1Input() != 3) {
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
				outString = "Moving South";
				out();
				playerRoom = 1;
				playerMoved = true;
				return 3;
			}
		else  {
                                outString = "NOT A VALID COMMAND. WHO HIRED YOU, ANYWAYS?";
				out();
				pIn();
				break;
                        }
		}
		return 1;
	}

	int room2() {
		playerRoom = 2;
		outString = playerName + ": This isn't too much better, smell wise";
		out();
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
	outString = "Welcome To SLAY THE ORC KING";
	out();
	outString = "...";
	out();
	outString = "What's your name, adventurer?";
	out();
	cout << "Adventurer: ";
	cin >> playerName;
	cout << endl;
	outString = "INITIALIZING...";
	out();
	PlayerController playerController(playerName);
	playerController.player = playerName;
	globalPlayerController = &playerController;

	if (globalPlayerController->stage > 1) {
	outString = "Greetings, " + playerName +  ".";
	out();
	outString = "Now, where were we?\n";
	out();
	}
		else {
			outString = "In the faraway world of Edoc-Dab, people are dying.";
			outString = "The orc king Gromulech has gone mad after reigning";
			outString = "for three hundred years. His paranoia has grown,";
			outString = "and he believes humans will destroy the peace between the two peoples.";
			outString = "Ruling with an iron fist, he began opressing the humans.";
			outString = "They were helplessly made captive by the orcs' overwhelming might.";
			outString = "But some can still stand. Some can still lead this fallen people";
			outString = "from the terror of the orc king. WHO WILL RISE? WHO WILL FIGHT?";
			outString = "WHO CAN DEFY THE WILL OF AN MADMAN COMMANDING LEGIONS OF OX-STRONG ORCS?";
			outString = "...";
			outString = "Who will SLAY THE ORC KING?\n";
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
