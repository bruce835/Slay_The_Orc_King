#pragma once
#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <fstream>
#include <iostream>

class PlayerController {
public:
	int health;
	int maxHealth;
	int mana;
	int maxMana;
	int level;
	int playerCurrentRoom;
	std::string player;
	int save();
	int fetchSaves(std::string& saveFolder, std::ifstream& playerChar);
	bool foundSave;
	int stage;
	std::string saveFilePath;
	std::string saveFile;
public:
	PlayerController(std::string& playerName);
};

#endif
