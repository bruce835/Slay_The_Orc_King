#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include "C:/Users/Robin/source/repos/SlayTheOrcKing/SlayTheOrcKing/PlayerController.h"

using namespace std;

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

// Room Logic
int room1() {
    playerRoom = 1;
    cout << playerName << ": AAGH! What is that stench?" << endl;
    while (true) {
        cin >> playerInput;
        if (playerInput == "north") { /*TODO: Fix room2() not running on north*/
            cout << "Moving North";
            playerRoom = 2;
            break;
        }
    }
    playerMoved = true;
    return 3;
}
int room2() {
    cout << playerName << ": This isn't too much worse, smell wise" << endl;
    return 3;
}

// Room Map
using roomFunction = function<int()>;
int room() {
    map<int, roomFunction> rooms = {
        {1, room1},
        {2, room2}
    };

    auto it = rooms.find(playerRoom); // Find the room by playerRoom
    if (it != rooms.end()) {
        return it->second(); // Call the function associated with the room
    }

    return 2;
}

int getPlayerInput(ifstream& iplayerChar, ofstream& saveGame)
{
    while (true) {
        cin >> playerInput;
        if (playerInput == "quit") {
            iplayerChar.close();
            saveGame << "Player Name : " << playerName << ";" << endl;
            saveGame << playerRoom;
            break;
        }
    }

    return 1;
}

int main(){
    // Start
    cout << "Welcome To SLAY THE ORC KING" << endl;
    cout << "..." << endl;
    cout << "What is your name, adventurer?";
    cin >> playerName;

    // Check playerSave
    playerSavePath = "C:/Users/Robin/source/repos/SlayTheOrcKing/SlayTheOrcKing/PlayerSaves/" + playerName + ".txt";
    ifstream checkPlayerSave;
    checkPlayerSave.open(playerSavePath);
    
    // Create New PlayerSave
    if (!checkPlayerSave) {
        playerSave.open(playerSavePath, fstream::in | fstream::out | fstream::trunc);
        playerSave << "Player Name: " << playerName << ";" << endl;
        playerSave << "1";
        playerSave.close();
    }

    
    checkPlayerSave.seekg(13, istream::beg);
    checkPlayerSave.getline(playerNameDestination, 10, ';');
    cout << "Greetings, "; cout << playerNameDestination << endl << endl;;
    gameStarted = true;

    cout << endl; cout << "Initializing..." << endl;
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
    }
    else {
        cout << "iplayerCharOpened"; cout << endl;
    }
    
    int iplayerCharLine = 0;
    iplayerChar.clear();
    string playerRoomString;
    while (!iplayerChar.eof()) {
        iplayerCharLine++;
        getline(iplayerChar, playerRoomString);
        if (iplayerCharLine == 2) {
            if (!playerRoomString.empty() && all_of(playerRoomString.begin(), playerRoomString.end(), ::isdigit)) {
                cout << endl; cout << "playerRoomString: " << playerRoomString << endl;
                playerRoom = stoi(playerRoomString);
            }
            else {
                cerr << "Error: STOK001 Invalid player room data in save file." << endl;
                cout << endl; cout << "playerRoomString: " << "null or invalid" << endl;
                playerRoom = 1;
            }  
            break;
        }
    }
    // Load Complete
    
    cout << endl;
    cout << "---" << endl;
    cout << "Initialized" << endl;
    cout << "---" << endl;

    if (gameStarted == true)
    {
        ofstream saveGame(playerSavePath, ios::trunc); /*TODO: Fix saveGame flushing player save line 2*/
        
        saveGame << "Player Name : " << playerName << ";" << endl;
        saveGame << playerRoom;
       /*saveGame << playerController.health;
        saveGame << playerController.maxHealth;
        saveGame << playerController.mana;
        saveGame << playerController.maxMana;*/ 

        if (playerRoom <= 0) {
            cerr << "Error: STOK003 playerRoom is not set correctly." << endl;
            return 1;
            room();
        }
        else {
            room();
        }
        getPlayerInput(iplayerChar, saveGame);
    }

    while (true) {
        if (playerMoved == true) {
            room();
            playerMoved = false;
        }
    }
        return 0;
}