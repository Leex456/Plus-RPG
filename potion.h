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
extern int playerHP;
extern int playerMaxHP;
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
        player_strength += 2;
        playerLog = "Player used Strength Potion, increasing damage by 2!";

    } else if (chosenPotion.find("Gambling Potion") != string::npos) {
        dmg = rand() % 4;
        playerLog = "Player used Gambling Potion!";

    } else if (chosenPotion.find("Weak Potion") != string::npos) {
        enemy_strength -= 2;
        playerLog = "Player used Weak Potion, reducing enemy damage by 2!";

    } else if (chosenPotion.find("Poison Potion") != string::npos) {
        enemy_poison += 1;
        playerLog = "Player used Poison Potion, applying 1 poison to the enemy!";

    } else if (chosenPotion.find("Damage Potion") != string::npos) {
        dmg = 3;
        playerLog = "Player used Damage Potion, dealing 3 DMG!";

    } else if (chosenPotion.find("Heal Potion") != string::npos) {
        playerLog = "Player used Heal Potion, healing 5 HP!";
        playerHP += 5;
        if (playerHP > playerMaxHP) playerHP = playerMaxHP;

    } else if (chosenPotion.find("Reckless Potion") != string::npos) {
        dmg = 5;
        playerHP -= 1;
        playerLog = "Player used Reckless Potion, dealing 5 DMG and taking 1 damage!";

    }  else if (chosenPotion.find("Block Potion") != string::npos) {
        block = 5;
        playerLog = "Player used Block Potion, blocking 5 DMG!";

    } else if (chosenPotion.find("Rush Potion") != string::npos) {
        block = 2;
        dmg = 2;
        playerLog = "Player used Rush Potion, blocking 2 DMG and dealing 2 DMG!";

    } else if (chosenPotion.find("Toxic Potion") != string::npos) {
        enemy_poison += 4;
        player_poison += 1;
        playerLog = "Player used Toxic Potion, applying 4 poison to the enemy, also applying 1 poison to self!";

    } else if (chosenPotion.find("Overgrowth Potion") != string::npos) {
        player_strength += 4;
        playerHP -= 1;
        playerLog = "Player used Overgrowth Potion, increasing damage by 4, also taking 1 damage!";

    }  else if (chosenPotion.find("Purify Potion") != string::npos) {
        enemy_strength = 0;
        player_poison = 0;
        playerLog = "Player used Purify Potion, removing all enemy strength and player poison!";

    }   else if (chosenPotion.find("Growth Potion") != string::npos) {
        playerLog = "Player used Growth Potion, increasing max HP by 1!";
        playerMaxHP += 1;
        playerHP += 1;

    }  

}
#endif