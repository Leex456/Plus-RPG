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
inline void displayBattleScreen() {
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
    cout << "|  2. Run Away" << string(SCREEN_WIDTH - 15, ' ') << "|\n";

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

    int potiondrop = 0;
    int relicdrop = 0;

    if (enemyType == "E") {
        string monsterlist[] = {"Goblin", "Frog", "Slime", "Gambler", "Bat", "Porcupine"};
        monsterName = monsterlist[rand() % 6];
        monsterHP = 6;
        monsterMaxHP = 6;
    } else if (enemyType == "B") {
        string bosslist[] = {"Mister Big Brain"};
        monsterName = bosslist[rand() % 1];
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

    
    string PotionList[] = {
        "[Strength Potion] Increases damage by 1 permanently",
        "[Gambling Potion] Deals 0-3 DMG randomly",
        "[Weak Potion] Reduces enemy damage by 1 permanently",
        "[Poison Potion] Applies 1 poison to the enemy"
    };
    string RelicList[] = {
        "[Ring of Strength] +1 Strength",
        "[Toxic Bottle] Enemy start with 1 poison",
    };

    generateNextIntent();

    while (playerHP > 0 && monsterHP > 0) {
        displayBattleScreen();
        cout << "Choose action (1: Select Potion, 2: Run Away): ";
        int choice;
        
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n');
            playerLog = "Invalid action input choice.";
            continue;
        }

        if (choice == 1) {
            int totalPotions = countPotions(bag);
            if (totalPotions == 0) {
                playerLog = "Your inventory is empty!";
                continue;
            }

            displayBattleScreen();

            displayNumberedPotions(bag);
            cout << "Choose a potion number: ";
            int potChoice;
            
            if (!(cin >> potChoice)) {
                cin.clear(); cin.ignore(1000, '\n');
                playerLog = "Invalid potion input.";
                continue;
            }

            if (potChoice == totalPotions + 1) {
                playerLog = "Returned to primary menu.";
                continue;
            }

            if (potChoice >= 1 && potChoice <= totalPotions) {
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


                    cout << "===============LOOTS===============\n" << endl;
                    for (int i = 0; i < potiondrop; i++) {
                        string addPotion = PotionList[rand() % 4];
                        bag.addItem(addPotion);
                    }
                    for (int i = 0; i < relicdrop; i++) {
                        string addRelic = RelicList[rand() % 2];
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
        } else if (choice == 2) {
            cout << "\nYou ran away from combat!\n";
            cout << "Press any key to continue...";
            _getch();
            return true; 
        }
    }
    return playerHP > 0;
}

#endif