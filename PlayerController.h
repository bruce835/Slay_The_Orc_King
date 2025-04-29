#pragma once
#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
	int stage;
	std::vector<std::string> playerSaveVector;
	std::vector<std::string> playerSaveVectorSelected;
	std::string saveName;
public:
	PlayerController(std::string& playerName);
};

#endif
