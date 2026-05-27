#include <iostream>
#include <string>
#include <iomanip> 
#include <cstdlib> 
#include <ctime>   
#include "invent.h"
#include "enemy.h"
#include "potion.h"

using namespace std;

// SETUP VARIABLES
int playerHP = 20;
int playerMaxHP = 20;
int monsterHP = 5;
int monsterMaxHP = 5;

//STATUS VARIABLES
int enemy_strength = 0;
int player_strength = 0;   
int player_poison = 0;
int enemy_poison = 0;
int player_thorns = 0;
int enemy_thorns = 0;
int player_regeneration = 0;
int enemy_regeneration = 0;

int enemy_dmg = 0;

string monsterName = "Doctor";
string monsterLog = ""; 
string playerLog = "";
string enemyIntent = "";

//count inv
int countPotions(Inventory& inv) {
    int count = 0;
    Item* temp = inv.head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

//UI
void displayNumberedPotions(Inventory& inv) {
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

//CHOOSE POTION
string getPotionAt(Inventory& inv, int targetIndex) {
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

// Health bar 
string generateHealthBar(int current, int max, int barWidth = 10) {
    if (current < 0) current = 0;
    int filledSegments = (current * barWidth) / max;
    if (filledSegments == 0 && current > 0) filledSegments = 1;

    string bar = "[";
    for (int i = 0; i < barWidth; i++) {
        if (i < filledSegments) bar += "|"; 
        else bar += "-"; 
    }
    bar += "]";
    return bar;
}

// Renders
void displayBattleScreen() {
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

    cout << "|";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << " ";
    cout << "|\n";

    string vsText = "VS";
    int vsPadding = (SCREEN_WIDTH - 2 - vsText.length()) / 2;
    cout << "|" << string(vsPadding, ' ') << vsText << string(vsPadding, ' ');
    if ((SCREEN_WIDTH - 2 - vsText.length()) % 2 != 0) cout << " "; 
    cout << "|\n";

    cout << "|";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << " ";
    cout << "|\n";

    //EFFECTS 
    cout << "|  Status: " << string(SCREEN_WIDTH - 20, ' ') << "Status: |\n";
    cout << "|  Strength: " << player_strength << string(SCREEN_WIDTH - 26 - to_string(player_strength).length() - to_string(enemy_strength).length(), ' ') << "Strength: " << enemy_strength << "  |\n";
    cout << "|  Poison: " << player_poison << string(SCREEN_WIDTH - 22 - to_string(player_poison).length() - to_string(enemy_poison).length(), ' ') << "Poison: " << enemy_poison << "  |\n";
    cout << "|  Thorns: " << player_thorns << string(SCREEN_WIDTH - 22 - to_string(player_thorns).length() - to_string(enemy_thorns).length(), ' ') << "Thorns: " << enemy_thorns << "  |\n";
    cout << "|  Regeneration: " << player_regeneration << string(SCREEN_WIDTH - 34 - to_string(player_regeneration).length() - to_string(enemy_regeneration).length(), ' ') << "Regeneration: " << enemy_regeneration << "  |\n";   

    cout << "|";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << " ";
    cout << "|\n";

    cout << "|  [Action Menu]" << string(SCREEN_WIDTH - 17, ' ') << "|\n";
    cout << "|  1. Select Potion" << string(SCREEN_WIDTH - 20, ' ') << "|\n";
    cout << "|  2. Run Away" << string(SCREEN_WIDTH - 15, ' ') << "|\n";

    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";

    cout << "PLAYER LOG: " + playerLog + "\n";

    cout << "ENEMY LOG: " + monsterLog + "\n";

    cout << "ENEMY INTENT: " + enemyIntent + "\n";

    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";
}

int main() {
    srand(time(0));
    
    //INV
    Inventory bag;
    bag.addItem("[Attack Potion] Deals 1 DMG, return this potion at end of turn");
    bag.addItem("[Defend Potion] Block 2 DMG, return this potion at end of turn");
    bag.addItem("[Strength Potion] Increases DMG by 1 in this battle");
    bag.addItem("[Gambling Potion] Deal 0-3 DMG randomly");
    bag.addItem("[Weak Potion] Enemy DMG decreased by 1 in this battle");
    bag.addItem("[Poison Potion] Apply 1 Poison");

    generateNextIntent();

    while (playerHP > 0 && monsterHP > 0) {
        displayBattleScreen();
        cout << "Choose action (1: Select Potion, 2: Run Away): ";
        int choice;
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            playerLog = "Invalid action input choice.";
            continue;
        }

        if (choice == 1) {
            int totalPotions = countPotions(bag);
            if (totalPotions == 0) {
                playerLog = "Your inventory is empty!";
                continue;
            }

            displayNumberedPotions(bag);
            cout << "Choose a potion number: ";
            int potChoice;
            
            if (!(cin >> potChoice)) {
                cin.clear();
                cin.ignore(1000, '\n');
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

                int dmg = 0;
                int block = 0;
                
                // Call potion.h
                handlePotionUsage(chosenPotion, bag, dmg, block);

                // Player turn damage resolution
                if (dmg > 0 || chosenPotion.find("Attack Potion") != string::npos || chosenPotion.find("Gambling Potion") != string::npos) {
                    monsterHP -= (dmg + player_strength);
                    playerLog = "Player used " + chosenPotion.substr(0, chosenPotion.find("]")+1) + ", dealing " + to_string(dmg + player_strength) + " DMG!";
                    if (enemy_thorns > 0) {
                        playerHP -= enemy_thorns;
                        playerLog += " Player takes " + to_string(enemy_thorns) + " thorns damage!";
                    }
                }

                if (player_poison > 0) {
                    playerHP -= player_poison;
                    playerLog += " Player takes " + to_string(player_poison) + " poison damage!";
                }

                if (player_regeneration > 0) {
                    playerHP += player_regeneration;
                    if (playerHP > playerMaxHP) playerHP = playerMaxHP;
                    playerLog += " Player regenerates " + to_string(player_regeneration) + " HP!";
                    player_regeneration -= 1;
                }

                // Check WIN
                if (monsterHP <= 0) {
                    monsterHP = 0;
                    monsterLog = playerLog + " " + monsterName + " was crushed!";
                    displayBattleScreen();
                    cout << "\nVICTORY! You defeated the monster!\n";
                    break;
                }

                // Enemy Response Turn
                if (enemyIntent.find("Attack") != string::npos) {
                    int combinedEnemyDmg = enemy_dmg + enemy_strength;
                    int damageAfterBlock = combinedEnemyDmg - block;
                    if (player_thorns > 0) {
                        monsterHP -= player_thorns;
                        monsterLog += " " + monsterName + " takes " + to_string(player_thorns) + " thorns damage!";
                    }
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

                if (enemy_regeneration > 0) {
                    monsterHP += enemy_regeneration;
                    if (monsterHP > monsterMaxHP) monsterHP = monsterMaxHP;
                    monsterLog += " " + monsterName + " regenerates " + to_string(enemy_regeneration) + " HP!";
                    enemy_regeneration -= 1;
                }
            
                if (monsterHP > monsterMaxHP) monsterHP = monsterMaxHP;

                if (playerHP <= 0) {
                    playerHP = 0;
                    displayBattleScreen();
                    cout << "\nDEFEAT! You were beaten by the " << monsterName << ". Game Over.\n";
                    break;
                }

                generateNextIntent(); 
            } else {
                playerLog = "Out of range choice allocation selected.";
            }
        } else if (choice == 2) {
            cout << "\nYou ran away from combat!\n";
            break;
        } else {
            playerLog = "Invalid selection.";
        }
    }
    return 0;
}