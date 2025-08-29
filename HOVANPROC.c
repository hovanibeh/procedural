#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 8
#define MINES 10
#define MAX_NAME 50
// Player info
typedef struct Player {
    char username[MAX_NAME];
    char password[MAX_NAME];
    int score;
    struct Player* next;
} Player;
Player* head = NULL;
// Cell info
typedef struct {
    int isMine;
    int revealed;
    int nearbyMines;
} Cell;
Cell board[SIZE][SIZE];
// Create a new player
Player* createPlayer(const char* username, const char* password) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    strcpy(newPlayer->username, username);
    strcpy(newPlayer->password, password);
    newPlayer->score = 0;
    newPlayer->next = NULL;
    
}
   
