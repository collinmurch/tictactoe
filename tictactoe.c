#include "tictactoe.h"

char human = 'X';
char computer = 'O';

int promptForInt(const char *prompt, int low, int high) {
    int choice;

    while (1) {
        const int size = 5;
        char buffer[size];
        printf("%s\n\n", prompt);

        if (fgets(buffer, size, stdin) == NULL) {
            return 0;
        }
        if (sscanf(buffer, "%d", &choice) != 1 ) {
            printf("\nPlease enter a valid number.\n\n");
        }
        else if (choice > high || choice < low) {
            printf("\nNumber is not within the correct range.\n\n");
        }
        else break;
    }

    return choice;
}

void printBoard(char *board) {
    printf("\n\n");
    for (int i = 1; i < 10; i++) {
        printf("%c ", board[i-1]);
        if (i % 3 == 0) printf("\n");
    }
    printf("\n\n");
}

char *resetBoard(char *board) {
    for (int i = 0; i < 9; i++) {
        board[i] = '-';
    }

    return board;
}

int user(char *board) {
    while (1) {
        int move = promptForInt("Please enter a move (1 - 9):", 1, 9);
        move--;

        if (board[move] == '-') {
            return move;
        } else {
            printf("Move taken.\n");
            printBoard(board);
        }
    }

    return -1;
}

int randomMove() {
    srand(time(0));

    int num = rand() % 9;

    return num;
}

mmMove minimax(char *board, char player) {
    mmMove lose = {-1, -10};
    mmMove win = {-1, 10};
    mmMove tie = {-1, 0};

    if (checkWin(board, human)) return lose;
    if (checkWin(board, computer)) return win;
    if (checkTie(board)) return tie;

    // Get array of open spots
    int count = 0;

    for (int i = 0; i < 9; i++) {
        if (board[i] == '-') count++;
    }

    int freeSpots[count];
    int pointer = 0;

    for (int i = 0; i < 9; i++) {
        if (board[i] == '-') {
            freeSpots[pointer] = i;
            pointer++;
        }
    }

    // Begin actual recursion
    mmMove moves[count];

    for (int i = 0; i < count; i++) {
        mmMove move;

        move.index = freeSpots[i];
        board[freeSpots[i]] = player;

        if (player == human) {
            move.score = minimax(board, computer).score;
        } else {
            move.score = minimax(board, human).score;
        }

        moves[i] = move;
        board[freeSpots[i]] = '-';
    }

    // Choose best move depending on if computer or human is moving
    int bestMove;
    if (player == computer) {
        int bestScore = -10000;

        for (int i = 0; i < count; i++) {
            if (bestScore < moves[i].score) {
                bestScore = moves[i].score;
                bestMove = i;
            }
        }
    } else {
        int bestScore = 10000;

        for (int i = 0; i < count; i++) {
            if (bestScore > moves[i].score) {
                bestScore = moves[i].score;
                bestMove = i;
            }
        }
    }

    return moves[bestMove];
}

int ai(char *board) {
    mmMove choice = minimax(board, computer);

    printf("The AI chooses: %d\n", choice.index + 1);

    // Implement winnable game later using:
    // choice = randomMove();
    // ... assuming a check is made for validity

    return choice.index;
}

int checkWin(char *board, char player) {
    // Rows
    if (board[0] == player && board[1] == player && board[2] == player) return 1;
    if (board[3] == player && board[4] == player && board[5] == player) return 1;
    if (board[6] == player && board[7] == player && board[8] == player) return 1;

    // Columns
    if (board[0] == player && board[3] == player && board[6] == player) return 1;
    if (board[1] == player && board[4] == player && board[7] == player) return 1;
    if (board[2] == player && board[5] == player && board[8] == player) return 1;

    // Diagonals
    if (board[0] == player && board[4] == player && board[8] == player) return 1;
    if (board[2] == player && board[4] == player && board[6] == player) return 1;

    return 0;
}

int checkTie(char *board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == '-') return 0;
    }

    if (checkWin(board, human) == 0 && checkWin(board, computer) == 0) return 1;

    return 0;
}

void menu(char *board) {
    while (1) {
        int input = promptForInt("[1]: Play as X\n[2]: Play as O", 1, 2);

        board = resetBoard(board);

        if (input == 1) {
            human = 'X';
            computer = 'O';
            printBoard(board);
            break;
        } else if (input == 2) {
            human = 'O';
            computer = 'X';
            printBoard(board);
            break;
        } else {
            printf("Please enter a valid option\n\n");
        }
    }

    xTurn(board);
}

int checkEnd(char *board) {
    if (checkWin(board, human)) {
        printf("You WON!\n");
        return 1;
    }
    if (checkWin(board, computer)) {
        printf("The computer won...\n");
        return 1;
    }
    if (checkTie(board)) {
        printf("It's a tie.\n");
        return 1;
    }

    return 0;
}

int main() {
    char *board = malloc(sizeof(char) * 9);

    menu(board);

    printf("Thanks for playing!\n");

    free(board);

    return 0;
}

void xTurn(char *board) {
    if (checkEnd(board)) return;

    int move;

    human == 'X' ? (move = user(board)) : (move = ai(board));

    board[move] = 'X';
    printBoard(board);

    oTurn(board);
}

void oTurn(char *board) {
    if (checkEnd(board)) return;

    int move;

    human == 'O' ? (move = user(board)) : (move = ai(board));

    board[move] = 'O';
    printBoard(board);

    xTurn(board);
}
