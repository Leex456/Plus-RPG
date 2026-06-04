#include <iostream>
using namespace std;

string map[54][54];

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

}

int main() 
{
    initializeMap();
    for (int i = 0; i < 54; i++) 
    {
        for (int j = 0; j < 54; j++) 
        {
            cout << map[i][j];
        }
    
        cout << endl;
    }
    return 0;
}