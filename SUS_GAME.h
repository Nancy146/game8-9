#ifndef _SUS_GAME_H
#define _SUS_GAME_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Sus_Board : public Board<T> {
public:
    Sus_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void count_sus_sequences(char last_player, int last_x, int last_y);
    void display_sus_counts();

    int sus_count_player1 = 0;  // Track SUS sequences for Player 1 (S)
    int sus_count_player2 = 0;  // Track SUS sequences for Player 2 (U)

private:
    vector<vector<bool>> checked_sequences;  // Track already counted sequences to avoid double-counting
};

template <typename T>
class Sus_Player : public Player<T> {
public:
    Sus_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Sus_Random_Player : public RandomPlayer<T> {
public:
    Sus_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

// Board Constructor
template <typename T>
Sus_Board<T>::Sus_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0; // Empty cell
        }
    }
    this->n_moves = 0;

    // Initialize checked_sequences to mark whether a line has been counted
    checked_sequences = vector<vector<bool>>(this->rows, vector<bool>(this->columns, false));
}

template <typename T>
bool Sus_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = symbol;
        this->n_moves++;

        // Track the last player to make the move
        char last_player = symbol;

        // Count SUS sequences after every move, passing last_x and last_y
        count_sus_sequences(last_player, x, y);

        display_sus_counts();

        return true;
    }
    return false;
}

// Display the Board
template <typename T>
void Sus_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            cout << (this->board[i][j] == 0 ? "." : string(1, this->board[i][j])) << " ";
        }
        cout << endl;
    }
}

template <typename T>
void Sus_Board<T>::count_sus_sequences(char last_player, int last_x, int last_y) {

    auto check_sequence_S = [&](int x1, int y1, int x2, int y2) {
        // Ensure indices are within bounds
        if (x1 < 0 || x1 >= this->rows || y1 < 0 || y1 >= this->columns ||
            x2 < 0 || x2 >= this->rows || y2 < 0 || y2 >= this->columns) {
            return false;
        }
        // Check the S-U-S pattern
        return (this->board[x1][y1] == 'U' && this->board[x2][y2] == 'S');
    };

    if (last_player == 'S') {
        // Horizontal: Check before and after
        if (last_y - 2 >= 0 && check_sequence_S(last_x, last_y - 1, last_x, last_y - 2)) {
            sus_count_player1++;
        }
        if (last_y + 2 < this->columns && check_sequence_S(last_x, last_y + 1, last_x, last_y + 2)) {
            sus_count_player1++;
        }

        // Vertical: Check before and after
        if (last_x - 2 >= 0 && check_sequence_S(last_x - 1, last_y, last_x - 2, last_y)) {
            sus_count_player1++;
        }
        if (last_x + 2 < this->rows && check_sequence_S(last_x + 1, last_y, last_x + 2, last_y)) {
            sus_count_player1++;
        }

        // Diagonal (Top-left to Bottom-right)
        if (last_x - 2 >= 0 && last_y - 2 >= 0 && check_sequence_S(last_x - 1, last_y - 1, last_x - 2, last_y - 2)) {
            sus_count_player1++;  // S-U-S diagonally up-left
        }
        if (last_x + 2 < this->rows && last_y + 2 < this->columns &&
            check_sequence_S(last_x + 1, last_y + 1, last_x + 2, last_y + 2)) {
            sus_count_player1++;  // S-U-S diagonally down-right
        }

        // Diagonal (Top-right to Bottom-left)
        if (last_x - 2 >= 0 && last_y + 2 < this->columns &&
            check_sequence_S(last_x - 1, last_y + 1, last_x - 2, last_y + 2)) {
            sus_count_player1++;  // S-U-S diagonally up-right
        }
        if (last_x + 2 < this->rows && last_y - 2 >= 0 &&
            check_sequence_S(last_x + 1, last_y - 1, last_x + 2, last_y - 2)) {
            sus_count_player1++;  // S-U-S diagonally down-left
        }
    }



    // Helper lambda to check for "SUS" sequence
    auto check_sequence = [&](int x1, int y1, int x2, int y2, int x3, int y3) {
        // Check if the three positions form "SUS" sequence
        if (this->board[x1][y1] == 'S' && this->board[x2][y2] == 'U' && this->board[x3][y3] == 'S') {
            return true;
        }
        return false;
    };

    if (last_y - 1 >= 0 && last_y + 1 < this->columns) {
        if (last_player == 'U' && check_sequence(last_x, last_y - 1, last_x, last_y, last_x, last_y + 1)) {
            sus_count_player2++;
        }
    }

    // Vertical Sequences (around the last move)
    if (last_x - 1 >= 0 && last_x + 1 < this->rows) {
        if (last_player == 'U' && check_sequence(last_x - 1, last_y, last_x, last_y, last_x + 1, last_y)) {
            sus_count_player2++;
        }
    }

    // Diagonal Sequences (Top-left to Bottom-right)
    if (last_x - 1 >= 0 && last_y - 1 >= 0 && last_x + 1 < this->rows && last_y + 1 < this->columns) {
        if (last_player == 'U' &&
            check_sequence(last_x - 1, last_y - 1, last_x, last_y, last_x + 1, last_y + 1)) {
            sus_count_player2++;
        }
    }

    // Diagonal Sequences (Top-right to Bottom-left)
    if (last_x - 1 >= 0 && last_y + 1 < this->columns && last_x + 1 < this->rows && last_y - 1 >= 0) {
        if (last_player == 'U' &&
            check_sequence(last_x - 1, last_y + 1, last_x, last_y, last_x + 1, last_y - 1)) {
            sus_count_player2++;
        }
    }


}


template <typename T>
void Sus_Board<T>::display_sus_counts() {
    cout << "Player 1 (S) has " << sus_count_player1 << " SUS sequences." << endl;
    cout << "Player 2 (U) has " << sus_count_player2 << " SUS sequences." << endl;
}

template <typename T>
bool Sus_Board<T>::is_win() {
    // The winner is the player with the most SUS sequences
    if (this->n_moves == this->rows * this->columns) {
        if (sus_count_player1 > sus_count_player2) {
            cout << "Player 1 wins with " << sus_count_player1 << " SUS sequences!" << endl;
        } else if (sus_count_player2 > sus_count_player1) {
            cout << "Player 2 wins with " << sus_count_player2 << " SUS sequences!" << endl;
        } else {
            cout << "It's a draw! Both players have the same number of SUS sequences." << endl;
            return false;
        }
        return true;
    }
    return false;
}

template <typename T>
bool Sus_Board<T>::is_draw() {
    return (this->n_moves == this->rows * this->columns) && (sus_count_player1 == sus_count_player2);
}

// Check if Game is Over
template <typename T>
bool Sus_Board<T>::game_is_over() {
    return is_win();
}

// Player Constructor
template <typename T>
Sus_Player<T>::Sus_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Get Move from Player
template <typename T>
void Sus_Player<T>::getmove(int& x, int& y) {
    cout << this->getname() << ", enter your move (row and column): ";
    cin >> x >> y;
}

// Random Player Constructor
template <typename T>
Sus_Random_Player<T>::Sus_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

// Get Move for Random Player
template <typename T>
void Sus_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 3;
}

#endif //_SUS_GAME_H