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
            enemyIntent = "Poison (deal " + to_string(1 + enemy_strength) + " DMG and apply 1 Poison)";  
            player_poison += 1;
            enemy_dmg = 1; 
        }
        else {
            enemyIntent = "Toxic (Apply 2 Poison)";  
            player_poison += 2;
        }
    }
    
    if (monsterName == "Slime") { //boss1
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
            enemy_dmg = 1;
        }
        else if (r == 1) {
            enemyIntent = "Heavy Attack (deal " + to_string(2 + enemy_strength) + " DMG)";  
            enemy_dmg = 2; 
        }
        else {
            enemyIntent = "Poison and Split (Apply 1 Poison, heal 1 HP)";  
            player_poison += 1;
            monsterHP += 1;
            if (monsterHP > monsterMaxHP) monsterHP = monsterMaxHP;
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
            enemy_dmg = 1;
        }
        else if (r == 1) {
            enemyIntent = "Drain (deal " + to_string(1 + enemy_strength) + " DMG and heal self for 1 HP)";  
            monsterHP += 1;
            enemy_dmg = 1; 
            if (monsterHP > monsterMaxHP) monsterHP = monsterMaxHP;
        }
        else {
            enemyIntent = "Heavy Attack (deal " + to_string(3 + enemy_strength) + " DMG and lose 1 HP)";
            enemy_dmg = 3;
            monsterHP -= 1;
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

    if (monsterName == "Mister Big Brain") {
        if (r == 0) {   
            enemyIntent = "Attack (" + to_string(3 + enemy_strength) + " DMG)";
            enemy_dmg = 3;
        }
        else if (r == 1) {
<<<<<<< HEAD
            enemyIntent = "Kill Myself (deal 10 DMG to self)";  
            monsterHP -= 10;

=======
            enemyIntent = "Self Destruct (deal 5 DMG to self, deal 5 DMG to player)";  
            enemy_dmg = 5;
            monsterHP -= 5;
>>>>>>> 08bfdd27becee9c3ad70c0a982bb6b59aaf4fe7a
        }
        else {
            enemyIntent = "Buff 3 (apply 3 Strength)";  
            enemy_strength += 3;
        }
    }

    if (monsterName == "Dragon") {
        if (r == 0) {   
<<<<<<< HEAD
            enemyIntent = "Attack (" + to_string(4 + enemy_strength) + " DMG)";
            enemy_dmg = 4;
        }
        else if (r == 1) {
            enemyIntent = "Fire Breath (deal 2 DMG and apply 2 Poison)";  
            player_poison += 2;
            enemy_dmg = 2; 
        }
        else {
            enemyIntent = "Tail Swipe (deal 3 DMG and reduce player strength by 1)";  
            player_strength -= 1;
            enemy_dmg = 3; 
        }
    }
=======
            enemyIntent = "Attack (" + to_string(2 + enemy_strength) + " DMG)";
            enemy_dmg = 2;
        }
        else if (r == 1) {
            enemyIntent = "Harden Scales (apply 1 Strength and Heal 2 DMG)";  
            enemy_strength += 1;
            monsterHP += 2;
            if (monsterHP > monsterMaxHP) monsterHP = monsterMaxHP;
        }
        else {
            enemyIntent = "Fire Breath (deal " + to_string(4 + enemy_strength) + " DMG and apply 2 Poison)"; 
            enemy_dmg = 4; 
            player_poison += 2;
        }
>>>>>>> 08bfdd27becee9c3ad70c0a982bb6b59aaf4fe7a

}
#endif