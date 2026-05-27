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
}
#endif