#include "PlayerController.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Init playersave Variables
int PlayerController::save() {
                        cout << "Name for save: ";
                        cin >> saveName;
			cout << "SAVING..." << endl;
			ofstream saveGame("PlayerSaves/" + player +".txt", ios::trunc);
			for (const string& line : playerSaveVector) {
				saveGame << line << endl;
			}
			saveGame << "Save\n";
                        saveGame << saveName << endl;
			saveGame << "Player Name : " << player << ";" << endl;
			saveGame << playerCurrentRoom << endl;
			saveGame << health << endl;
			saveGame << maxHealth << endl;
			saveGame << mana << endl;
			saveGame << maxMana << endl;
			saveGame << level << endl;;
			saveGame << stage;
			saveGame.close();
			cout << "DONE.\n" << endl;
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
	stage = 0;
        saveName = "";

		ifstream playerChar;
		playerChar.open("PlayerSaves/" + player + ".txt");
		if (playerChar) {
			cout << "Save found for player: " << player <<". Save list: \n";
		}
		int playerCharLine = 0;
		int playerSaveStart;
		int playerSaveEnd;
		string playerCharDestination;
		int playerStat;
		while(!playerChar.eof()) {
			getline(playerChar, playerCharDestination);
			if (playerCharDestination == "Save") {
				getline(playerChar, playerCharDestination);
				cout << playerCharDestination << endl;
			}
			}
		
		cout << "Type desired save: ";
		cin >> saveName;
		playerChar.clear();
		playerChar.seekg(0);
		bool readingSave = false;
		while(true) {
			if (playerChar.eof()) {
				break;
			}
			cout << "Reading playerChar\n";
			playerCharLine++;
			getline(playerChar, playerCharDestination);
			if (playerCharDestination == saveName) {
				playerSaveStart = playerCharLine;
				cout << "true\n";
				readingSave = true;
			}
				else {
					cout << "false\n";
					playerSaveVector.push_back(playerCharDestination);
		}

			if (readingSave == true) {
				playerCharLine++;
				getline(playerChar, playerCharDestination);
				if (playerCharDestination == "Save") {
					playerSaveEnd = playerCharLine - 1;
					readingSave = false;
				}
					else {
						cout << "writing to seclected player save vector\n";
						playerSaveVectorSelected.push_back(playerCharDestination);
					}
			}
		}
			cout << "read player char\n";
			playerCharLine = 0;
		    playerChar.clear();
		    playerChar.seekg(0);
		    while(!playerChar.eof() && playerCharLine < playerSaveEnd) {
			    playerCharLine++;
		    if (playerCharLine <= playerSaveStart || playerCharLine > playerSaveEnd) {
		        continue; // Move to the next line without processing
		    }
	        try {
	            playerStat = stoi(playerCharDestination);
	        } catch (const invalid_argument& e) {
	            continue;
	        } catch (const out_of_range& e) {
	            continue;
	        }

	        if(playerCharLine == playerSaveStart+2) {
				playerCurrentRoom = playerStat;
			}

	        if(playerCharLine == playerSaveStart+3) {
				health = playerStat;
			}

			if(playerCharLine == playerSaveStart+4) {
				maxHealth = playerStat;
			}

			if(playerCharLine == playerSaveStart+5) {
				mana = playerStat;
			}

			if(playerCharLine == playerSaveStart+6) {
				maxMana = playerStat;
			}


			if(playerCharLine == playerSaveStart+7) {
				level = playerStat;
			}
			
			if(playerCharLine == playerSaveStart+8) {
				stage = playerStat;
				cout << "DONE.\n";
				break;
			}
		}
		if (playerCurrentRoom == 0 || level == 0) {
			// Set Default Stats
			cout << "\n" << "Setting Default Stats" << endl;
			health = 10;
			mana = 10;
			maxHealth = 10;
			maxMana = 10;
			level = 1;
			playerCurrentRoom = 1;
			stage = 1;
			playerChar.close();
		}
		save();
}
