#ifndef POTION_H
#define POTION_H

#include <string>
#include <cstdlib>
#include "invent.h"

using namespace std;

// PUBLIC VARIABLES
extern int player_strength;
extern int enemy_strength;
extern int enemy_poison;
extern int player_poison;
extern string playerLog;

inline void handlePotionUsage(string chosenPotion, Inventory& bag, int& dmg, int& block) {
    dmg = 0;
    block = 0;

    if (chosenPotion.find("Attack Potion") != string::npos) {
        dmg = 1;
        bag.insertItem("[Attack Potion] Deals 1 DMG, return this potion at end of turn", 1);
        playerLog = "Player used Attack Potion!";

    } else if (chosenPotion.find("Defend Potion") != string::npos) {
        block = 2;
        bag.insertItem("[Defend Potion] Block 2 DMG, return this potion at end of turn", 2);
        playerLog = "Player used Defend Potion, blocking 2 DMG.";

    } else if (chosenPotion.find("Strength Potion") != string::npos) {
        player_strength += 1;
        playerLog = "Player used Strength Potion, increasing damage by 1!";

    } else if (chosenPotion.find("Gambling Potion") != string::npos) {
        dmg = rand() % 4;
        playerLog = "Player used Gambling Potion!";

    } else if (chosenPotion.find("Weak Potion") != string::npos) {
        enemy_strength -= 1;
        playerLog = "Player used Weak Potion, reducing enemy damage by 1!";

    } else if (chosenPotion.find("Poison Potion") != string::npos) {
        enemy_poison += 1;
        playerLog = "Player used Poison Potion, applying 1 poison to the enemy!";
    } 

}
#endif