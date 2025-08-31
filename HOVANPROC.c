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
    return newPlayer;
}
// Add player to the list
void addPlayer(Player* newPlayer) {
    newPlayer->next = head;
    head = newPlayer;
}
// Check login
Player* checkLogin(const char* username, const char* password) {
    Player* current = head;
    while (current) {
        if (strcmp(current->username, username) == 0 &&
            strcmp(current->password, password) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
// Set up the board before the game starts
void setupBoard() {
    // Loop through every row
    for (int i = 0; i < SIZE; i++)
        // Loop through every column in that row
        for (int j = 0; j < SIZE; j++) {
            board[i][j].isMine = 0;       // No mine in this cell
            board[i][j].revealed = 0;     // Cell is hidden
            board[i][j].nearbyMines = 0;  // No nearby mines counted yet
        }
}
// Place mines randomly on the board
void placeMines() {
    int count = 0;
    while (count < MINES) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (!board[r][c].isMine) {
            board[r][c].isMine = 1;
            count++;
        }
    }
}
// Count
void countNearbyMines() {
    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].isMine) continue; // Skip if it's a mine
            int count = 0;
            
            for (int x = -1; x <= 1; x++)       // Rows around the cell
                for (int y = -1; y <= 1; y++) { // Columns around the cell
                    int ni = i + x;
                    int nj = j + y;
                    // Make sure we're inside the board
                    if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE)
                        count += board[ni][nj].isMine; // Add if it's a mine
                }
            board[i][j].nearbyMines = count; // Save the count
        }
}
// Show the board to the player
void displayBoard() {
    printf("   ");
    for (int i = 0; i < SIZE; i++) printf("%d ", i); // Print 
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d: ", i); // Print row number
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j].revealed) {
                if (board[i][j].isMine) printf("* ");
                else printf("%d ", board[i][j].nearbyMines);
            }
            else {
                printf(". ");
            }
        }
        printf("\n");
    }
}
// Reveal a cell and return result
int revealCell(int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col].revealed)
        return 0;
    board[row][col].revealed = 1;
    return board[row][col].isMine ? -1 : board[row][col].nearbyMines;
}
// Play the game
void playGame(Player* player) {
    int moves = 0;
    while (1) {
        displayBoard();
        int r, c;
        printf("Enter row and column: ");
        scanf("%d %d", &r, &c);
        int result = revealCell(r, c);
        if (result == -1) {
            printf("Boom! You hit a mine.\n");
            break;
        }
        else {
            printf("Safe! %d mines nearby.\n", result);
            player->score += 10;
            moves++;
        }
        // Win condition: all safe cells revealed
        if (moves == (SIZE * SIZE - MINES)) {
            printf("You cleared the board! Well done!\n");
            break;
        }
    }
    printf("Your final score: %d\n", player->score);
}
// Start the game
int main() {
    srand(time(NULL)); // Set up random numbers
    char username[MAX_NAME], password[MAX_NAME];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    // Try to log in
    Player* player = checkLogin(username, password);
    if (!player) {
        printf("New player created.\n");
        player = createPlayer(username, password);
        addPlayer(player);
    }
    else {
        printf("Welcome back, %s!\n", player->username);
    }
    // Set up 
    setupBoard();         
    placeMines();         
    countNearbyMines();   // Count nearby mines for each cell
    playGame(player);     // Start the game
    return 0;
}