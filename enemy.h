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
extern int enemy_thorns;
extern int enemy_regeneration;
extern int player_strength;
extern int player_poison;
extern int player_thorns;
extern int player_regeneration;

// Process State Actions
inline void generateNextIntent() {
    int r = rand() % 3;


    if (monsterName == "Goblin") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 1;
        }
        else if (r == 1) {
            enemyIntent = "Buff (+1 DMG in this battle)";  
            enemy_strength += 1; 
            enemy_dmg = 0; 
        }
        else {
            enemyIntent = "Heavy Attack (" + to_string(2 + enemy_strength) + " DMG)";
            enemy_dmg = 2;
        }
    }

    if (monsterName == "Doctor") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 1;
        }
        else if (r == 1) {
            enemyIntent = "Regen (+2 Regeneration in this battle)";  
            enemy_regeneration += 2;
            enemy_dmg = 0; 
        }
        else {
            enemyIntent = "Heal (+3 HP)";
            enemy_dmg = 0;
            monsterHP += 3;
            if (monsterHP > monsterMaxHP) monsterHP = monsterMaxHP;
        }
    }

    if (monsterName == "Bat") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 2;
        }
        else if (r == 1) {
            enemyIntent = "Drain 1 (deal 1 DMG and heal self for 1 HP)";  
            enemy_regeneration += 1;
            enemy_dmg = 1; 
        }
        else {
            enemyIntent = "Drain 3 (deal 3 DMG and heal self for 3 HP)";
            enemy_dmg = 3;
            monsterHP += 3;
            if (monsterHP > monsterMaxHP) monsterHP = monsterMaxHP;
        }
    }

    if (monsterName == "Frog") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 2;
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
    
    if (monsterName == "Slime") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 3;
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

    if (monsterName == "Porcupine") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 1;
        }
        else if (r == 1) {
            enemyIntent = "Thorns 1 (apply 1 Thorns)";  
            enemy_thorns += 1;
            enemy_dmg = 0; 
        }
        else {
            enemyIntent = "Thorns 3 (apply 3 Thorns)";  
            enemy_thorns += 3;
            enemy_dmg = 0; 
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
            player_regeneration += rand() % 3;
            enemy_dmg = 0; 
        }
    }

    
}
#endif