// Tic Tac Toe (Player vs Computer)
// Made while practicing C++ basics in 2nd semester

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// board setup
char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

// prints the board
void showBoard() {
    cout << "\nBoard:\n";
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// place X or O if spot is free
bool makeMove(int pos, char ch) {
    int r = (pos - 1) / 3;
    int c = (pos - 1) % 3;

    if(board[r][c] != 'X' && board[r][c] != 'O') {
        board[r][c] = ch;
        return true;
    }
    return false;
}

// check winner
bool checkWinner(char ch) {
    for(int i = 0; i < 3; i++) {
        if(board[i][0]==ch && board[i][1]==ch && board[i][2]==ch)
            return true;

        if(board[0][i]==ch && board[1][i]==ch && board[2][i]==ch)
            return true;
    }

    if(board[0][0]==ch && board[1][1]==ch && board[2][2]==ch)
        return true;

    if(board[0][2]==ch && board[1][1]==ch && board[2][0]==ch)
        return true;

    return false;
}

// tries to find winning or blocking move
int tryMove(char ch) {
    for(int pos = 1; pos <= 9; pos++) {

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;

        if(board[r][c] != 'X' && board[r][c] != 'O') {

            char temp = board[r][c];
            board[r][c] = ch;

            if(checkWinner(ch)) {
                board[r][c] = temp;
                return pos;
            }

            board[r][c] = temp;
        }
    }
    return -1;
}

// computer logic (sometimes smart, sometimes random)
int computerMove() {

    // sometimes random move first
    if(rand()%2 == 0) {
        while(true) {
            int p = rand()%9 + 1;
            int r = (p - 1) / 3;
            int c = (p - 1) % 3;

            if(board[r][c] != 'X' && board[r][c] != 'O')
                return p;
        }
    }

    // try to win
    int move = tryMove('O');
    if(move != -1) return move;

    // block player
    move = tryMove('X');
    if(move != -1) return move;

    // fallback random
    while(true) {
        int p = rand()%9 + 1;
        int r = (p - 1) / 3;
        int c = (p - 1) % 3;

        if(board[r][c] != 'X' && board[r][c] != 'O')
            return p;
    }
}

int main() {

    srand(time(0));
    int move;

    cout << "Tic Tac Toe (You = X, Computer = O)\n";

    for(int turn = 0; turn < 9; turn++) {

        showBoard();

        if(turn % 2 == 0) {
            cout << "Enter position: ";
            cin >> move;

            if(!makeMove(move,'X')) {
                cout << "Try another spot\n";
                turn--;
                continue;
            }
        }
        else {
            move = computerMove();
            makeMove(move,'O');
            cout << "Computer played: " << move << endl;
        }

        if(checkWinner('X')) {
            showBoard();
            cout << "Nice, you won!\n";
            return 0;
        }

        if(checkWinner('O')) {
            showBoard();
            cout << "Computer won this time\n";
            return 0;
        }
    }

    showBoard();
    cout << "Game draw\n";

    return 0;
}
