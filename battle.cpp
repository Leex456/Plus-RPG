#include <iostream>
#include <string>
#include <iomanip> 
#include <cstdlib> 
#include <ctime>   
#include "Invent.h" // Make sure this matches your exact filename (Invent.h or invent.h)

using namespace std;

// Game State Variables
int playerHP = 20;
int playerMaxHP = 20;
int monsterHP = 5;
int monsterMaxHP = 5;

int enemy_strength = 0;
int player_strength = 0;   

int enemy_dmg = 0;


string monsterName = "Goblin";
string monsterLog = ""; 
string playerLog = "";
string enemyIntent = "";
string enemyIntentType = ""; 


// Helper function INVENT
int countPotions(Inventory& inv) {
    int count = 0;
    Item* temp = inv.head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Helper function to display potions numerically
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

// Helper function to grab item name at a numeric position
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

// Health bar generator
string generateHealthBar(int current, int max, int barWidth = 10) 
{
    if (current < 0) current = 0;
    
    int filledSegments = (current * barWidth) / max;
    if (filledSegments == 0 && current > 0) filledSegments = 1;

    string bar = "[";
    for (int i = 0; i < barWidth; i++) {
        if (i < filledSegments) {
            bar += "|"; 
        } else {
            bar += "-"; 
        }
    }
    bar += "]";
    return bar;
}

// Renders
void displayBattleScreen() 
{
    #ifdef _WIN32
        system("cls");  // Windows 
    #else
        system("clear"); // Linux / macOS 
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

    cout << "|  [Action Menu]" << string(SCREEN_WIDTH - 17, ' ') << "|\n";
    cout << "|  1. Select Potion" << string(SCREEN_WIDTH - 20, ' ') << "|\n";
    cout << "|  2. Run Away" << string(SCREEN_WIDTH - 15, ' ') << "|\n";

    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";

    cout << "|  LOG: " + playerLog;
    int logPadding = SCREEN_WIDTH - 9 - playerLog.length(); 
    if (logPadding > 0) cout << string(logPadding, ' ');
    cout << "|\n";

    cout << "|  LOG: " + monsterLog;
    int logPadding3 = SCREEN_WIDTH - 9 - monsterLog.length(); 
    if (logPadding3 > 0) cout << string(logPadding3, ' ');
    cout << "|\n";

    cout << "|  ENEMY INTENT: " + enemyIntent;
    int logPadding2 = SCREEN_WIDTH - 18 - enemyIntent.length(); 
    if (logPadding2 > 0) cout << string(logPadding2, ' ');
    cout << "|\n";

    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";
}

// Generate what monster plans to do next turn
void generateNextIntent() {
    int r = rand() % 3;
    
    monsterName = "Goblin";
    if (r == 0) {   
        enemyIntent = "Attack (" + to_string(1 + enemy_strength) + " DMG)";
        enemy_dmg = 1;
    }
    else if (r == 1) 
    {
        enemyIntent = "Buff (+1 DMG in this battle)";  
    }
    else 
    {
        enemyIntent = "Heavy Attack (" + to_string(2 + enemy_strength) + " DMG)";
        enemy_dmg = 2;
    }
}



int main() 
{
    srand(time(0));
    
    
    Inventory bag;
    bag.addItem("Attack Potion: Deals 1 DMG, return this potion at end of turn");
    bag.addItem("Defend Potion: Block 2 DMG, return this potion at end of turn");
    bag.addItem("Strength Potion: Increases DMG by 1 in this battle");


    generateNextIntent();

    while (playerHP > 0 && monsterHP > 0) {
        displayBattleScreen();
        cout << "Choose action (1-2): ";
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
                int heal = 0;
                int block = 0;
                if (chosenPotion == "Attack Potion: Deals 1 DMG, return this potion at end of turn") {
                    dmg = 1;
                    bag.addItem("Attack Potion: Deals 1 DMG, return this potion at end of turn");
                    playerLog = "Player used Attack Potion, dealing 1 DMG.";

                } else if (chosenPotion == "Strength Potion: Increases DMG by 1 in this battle") {
                    player_strength += 1;
                    playerLog = "Player used Strength Potion, increasing damage by 1!";

                } else if (chosenPotion == "Defend Potion: Block 2 DMG, return this potion at end of turn") {
                    block = 2;
                    bag.addItem("Defend Potion: Block 2 DMG, return this potion at end of turn");
                    playerLog = "Player used Defend Potion, blocking 2 DMG.";
                }

                // Process Player turn actions
                if (dmg > 0) {
                    monsterHP -= dmg + player_strength;
                }
                playerHP += heal;
                if (playerHP > playerMaxHP) playerHP = playerMaxHP;


                if (monsterHP <= 0) {
                    monsterHP = 0;
                    monsterLog = playerLog + " " + monsterName + " was crushed!";
                    displayBattleScreen();
                    cout << "\nVICTORY! You defeated the monster!\n";
                    break;
                }


                // Process Monster counter turn action

                if (enemyIntent.find("Attack") != string::npos) {
                    enemy_dmg += enemy_strength;
                    int damageAfterBlock = enemy_dmg - block;
                    if (damageAfterBlock < 0) damageAfterBlock = 0;
                    playerHP -= damageAfterBlock;
                    monsterLog = monsterName + " attacks for " + to_string(enemy_dmg) + " DMG! Player blocks " + to_string(block) + " DMG.";
                }
                else if (enemyIntent.find("Buff") != string::npos) {
                    enemy_strength += 1;
                    monsterLog = monsterName + " buffs itself";
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