#include <stdio.h>
#include <stdlib.h> // for rand()
#include <time.h>
#include <ctype.h>

void resetBoard();
void printBoard();
void playerMove();
void computerMove();
int checkFreeSpaces();
char checkWinner();
void printWinner(char);

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

int main() {

    char winner = ' ';
    char response = 'n';
    
    do {
        winner = ' ';
        resetBoard();
        while (winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) break;
            computerMove();
            if (winner != ' ' || checkFreeSpaces() == 0) break;
        }
        printWinner(winner);
        printf("Would you like to play again? (y/n): ");scanf("\n");
        scanf("%c", &response);
        response = tolower(response);
    } while (response == 'y');

    printf("\nTHANKS FOR PLAYING!");
    return 0;
}

void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

void playerMove() {
    char box[2];

    int x, y;
    printf("Select row (1-3): ");
    scanf("%d", &x);x--;
    printf("Select column (1-3): ");
    scanf("%d", &y);y--;

    if (board[x][y] != ' ') { 
        printf("Invalid input!\n");
        playerMove();
    } else board[x][y] = PLAYER;
    printBoard();
    
}

void computerMove() {
    int x,y;
    srand(time(0));
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');
    board[x][y] = COMPUTER;
    printBoard();
    
}

int checkFreeSpaces() {
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') freeSpaces--;
    }
    }
    return freeSpaces;
}

char checkWinner() {
    // rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0]==board[i][1] && board[i][0]==board[i][2]) return board[i][0];
    }
    // columns
    
    for (int i = 0; i < 3; i++) {
        if (board[0][i]==board[1][i] && board[0][i]==board[2][i]) return board[0][i];
    }
    // diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) return board[0][0];
    else if (board[2][0] == board[1][1] && board[2][0] == board[0][2]) return board[2][0];

    return ' ';
}

void printWinner(char winner) {
    if (winner == PLAYER) printf("YOU WON!\n");
    else if (winner == COMPUTER) printf("YOU LOST!\n");
    else printf("IT'S A TIE!\n");
}