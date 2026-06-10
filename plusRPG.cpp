#include <iostream>
#include <conio.h>
#include <string>
#include "battle.h"

using namespace std;

//global variables
string player = "@";
int posX=27, posY=50;   //initial position of the player

void console_clear_screen() 
{
  system("cls");
}

string map[54][54];

//generate the map
void initializeMap() 
{
    for (int i = 0; i < 54; i++) 
    {
        for (int j = 0; j < 54; j++) 
        {
            if (i == 0 || i == 53 || j == 0 || j == 53 || i == 1 || i == 52 || j == 1 || j == 52)
            {
                map[i][j] = " ";  //space
            }
            else if (i == 2 || i == 51 || j == 2 || j == 51)
            {
                map[i][j] = "#";  //wall
            }
            else
                map[i][j] = ".";  //floor
        }
    }

    //walls and rooms
    for (int i = 3; i < 13; i++) {
        map[6][i] = "#";
    } map[6][4] = ".";

    for (int i = 3; i < 22; i++) {
        map[13][i] = "#";
    } map[13][10] = "."; map[13][17] = "."; map[13][18] = ".";

    for (int i = 41; i < 51; i++) {
        map[13][i] = "#";
    }

    for (int i = 3; i < 51; i++) {
        map[22][i] = "#";
    } map[22][5] = "."; map[22][28] = "."; map[22][39] = ".";

    for (int i = 3; i < 51; i++) {
        map[32][i] = "#";
    } map[32][13] = "."; map[32][27] = "."; map[32][42] = "."; map[32][43] = "."; map[32][44] = "."; 

    for (int i = 3; i < 51; i++) {
        map[40][i] = "#";
    } map[40][15] = "."; map[40][26] = "."; map[40][27] = "."; map[40][28] = "."; map[40][35] = ".";

    for (int i = 45; i < 51; i++) {
        map[43][i] = "#";
    } map[43][46] = ".";

    for (int i = 3; i < 36; i++) {
        map[45][i] = "#";
    } map[45][11] = "."; map[45][12] = "."; map[45][23] = "."; map[45][27] = "."; map[45][33] = ".";

    for (int i = 45; i < 51; i++) {
        map[47][i] = "#";
    } map[47][50] = ".";

    for (int i = 6; i < 14; i++) {
        map[i][7] = "#";
    } map[10][7] = ".";
    for (int i = 32; i < 46; i++) {
        map[i][7] = "#";
    } map[36][7] = "."; map[43][7] = ".";

    for (int i = 22; i < 33; i++) {
        map[i][10] = "#";
    }
    for (int i = 45; i < 51; i++) {
        map[i][10] = "#";
    } map[24][10] = "."; map[46][10] = ".";

    for (int i = 3; i < 14; i++) {
        map[i][13] = "#";
    }
    for (int i = 40; i < 50; i++) {
        map[i][13] = "#";
    } map[9][13] = "."; map[50][13] = ".";

    for (int i = 13; i < 41; i++) {
        map[i][16] = "#";
    } map[18][16] = "."; map[27][16] = "."; map[36][16] = ".";

    for (int i = 45; i < 51; i++) {
        map[i][17] = "#";
    } map[46][17] = ".";

    for (int i = 45; i < 51; i++) {
        map[i][21] = "#";
    } map[50][21] = ".";

    for (int i = 3; i < 33; i++) {
        map[i][22] = "#";
    } map[11][22] = "."; map[27][22] = ".";

    for (int i = 32; i < 51; i++) {
        map[i][25] = "#";
    } map[37][25] = "."; map[42][25] = ".";

    for (int i = 32; i < 51; i++) {
        map[i][29] = "#";
    } map[37][29] = "."; map[42][29] = ".";

    for (int i = 22; i < 32; i++) {
        map[i][32] = "#";
    } map[27][32] = ".";    

    for (int i = 45; i < 51; i++) {
        map[i][35] = "#";
    } 

    for (int i = 3; i < 14; i++) {
        map[i][41] = "#";
    } map[7][41] = "."; map[8][41] = ".";  map[9][41] = ".";  
    for (int i = 32; i < 51; i++) {
        map[i][41] = "#";
    } map[38][41] = "."; map[43][41] = ".";  map[44][41] = ".";  map[45][41] = ".";
    
    for (int i = 13; i < 51; i++) {
        map[i][45] = "#";
    } map[16][45] = "."; map[25][45] = ".";  map[35][45] = ".";  map[41][45] = "."; map[42][45] = ".";

    //enemies
    map[8][5] = "E";
    map[10][8] = "E";
    map[5][19] = "E";
    map[10][17] = "E";
    map[17][18] = "E";
    map[18][13] = "E";
    map[15][6] = "E";
    map[17][24] = "E";
    map[7][26] = "E";
    map[11][29] = "E";
    map[6][35] = "E";
    map[16][35] = "E";
    map[19][42] = "E";
    map[10][45] = "E";
    map[6][46] = "E";
    map[4][49] = "E";
    map[10][49] = "E";
    map[16][49] = "E";
    map[24][4] = "E";
    map[36][4] = "E";
    map[47][4] = "E";
    map[29][7] = "E";
    map[49][7] = "E";
    map[42][9] = "E";
    map[34][10] = "E";
    map[26][13] = "E";
    map[37][14] = "E";
    map[46][15] = "E";
    map[42][17] = "E";
    map[48][19] = "E";
    map[28][20] = "E";
    map[36][22] = "E";
    map[47][23] = "E";
    map[46][27] = "E";
    map[41][27] = "E";
    map[36][27] = "E";
    map[34][32] = "E";
    map[48][32] = "E";
    map[25][36] = "E";
    map[37][38] = "E";
    map[43][38] = "E";
    map[30][39] = "E";
    map[45][42] = "E";
    map[28][48] = "E";
    map[33][50] = "E";
    map[45][50] = "E";

    //bosses
    map[4][10] = "B";
    map[42][3] = "B";
    map[7][50] = "B";
    map[49][47] = "B";
    map[27][27] = "D";

}

