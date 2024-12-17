#ifndef _ULTIMATE_X_O_H
#define _ULTIMATE_X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
using namespace std;

// ------------------ Ultimate Tic Tac Toe Board ------------------
template <typename T>
class Ultimate_X_O_Board : public Board<T> {
public:
    Ultimate_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    bool submatrix_won[3][3];     // Track if a submatrix is won
    T main_board[3][3];           // Represents the main 3x3 meta-grid

    bool check_submatrix_win(int sub_x, int sub_y, T symbol);
    void mark_submatrix_won(int sub_x, int sub_y, T symbol);
    bool check_main_board_win(T symbol);
};

// ------------------ Player Class ------------------
template <typename T>
class Ultimate_X_O_Player : public Player<T> {
public:
    Ultimate_X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

// ------------------ Random Player ------------------
template <typename T>
class Ultimate_X_O_Random_Player : public RandomPlayer<T> {
public:
    Ultimate_X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

// ------------------ Implementation ------------------

// Constructor
template <typename T>
Ultimate_X_O_Board<T>::Ultimate_X_O_Board() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize all cells
        }
    }

    this->n_moves = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            submatrix_won[i][j] = false;
            main_board[i][j] = ' ';  // Main board starts empty
        }
    }
}

// Update Board
template <typename T>
bool Ultimate_X_O_Board<T>::update_board(int x, int y, T symbol) {
    int sub_x = x / 3, sub_y = y / 3;

    // Check if move is valid
    if (submatrix_won[sub_x][sub_y] || this->board[x][y] != 0) {
        return false;  // Submatrix is won or cell is occupied
    }

    // Update board
    this->board[x][y] = toupper(symbol);
    this->n_moves++;

    // Check for submatrix win
    if (check_submatrix_win(sub_x, sub_y, symbol)) {
        mark_submatrix_won(sub_x, sub_y, symbol);
        main_board[sub_x][sub_y] = symbol;  // Place the symbol in the main board
    }

    return true;
}

// Display Board (9x9 grid and main grid status)
template <typename T>
void Ultimate_X_O_Board<T>::display_board() {
    cout << "\nUltimate Tic Tac Toe Board:" << endl;
    cout << "------------------------------------------" << endl;

    // Display the 9x9 grid
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int sub_x = i / 3, sub_y = j / 3;
            if (submatrix_won[sub_x][sub_y]) {
                // Show winner of submatrix
                cout << "| " << main_board[sub_x][sub_y] << " ";
            } else {
                // Show the board cell or its indices if empty
                if (this->board[i][j] == 0) {
                    cout << "|   ";  // Empty cell
                } else {
                    cout << "| " << this->board[i][j] << " ";  // Show symbol
                }
            }
            // Add spacing between submatrices
            if ((j + 1) % 3 == 0 && j != 8) {
                cout << "  ";
            }
        }
        cout << "|" << endl;

        // Add horizontal dividers between submatrices
        if ((i + 1) % 3 == 0 && i != 8) {
            cout << string(10, '-') << "    " << string(10, '-') << "    " << string(13, '-') << endl;
        }
    }

    // Display the main board (3x3 grid) at the bottom
    cout << "------------------------------------------" << endl;
    cout << "\nMain Board Status:" << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "| " << main_board[i][j] << " ";
        }
        cout << "|" << endl;
        if (i <= 2) {
            cout << "-------------" << endl;
        }
    }
}


// Check if a submatrix is won
template <typename T>
bool Ultimate_X_O_Board<T>::check_submatrix_win(int sub_x, int sub_y, T symbol) {
    int start_row = sub_x * 3, start_col = sub_y * 3;
    // Check rows, columns, diagonals in the submatrix
    for (int i = 0; i < 3; i++) {
        if (this->board[start_row + i][start_col] == symbol &&
            this->board[start_row + i][start_col + 1] == symbol &&
            this->board[start_row + i][start_col + 2] == symbol)
            return true;
        if (this->board[start_row][start_col + i] == symbol &&
            this->board[start_row + 1][start_col + i] == symbol &&
            this->board[start_row + 2][start_col + i] == symbol)
            return true;
    }
    return (this->board[start_row][start_col] == symbol &&
            this->board[start_row + 1][start_col + 1] == symbol &&
            this->board[start_row + 2][start_col + 2] == symbol) ||
           (this->board[start_row + 2][start_col] == symbol &&
            this->board[start_row + 1][start_col + 1] == symbol &&
            this->board[start_row][start_col + 2] == symbol);
}

// Mark submatrix as won
template <typename T>
void Ultimate_X_O_Board<T>::mark_submatrix_won(int sub_x, int sub_y, T symbol) {
    submatrix_won[sub_x][sub_y] = true;
}

// Check for main board win
template <typename T>
bool Ultimate_X_O_Board<T>::is_win() {
    return check_main_board_win('X') || check_main_board_win('O');
}

template <typename T>
bool Ultimate_X_O_Board<T>::check_main_board_win(T symbol) {
    for (int i = 0; i < 3; i++) {
        if ((main_board[i][0] == symbol && main_board[i][1] == symbol && main_board[i][2] == symbol) ||
            (main_board[0][i] == symbol && main_board[1][i] == symbol && main_board[2][i] == symbol)) {
            return true;
        }
    }
    return (main_board[0][0] == symbol && main_board[1][1] == symbol && main_board[2][2] == symbol) ||
           (main_board[2][0] == symbol && main_board[1][1] == symbol && main_board[0][2] == symbol);
}

// Check if game is a draw
template <typename T>
bool Ultimate_X_O_Board<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool Ultimate_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Player Implementation
template <typename T>
Ultimate_X_O_Player<T>::Ultimate_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Ultimate_X_O_Player<T>::getmove(int& x, int& y) {
    cout << "Enter your move (x y): ";
    cin >> x >> y;
}

// Random Player Implementation
template <typename T>
Ultimate_X_O_Random_Player<T>::Ultimate_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void Ultimate_X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 9;
    y = rand() % 9;
}

#endif  //_ULTIMATE_X_O_H