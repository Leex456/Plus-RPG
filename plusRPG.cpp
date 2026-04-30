#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

//global variables
string player = "@";
int posX=3, posY=3;   //initial position of the player

void console_clear_screen() 
{
  system("cls");
}

string map[52][52];

//generate the map
void initializeMap() 
{
    for (int i = 0; i < 52; i++) 
    {
        for (int j = 0; j < 52; j++) 
        {
            if (i == 0 || i == 51 || j == 0 || j == 51 || i == 1 || i == 50 || j == 1 || j == 50)
            {
                map[i][j] = " ";  //space
            }
            else if (i == 2 || i == 49 || j == 2 || j == 49)
            {
                map[i][j] = "#";  //wall
            }
            else
                map[i][j] = "-";  //floor
        }
    }
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
        map[previousPositionY][previousPositionX] = "-";   
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




