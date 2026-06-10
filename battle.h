#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <string>
#include <iomanip> 
#include <cstdlib> 
#include <ctime>   
#include <conio.h>
#include "invent.h"
#include "enemy.h"
#include "potion.h"
#include "relic.h"
#include <random>

using namespace std;

// SETUP VARIABLES
inline int playerHP = 20;
inline int playerMaxHP = 20;
inline int monsterHP = 5;
inline int monsterMaxHP = 5;

// STATUS VARIABLES
inline int enemy_strength = 0;
inline int player_strength = 0;   
inline int player_poison = 0;
inline int enemy_poison = 0;

inline int enemy_dmg = 0;
inline int relic_length = 0;

inline string monsterName = "Goblin"; 
inline string monsterLog = ""; 
inline string playerLog = "";
inline string enemyIntent = "";

inline Inventory bag;
inline Relic relic;

void generateNextIntent();
void handlePotionUsage(string chosenPotion, Inventory& bag, int& dmg, int& block);

// count inv
inline int countPotions(Inventory& inv) {
    int count = 0;
    Item* temp = inv.head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

inline int countRelic(Relic& rec) {
    int count = 0;
    RelicInv* temp = rec.head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    relic_length = count;
    return count;
}

// UI
inline void displayNumberedPotions(Inventory& inv) {
    Item* temp = inv.head;
    int index = 1;
    cout << "\n===============================\n";
    cout << "       SELECT A POTION         \n";
    cout << "===============================\n";
    while (temp != NULL) {
        cout << "  " << index << ". " << temp->name << "\n";
        index++;
        temp = temp->next;
    }
    cout << "  " << index << ". [Back to Action Menu]\n";
    cout << "===============================\n";
}

inline void displayNumberedRelic(Relic& rec) {
    RelicInv* temp = rec.head;
    int index = 1;
    while (temp != NULL) {
        cout << "|  " << temp->name << string(96 - temp->name.length(), ' ') << "|\n";
        index++;
        temp = temp->next;
    }
}

// CHOOSE POTION
inline string getPotionAt(Inventory& inv, int targetIndex) {
    Item* temp = inv.head;
    int currentIndex = 1;
    while (temp != NULL) {
        if (currentIndex == targetIndex) {
            return temp->name;
        }
        currentIndex++;
        temp = temp->next;
    }
    return "";
}

inline string generateHealthBar(int currentHP, int maxHP) {
    int barLength = 20; 
    int filledLength = (currentHP * barLength) / maxHP;
    string bar = "[";
    for (int i = 0; i < filledLength; i++) {
        bar += "#";
    }
    for (int i = filledLength; i < barLength; i++) {
        bar += " ";
    }
    bar += "]";
    return bar;
}

// Renders
inline void displayBattleScreen(bool canRunAway) {
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear"); 
    #endif

    constexpr int SCREEN_WIDTH = 100;
    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";

    string playerHeader = "  PLAYER";
    string monsterHeader = monsterName;
    int spacesBetweenHeaders = SCREEN_WIDTH - 2 - playerHeader.length() - monsterHeader.length();
    cout << "|" << playerHeader << string(spacesBetweenHeaders, ' ') << monsterHeader << "|\n";

    string playerHPStr = "  HP: " + generateHealthBar(playerHP, playerMaxHP) + " " + to_string(playerHP) + "/" + to_string(playerMaxHP);
    string monsterHPStr = "HP: " + generateHealthBar(monsterHP, monsterMaxHP) + " " + to_string(monsterHP) + "/" + to_string(monsterMaxHP) + "  ";
    int spacesBetweenHP = SCREEN_WIDTH - 2 - playerHPStr.length() - monsterHPStr.length();
    cout << "|" << playerHPStr << string(spacesBetweenHP, ' ') << monsterHPStr << "|\n";

    cout << "| " << string(SCREEN_WIDTH - 4, ' ') << " |\n";

    string vsText = "VS";
    int vsPadding = (SCREEN_WIDTH - 2 - vsText.length()) / 2;
    cout << "|" << string(vsPadding, ' ') << vsText << string(vsPadding, ' ') << "|\n";

    cout << "| " << string(SCREEN_WIDTH - 4, ' ') << " |\n";

    // EFFECTS
    cout << "|  Status: " << string(SCREEN_WIDTH - 20, ' ') << "Status: |\n";
    cout << "|  Strength: " << player_strength << string(SCREEN_WIDTH - 26 - to_string(player_strength).length() - to_string(enemy_strength).length(), ' ') << "Strength: " << enemy_strength << "  |\n";
    cout << "|  Poison: " << player_poison << string(SCREEN_WIDTH - 22 - to_string(player_poison).length() - to_string(enemy_poison).length(), ' ') << "Poison: " << enemy_poison << "  |\n";

    cout << "| " << string(SCREEN_WIDTH - 4, ' ') << " |\n";
    cout << "|  Relic: " << string(SCREEN_WIDTH - 11, ' ') << "|\n";

    displayNumberedRelic(relic);

    cout << "| " << string(SCREEN_WIDTH - 4, ' ') << " |\n";
    cout << "|  [Action Menu]" << string(SCREEN_WIDTH - 17, ' ') << "|\n";
    cout << "|  1. Select Potion" << string(SCREEN_WIDTH - 20, ' ') << "|\n";
    
    if (canRunAway) {
        cout << "|  2. Run Away" << string(SCREEN_WIDTH - 15, ' ') << "|\n";
    } else {
        cout << "|  [RETREAT LOCKED]" << string(SCREEN_WIDTH - 20, ' ') << "|\n";
    }

    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";

    cout << playerLog + "\n";
    cout << monsterLog + "\n";
    cout << "ENEMY INTENT: " + enemyIntent + "\n";

    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";
}

// MAIN
inline bool startBattle(string enemyType) {

    random_device rd;
    mt19937 gen(rd());

    int potiondrop = 0;
    int relicdrop = 0;
    bool interactionOccurred = false; // Tracks if player has locked in combat yet

    if (enemyType == "E") {
        string monsterlist[] = {"Goblin", "Frog", "Slime", "Gambler", "Bat", "Porcupine"};
        uniform_int_distribution<int> dist(0, 5);
        monsterName = monsterlist[dist(gen)];
        monsterHP = 6;
        monsterMaxHP = 6;
    } else if (enemyType == "B") {
        string bosslist[] = {"Mister Big Brain", "Beeg Cat", "Magician"};
        uniform_int_distribution<int> dist(0, 2);
        monsterName = bosslist[dist(gen)];
        monsterHP = 20;
        monsterMaxHP = 20;
    } else if (enemyType == "D") {
        monsterName = "Dragon";
        monsterHP = 40;
        monsterMaxHP = 40;
    }

    // Reset status conditions for the new fight
    enemy_strength = 0; player_strength = 0; player_poison = 0; enemy_poison = 0;
    playerLog = "An enemy blocks your path!"; monsterLog = "";

    if (relic.contains("[Ring of Strength] +1 Strength")) {
        player_strength += 1;
    }
    if (relic.contains("[Toxic Bottle] Enemy start with 1 poison")) {
        enemy_poison += 1;
    }
    if (relic.contains("[Healing Charm] Heal 1 HP at the start of each fight")) {
        playerHP += 1;
        if (playerHP > playerMaxHP) playerHP = playerMaxHP;
    }
    if (relic.contains("[Art of War] Boss enemies start with 25% less HP")) {
        if (enemyType == "B") {
            monsterHP = monsterHP * 0.75;
            monsterMaxHP = monsterMaxHP * 0.75;
        }
    }
    if (relic.contains("[Weakening Charm] Enemy start with 1 less Strength")) {
        enemy_strength -= 1;
    }
    if (relic.contains("[Charged Amulet] Player starts with 2 Strength, Enemy start with 1 strength")) {
        player_strength += 2;
        enemy_strength += 1;
    }
    if (relic.contains("[Art of War] Boss enemies start with 25% less HP")) {
        if (enemyType == "B") {
            monsterHP = monsterHP * 0.75;
            monsterMaxHP = monsterMaxHP * 0.75;
        }
    }
    if (relic.contains("[Scary Mask] Run away will gain you 1 HP")) {
        playerLog += " The Scary Mask grants you 1 HP for this fight...\n";
        playerHP += 1;
        if (playerHP > playerMaxHP) playerHP = playerMaxHP;
    }
    if (relic.contains("[Dragon Scale] Reduce dragon attack damage by 1")) {
        if (enemyType == "D") {
            enemy_dmg -= 1;
        }
    }
    if (relic.contains("[First Strike] Deal 3 DMG at the start of combat")) {
        monsterHP -= 3;
        playerLog += " The First Strike relic deals 3 DMG to the enemy at the start of combat!\n";
    }

    string PotionList[] = {
        "[Strength Potion] Increases damage by 2 permanently",
        "[Gambling Potion] Deals 0-3 DMG randomly",
        "[Weak Potion] Reduces enemy damage by 2 permanently",
        "[Poison Potion] Applies 1 poison to the enemy",
        "[Damage Potion] Deals 3 DMG",
        "[Heal Potion] Heals 5 HP",
        "[Reckless Potion] Deals 5 DMG and take 1 damage",
        "[Block Potion] Block 5 DMG",
        "[Rush Potion] Block 2 DMG and deal 2 DMG",
        "[Toxic Potion] Apply 4 poison to the enemy, also apply 1 poison to self",
        "[Overgrowth Potion] Increase damage by 4, also take 1 damage",
        "[Purify Potion] Remove all enemy strength and player poison",
        "[Growth Potion] Increase max HP by 1",
    };
    string RelicList[] = {
        "[Ring of Strength] Player starts with 1 Strength",
        "[Toxic Bottle] Enemy start with 1 poison",
        "[Healing Charm] Heal 1 HP at the start of each fight",
        "[Art of War] Boss enemies start with 25% less HP",
        "[Potion Satchel] Enemy drop 1 extra potion",
        "[Weakening Charm] Enemy start with 1 less Strength",
        "[Charged Amulet] Player starts with 2 Strength, Enemy start with 1 strength",
        "[Scary Mask] Run away will gain you 1 HP",
        "[Dragon Scale] Reduce dragon attack damage by 1",
        "[First Strike] Deal 3 DMG at the start of combat",
    };

    generateNextIntent();
    
    while (playerHP > 0 && monsterHP > 0) {
        // Can run away ONLY if it's not a dragon AND no potion has been used yet
        bool canRunAway = (enemyType != "D") && (!interactionOccurred);

        displayBattleScreen(canRunAway);
        
        // Directly display the dynamic list inside the action block frame with no exit option
        displayNumberedPotions(bag);

        if (canRunAway) {
            cout << "Choose a Potion Number to use (or enter 99 to Run Away): ";
        } else {
            cout << "Choose a Potion Number to use [Run Locked]: ";
        }

        int potChoice;
        if (!(cin >> potChoice)) {
            cin.clear(); cin.ignore(1000, '\n');
            playerLog = "Invalid numeric input configuration.";
            continue;
        }

        // Handle escape routing cleanly via an override variable value
        if (potChoice == 99) {
            if (canRunAway) {
                cout << "\nYou ran away from combat!\n";

                if (relic.contains("[Scary Mask] Run away will gain you 1 HP")) {
                    playerHP += 1;
                    if (playerHP > playerMaxHP) playerHP = playerMaxHP;
                    cout << "But the Scary Mask grants you 1 HP for running away...\n";
                }

                cout << "Press any key to continue...";
                _getch();
                return true; 
            } else {
                playerLog = "Retreat is impossible now!";
                continue;
            }
        }

        int totalPotions = countPotions(bag);
        if (potChoice >= 1 && potChoice <= totalPotions) {
            // A valid potion item execution drops running capabilities permanently
            interactionOccurred = true;

            string chosenPotion = getPotionAt(bag, potChoice);
            bag.removeItem(chosenPotion); 

            int dmg = 0; int block = 0;
            handlePotionUsage(chosenPotion, bag, dmg, block);

            if (dmg > 0 || chosenPotion.find("Attack Potion") != string::npos || chosenPotion.find("Gambling Potion") != string::npos) {
                monsterHP -= (dmg + player_strength);
                playerLog = "Player used " + chosenPotion.substr(0, chosenPotion.find("]")+1) + ", dealing " + to_string(dmg + player_strength) + " DMG!";
            }

            if (player_poison > 0) {
                playerHP -= player_poison;
                playerLog += " Player takes " + to_string(player_poison) + " poison damage!";
            }

            if (monsterHP <= 0) {
                #ifdef _WIN32
                    system("cls");  
                #else
                    system("clear"); 
                #endif

                if (enemyType == "E") {
                    potiondrop = 2;
                    relicdrop = 0;
                }
                else if (enemyType == "B") {
                    potiondrop = 4;
                    relicdrop = 1;
                }
                else if (enemyType == "D") {
                    potiondrop = 6;
                    relicdrop = 1;
                }

                if (relic.contains("[Potion Satchel] Enemy drop 1 extra potion")) {
                    potiondrop += 1;
                }
                if (relic.contains("[The Destruction] Heal 25% HP at the end of each fight, and raise max HP by 1")) {
                        playerMaxHP += 1;    
                        playerHP += playerMaxHP * 0.25;
                        if (playerHP > playerMaxHP) playerHP = playerMaxHP;
                        
                }

                cout << "===============LOOTS===============\n" << endl;
                uniform_int_distribution<int> potDist(0, 12);
                for (int i = 0; i < potiondrop; i++) {
                    string addPotion = PotionList[potDist(gen)];
                    bag.addItem(addPotion);
                }
                uniform_int_distribution<int> relicDist(0, 7);
                for (int i = 0; i < relicdrop; i++) {
                    string addRelic = RelicList[relicDist(gen)];
                    if (!relic.contains(addRelic)) {
                        relic.addItem(addRelic);
                    }
                }

                cout << "\n===================================\n";
                cout << "  VICTORY! You defeated the monster!\n";
                cout << "===================================\n";
                cout << "Press any key to return to the world map...";
                _getch();
                return true; 
            }

            if (enemyIntent.find("Attack") != string::npos) {
                int combinedEnemyDmg = enemy_dmg + enemy_strength;
                int damageAfterBlock = combinedEnemyDmg - block;
                if (damageAfterBlock < 0) damageAfterBlock = 0;
                playerHP -= damageAfterBlock;
                monsterLog = monsterName + " attacks for " + to_string(combinedEnemyDmg) + " DMG! Player blocks " + to_string(block) + " DMG.";
            }
            else if (enemyIntent.find("Buff") != string::npos) {
                monsterLog = monsterName + " buffs itself";
            }

            if (enemy_poison > 0) {
                monsterHP -= enemy_poison;
                monsterLog += " " + monsterName + " takes " + to_string(enemy_poison) + " poison damage!";
            }
        
            if (monsterHP > monsterMaxHP) monsterHP = monsterMaxHP;

            if (playerHP <= 0) {
                return false; 
            }

            generateNextIntent(); 
        } else {
            playerLog = "Out of range choice allocation selected.";
        }
    }
    return playerHP > 0;
}

#endif