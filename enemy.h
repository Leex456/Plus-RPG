#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <cstdlib>

using namespace std;

// Shared External Global References
extern string monsterName;
extern string enemyIntent;
extern int monsterHP;
extern int monsterMaxHP;
extern int enemy_strength;
extern int enemy_dmg;
extern int enemy_poison;
extern int player_strength;
extern int player_poison;

// Process State Actions
inline void generateNextIntent() {
    int r = rand() % 3;

    if (monsterName == "Goblin") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 1;
        }
        else if (r == 1) {
            enemyIntent = "Buff (apply 1 Strength)";  
            enemy_strength += 1; 
            enemy_dmg = 0; 
        }
        else {
            enemyIntent = "Heavy Attack (" + to_string(2 + enemy_strength) + " DMG)";
            enemy_dmg = 2;
        }
    }

    if (monsterName == "Frog") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 1;
        }
        else if (r == 1) {
            enemyIntent = "Poison (deal 1 DMG and apply 1 Poison)";  
            enemy_poison += 1;
            enemy_dmg = 1; 
        }
        else {
            enemyIntent = "Poison 3 (deal 3 DMG and apply 3 Poison)";  
            enemy_poison += 3;
            enemy_dmg = 3; 
        }
    }
    
    if (monsterName == "Slime") { //boss1
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 1;
        }
        else if (r == 1) {
            enemyIntent = "Poison 2 (deal 2 DMG and apply 2 Poison)";  
            enemy_poison += 2;
            enemy_dmg = 2; 
        }
        else {
            enemyIntent = "Poison 5 (deal 5 DMG and apply 5 Poison)";  
            enemy_poison += 5;
            enemy_dmg = 5; 
        }
    }

    if (monsterName == "Gambler") {
        if (r == 0) {   
            enemyIntent = "Unknown";
            enemy_dmg = rand() % 3;
        }
        else if (r == 1) {
            enemyIntent = "Unknown";  
            enemy_strength += rand() % 3;
            enemy_dmg = 0; 
        }
        else {
            enemyIntent = "Unknown";  
            enemy_poison += rand() % 2;
            enemy_dmg = 0; 
        }
    }

        if (monsterName == "Bat") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 2;
        }
        else if (r == 1) {
            enemyIntent = "Drain 1 (deal 1 DMG and heal self for 1 HP)";  
            monsterHP += 1;
            enemy_dmg = 1; 
        }
        else {
            enemyIntent = "Drain 3 (deal 3 DMG and heal self for 3 HP)";
            enemy_dmg = 3;
            monsterHP += 3;
            if (monsterHP > monsterMaxHP) monsterHP = monsterMaxHP;
        }
    }

    if (monsterName == "Porcupine") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 1;
        }
        else if (r == 1) {
            enemyIntent = "Buff 1 (apply 1 Strength)";  
            enemy_strength += 1;

        }
        else {
            enemyIntent = "Buff 3 (apply 3 Strength)";  
            enemy_strength += 3;
        }
    }

    if (monsterName == "Mister Big Brain") { //boss2
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 6;
        }
        else if (r == 1) {
            enemyIntent = "Zone Out";  
            enemy_strength += 0;

        }
        else {
            enemyIntent = "Buff 3 (apply 3 Strength)";  
            enemy_strength += 3;
        }
    }

}
#endif