#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int index;
    int score;
} mmMove;

void xTurn(char *board), oTurn(char *board);
int checkWin(char *board, char player), checkTie(char *board);

char human = 'X';
char computer = 'O';
