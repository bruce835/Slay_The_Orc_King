#include "PlayerController.h"
#include <fstream>
#include <iostream>
using namespace std;

// Init playersave Variables
int PlayerController::save() {
			cout << "SAVING" << endl;
			ofstream saveGame("PlayerSaves/" + player +".txt", ios::trunc);
			// Save Block (I don't feel like making this a function because I do not like pointers.
			saveGame << "Player Name : " << player << ";" << endl;
			saveGame << playerCurrentRoom << endl;
			cout << playerCurrentRoom << endl;
			saveGame << health << endl;
			saveGame << maxHealth << endl;
			saveGame << mana << endl;
			saveGame << maxMana << endl;
			saveGame << level << endl;
			saveGame.close();
			return 0;
}
PlayerController::PlayerController(string& playerName) {
	player = playerName;
	health = 0;
	maxHealth = 0;
	mana = 0;
	maxMana = 0;
	level = 0;
	playerCurrentRoom = 0;

		ifstream playerChar;
		playerChar.open("PlayerSaves/" + player + ".txt");
		int playerCharLine = 0;
		string playerCharDestination;
		int playerStat;


		while(!playerChar.eof() && playerCharLine <= 7) {
			playerCharLine++;
			getline(playerChar, playerCharDestination);

		    if (playerCharLine < 3 || playerCharLine > 7) {
		        continue; // Move to the next line without processing
		    }

	        try {
	            playerStat = stoi(playerCharDestination);
	        } catch (const invalid_argument& e) {
	            cerr << "Invalid data on line " << playerCharLine << ": " << playerCharDestination << endl;
	            continue;
	        } catch (const out_of_range& e) {
	            cerr << "Number out of range on line " << playerCharLine << ": " << playerCharDestination << endl;
	            continue;
	        }

	        if(playerCharLine == 3) {
				health = playerStat;
			}

			if(playerCharLine == 4) {
				maxHealth = playerStat;
			}

			if(playerCharLine == 5) {
				mana = playerStat;
			}

			if(playerCharLine == 6) {
				maxMana = playerStat;
			}

			if(playerCharLine == 7) {
				level = playerStat;
			}
			break;
		}
		if (playerCurrentRoom == 0 || level == 0) {
			// Set Default Stats
			cout << "Setting Default Stats" << endl;
			health = 10;
			mana = 10;
			maxHealth = 10;
			maxMana = 10;
			level = 1;
			playerCurrentRoom = 1;
			playerChar.close();
		}
		save();
}
