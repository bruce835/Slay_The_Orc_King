#include <iostream>
#include <fstream>
#include "PlayerController.h"
using namespace std;

//Init playersave Variables
PlayerController::PlayerController() {
        health = 0;
        maxHealth = 0;
        mana = 0;
        maxMana = 0;
        level = 0;
}