void borderPrint()
{
    for(int i = 0; i < 5; i++)
    {
        cout << "_____________";
    }
}

//display only in a 5x5 area around the player with a border
void displayMap() 
{
    int startY = posY - 2;
    int startX = posX - 2;
    
    const int CONTENT_WIDTH = 5;
    const int CONTENT_HEIGHT = 5;
    const int HORIZONTAL_SPACING = 3;
    const int VERTICAL_SPACING = 2;
    
    int totalWidth = CONTENT_WIDTH + (HORIZONTAL_SPACING * 2);
    int totalHeight = CONTENT_HEIGHT + (VERTICAL_SPACING * 2);
    
    // Create a 2D array to hold the framed content
    string frame[totalHeight][totalWidth];
    
    // Initialize frame with spaces
    for (int i = 0; i < totalHeight; i++) {
        for (int j = 0; j < totalWidth; j++) {
            frame[i][j] = " ";
        }
    }
    
    // Place the map content in the center of the frame
    for (int y = 0; y < CONTENT_HEIGHT; y++) {
        for (int x = 0; x < CONTENT_WIDTH; x++) {
            frame[y + VERTICAL_SPACING][x + HORIZONTAL_SPACING] = map[startY + y][startX + x];
        }
    }
    
    // Draw top border
    for (int x = 0; x < totalWidth; x++) {
        frame[0][x] = "-";
    }
    frame[0][0] = "+";
    frame[0][totalWidth - 1] = "+";
    
    // Draw bottom border
    for (int x = 0; x < totalWidth; x++) {
        frame[totalHeight - 1][x] = "-";
    }
    frame[totalHeight - 1][0] = "+";
    frame[totalHeight - 1][totalWidth - 1] = "+";
    
    // Draw left and right borders
    for (int y = 1; y < totalHeight - 1; y++) {
        frame[y][0] = "|";
        frame[y][totalWidth - 1] = "|";
    }
    
    // Print the top border line
    for (int x = 0; x < totalWidth; x++) {
        cout << frame[0][x];
    }
    cout << endl;
    
    // Print the rest of the frame
    for (int y = 1; y < totalHeight; y++) {
        for (int x = 0; x < totalWidth; x++) {
            cout << frame[y][x];
        }
        cout << endl;
    }
}


