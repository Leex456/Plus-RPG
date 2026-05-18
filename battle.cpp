#include <iostream>
#include <string>
#include <iomanip> // Used for clean text spacing alignment

using namespace std;

// Placeholder
int playerHP = 100;
int playerMaxHP = 100;
int monsterHP = 45;
int monsterMaxHP = 100;

string monsterName = "Slime";
string combatLog = "Select Action";

//health bars
string generateHealthBar(int current, int max, int barWidth = 10) 
{
    if (current < 0) current = 0;
    
    int filledSegments = (current * barWidth) / max;
    if (filledSegments == 0 && current > 0) filledSegments = 1; // Show life if alive

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

void displayBattleScreen() 
{
    constexpr int SCREEN_WIDTH = 60;
    
    // Top Decorative Boundary Border
    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";

    // Character Names
    string playerHeader = "  PLAYER";
    string monsterHeader = monsterName;
    
    int spacesBetweenHeaders = SCREEN_WIDTH - 2 - playerHeader.length() - monsterHeader.length();
    
    cout << "|" << playerHeader;
    for (int i = 0; i < spacesBetweenHeaders; i++) cout << " ";
    cout << monsterHeader << "|\n";

    // HP Stats and Health Bars
    string playerHPStr = "  HP: " + generateHealthBar(playerHP, playerMaxHP) + " " + to_string(playerHP) + "/" + to_string(playerMaxHP);
    string monsterHPStr = "HP: " + generateHealthBar(monsterHP, monsterMaxHP) + " " + to_string(monsterHP) + "/" + to_string(monsterMaxHP) + "  ";
    
    int spacesBetweenHP = SCREEN_WIDTH - 2 - playerHPStr.length() - monsterHPStr.length();
    
    cout << "|" << playerHPStr;
    for (int i = 0; i < spacesBetweenHP; i++) cout << " ";
    cout << monsterHPStr << "|\n";

    // Middle Divider
    cout << "|";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << " ";
    cout << "|\n";

    // ("VS")
    string vsText = "VS";
    int vsPadding = (SCREEN_WIDTH - 2 - vsText.length()) / 2;
    
    cout << "|";
    for (int i = 0; i < vsPadding; i++) cout << " ";
    cout << vsText;
    // Account for odd-integer rounding variations safely
    for (int i = 0; i < vsPadding; i++) cout << " ";
    if ((SCREEN_WIDTH - 2 - vsText.length()) % 2 != 0) cout << " "; 
    cout << "|\n";

    // Extra vertical framing space
    for (int r = 0; r < 2; r++) {
        cout << "|";
        for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << " ";
        cout << "|\n";
    }

    // Action Menu UI Block
    cout << "|  [Action Menu]" << string(SCREEN_WIDTH - 18, ' ') << "|\n";
    cout << "|  1. Select Potion" << string(SCREEN_WIDTH - 21, ' ') << "|\n";
    cout << "|  2. Run Away" << string(SCREEN_WIDTH - 16, ' ') << "|\n";

    // Close Main Box Block
    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";

    // Action Combat Feed Box
    cout << "| LOG: " << combatLog;
    // Compute padding needed to ensure the right border line aligns perfectly
    int logPadding = SCREEN_WIDTH - 8 - combatLog.length(); 
    if (logPadding > 0) {
        for (int i = 0; i < logPadding; i++) cout << " ";
    }
    cout << "|\n";

    // Close Combat Feed Box
    cout << "+";
    for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
    cout << "+\n";
}

int main() 
{
    displayBattleScreen();
    return 0;
}