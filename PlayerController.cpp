#include "PlayerController.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = filesystem;


int PlayerController::fetchSaves(string& saveFolder, ifstream& playerChar) {
		foundSave = false;
		cout << "Enter Save Name: ";
		cin >> saveFile;

		saveFilePath = ("PlayerSaves/" + player + "/" + saveFile + ".txt");
		playerChar.open(saveFilePath);
		if (!playerChar) {
			saveFolder = "PlayerSaves/" + player;
			int status = mkdir(saveFolder.c_str(), 0777);
			playerChar.open(saveFilePath);
		}

		std::vector<std::string> saveList;
		const string& saveFold = saveFolder;
		for (const auto& entry : fs::directory_iterator(saveFold)) {
        		if (fs::is_regular_file(entry)) {
            			saveList.push_back(entry.path().filename().string());
        		}
    		}
		
		for (const string& fileName : saveList) {
			if (saveFile + ".txt" == fileName) {
				foundSave = true;
			}
		}	
		return 0;
}

int PlayerController::save() {
			cout << "SAVING..." << endl;
			ofstream saveGame(saveFilePath, ios::trunc);
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
	foundSave = false;

		saveFolder = "PlayerSaves/" + player;
		ifstream playerChar;
		fetchSaves(saveFolder, playerChar);	
		string newSave;
		if(!foundSave) {
			cout << "Save not found. Create new save? y/n: ";
			cin >> newSave;
			if (newSave == "y") {
				cout << "Creating new save...\n";
				saveFilePath = ("PlayerSaves/" + player + "/" + saveFile + ".txt");
				save();
			}
			else if (newSave == "n") {
				fetchSaves(saveFolder, playerChar);
			}
			else {
				cout << "Invalid command\n";
			}
		}
		
			else {
			saveFilePath = ("PlayerSaves/" + player + "/" + saveFile + ".txt");
			}
		

		
		int playerCharLine = 0;
		string playerCharDestination;
		int playerStat;

		while(!playerChar.eof() && playerCharLine < 8) {
			playerCharLine++;
			getline(playerChar, playerCharDestination);
		    if (playerCharLine < 2 || playerCharLine > 8) {
		        continue; // Move to the next line without processing
		    }

	        try {
	            playerStat = stoi(playerCharDestination);
	        } catch (const invalid_argument& e) {
	            continue;
	        } catch (const out_of_range& e) {
	            continue;
	        }

	        if(playerCharLine == 2) {
				playerCurrentRoom = playerStat;
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
			
			if(playerCharLine == 8) {
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

int PlayerController::fetchAndSave() {
		string newSave;
		ifstream playerChar;
		saveFolder = "PlayerSaves/" + player;
		fetchSaves(saveFolder, playerChar);	
		if(!foundSave) {
			cout << "Save not found. Create new save? y/n: ";
			cin >> newSave;
			if (newSave == "y") {
				cout << "Creating new save...\n";
				saveFilePath = ("PlayerSaves/" + player + "/" + saveFile + ".txt");
				save();
			}
			else if (newSave == "n") {
				fetchSaves(saveFolder, playerChar);
			}
			else {
				cout << "Invalid command\n";
			}
		}
		
			else {
			saveFilePath = ("PlayerSaves/" + player + "/" + saveFile + ".txt");
			}
	save();
	return 0;
}