string generateOverworldHealthBar(int currentHP, int maxHP) {
    if (maxHP <= 0) return "[]";
    int barLength = 20; 
    int filledLength = (currentHP * barLength) / maxHP;
    if (filledLength < 0) filledLength = 0;
    if (filledLength > barLength) filledLength = barLength;

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

void displayHUD() {
    cout << "======================================\n";
    cout << "  HP: " << playerHP << "/" << playerMaxHP << " " 
         << generateOverworldHealthBar(playerHP, playerMaxHP) << "\n";
    cout << "======================================\n";

    Item* current = bag.head;
    
    if (current == NULL) {
        cout << "  (No potions in inventory)\n";
    } else {
        while (current != NULL) {
            string originalName = current->name;
            size_t bracketPos = originalName.find("]");
            
            if (bracketPos != string::npos) {
                cout << " " << originalName.substr(0, bracketPos + 1) << "\n";
            } else {
                cout << " " << originalName << "\n";
            }
            current = current->next;
        }
    }
    cout << "======================================\n";
    cout << "  Use Arrow keys to move around map\n";
}

int collisionDetection(int x, int y)
{
    if(map[y][x] == "#") return 1;   
    return 0;   
}

int playerMovement(int& posX, int& posY)
{
    char input;      
    bool gameRunning = true;

    while(gameRunning)
    {
        int previousPositionX = posX, previousPositionY = posY;  
        int nextX = posX;
        int nextY = posY;

        input = _getch();  

        if(input==72) nextY--;      
        else if(input==80) nextY++; 
        else if(input==75) nextX--; 
        else if(input==77) nextX++; 

        if (!collisionDetection(nextX, nextY))
        {
            string targetTile = map[nextY][nextX];

            if (targetTile == "E" || targetTile == "B" || targetTile == "D") 
            {
                bool victory = startBattle(targetTile);

                if (victory) {
                    map[previousPositionY][previousPositionX] = " ";   
                    posX = nextX;
                    posY = nextY;
                    map[posY][posX] = player;   
                } else {
                    console_clear_screen();
                    cout << "\n===================================\n";
                    cout << "   GAME OVER - YOU WERE DEFEATED   \n";
                    cout << "===================================\n";
                    gameRunning = false;
                    break;
                }
            }
            else 
            {
                map[previousPositionY][previousPositionX] = ".";   
                posX = nextX;
                posY = nextY;
                map[posY][posX] = player;   
            }
        }

        if (gameRunning) {
            console_clear_screen();      
            displayMap();                
            displayHUD(); // Render active UI screen updates on step loop
        }
    }
    return 0;
}

void mainMenu()
{
    string line1 = R"(  _____       _      _____      _   _              _____                      )"; 
    string line2 = R"( |  __ \     | |    |  __ \    | | (_)            / ____|                     )";
    string line3 = R"( | |__) |___ | | ___| |__) |__ | |_ _  ___  _ __ | |  __  __ _ _ __ ___   ___ )";
    string line4 = R"( |  _  // _ \| |/ _ \  ___/ _ \| __| |/ _ \| '_ \| | |_ |/ _` | '_ ` _ \ / _ \)";
    string line5 = R"( | | \ \ (_) | |  __/ |  | (_) | |_| | (_) | | | | |__| | (_| | | | | | |  __/)";
    string line6 = R"( |_|  \_\___/|_|\___|_|   \___/ \__|_|\___/|_| |_|\_____|\__,_|_| |_| |_|\___|)";

    cout << line1 << endl;
    cout << line2 << endl;
    cout << line3 << endl;
    cout << line4 << endl;
    cout << line5 << endl;
    cout << line6 << endl << endl;

    cout << "Press Enter to Start!\n";
    cin.get();
}

int main()
{
    initializeMap();
    map[posY][posX] = player;  
    bag.addItem("[Attack Potion] Deals 1 DMG, return this potion at end of turn");
    bag.addItem("[Defend Potion] Block 2 DMG, return this potion at end of turn");
    relic.addItem("[The Destruction] Heal 25% HP at the end of each fight, and raise max HP by 1");

    mainMenu();
    console_clear_screen();      
    displayMap();                
    displayHUD(); 
    playerMovement(posX, posY);   

    return 0;
}



