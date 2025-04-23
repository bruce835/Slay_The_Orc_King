#include "PlayerController.h"
#include <fstream>
#include <iostream>
using namespace std;

// Init playersave Variables
PlayerController::PlayerController() {
	health = 0;
	maxHealth = 0;
	mana = 0;
	maxMana = 0;
	level = 0;
}
