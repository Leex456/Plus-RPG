#include <iostream>
#include <conio.h>
#include <string>

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

//detect collision with walls
int collisionDetection(int x, int y)
{
    if(map[y][x] == "#")
    {
        return 1;   //collision detected
    }
    return 0;   //no collision
}

//handle player movement based on user input
int playerMovement(int& posX, int& posY)
{
    char input;      //variable to store the user input
    
    while(1)
    {
        int previousPositionX = posX, previousPositionY = posY;  
        input = _getch();  //get the user input

        if(input==72)
        {
            if (!collisionDetection(posX, posY - 1))
            {
                posY--;    //move up
            }
        }
        else if(input==80)
        {
            if (!collisionDetection(posX, posY + 1))
            {
                posY++;    //move down
            }
        }
        else if(input==75)
        {
            if (!collisionDetection(posX - 1, posY))
            {
                posX--;    //move left
            }
        }
        else if(input==77)
        {
            if (!collisionDetection(posX + 1, posY))
            {
                posX++;    //move right
            }
        }

        console_clear_screen();      //clear the console screen
        map[previousPositionY][previousPositionX] = ".";   
        map[posY][posX] = player;   //update the player's position on the map
        displayMap();                //display the updated map
    }
}

//main function
int main()
{
    initializeMap();
    map[posY][posX] = player;   //put player in the map

    console_clear_screen();      //clear the console screen
    displayMap();                //display the initial map
    playerMovement(posX, posY);   //call the player movement function

    return 0;
}




