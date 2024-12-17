#ifndef UNTITLED66_4X4_TICTACTOE_H
#define UNTITLED66_4X4_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <bits/stdc++.h>


template <typename T>
class X_OBoard:public Board<T> {
public:
    X_OBoard ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();


    T get_symbol_at(int x, int y); // Function to get the symbol at a specific position
    bool is_empty(int x, int y);

    int get_rows() const { return this->rows; }      // Getter for rows
    int get_columns() const { return this->columns; } // Getter for columns

};

template <typename T>
class X_OPlayer : public Player<T> {
public:
    X_OPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_ORandom_Player : public RandomPlayer<T> {
    X_OBoard<T>* board; // Pointer to the board
public:
    X_ORandom_Player(T symbol, X_OBoard<T>* board);
    void getmove(int& x, int& y);
};







//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
X_OBoard<T>::X_OBoard() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' '; // Default empty cell
        }
    }
    this->n_moves = 0;

    // Set up the initial positions for 'O' and 'X' to match the image
    this->board[0][0] = 'O';
    this->board[0][1] = 'X';
    this->board[0][2] = 'O';
    this->board[0][3] = 'X';

    this->board[3][0] = 'X';
    this->board[3][1] = 'O';
    this->board[3][2] = 'X';
    this->board[3][3] = 'O';
}


template <typename T>
bool X_OBoard<T>::update_board(int x, int y, T mark) {
    int old_x, old_y;

    // Ask the user to specify the position of their token
    cout << "\nEnter the row and column of the token you want to move: ";
    cin >> old_x >> old_y;

    // Validate that the specified token matches the player's mark
    if (old_x < 0 || old_x >= this->rows || old_y < 0 || old_y >= this->columns ||
        this->board[old_x][old_y] != mark) {
        cout << "Invalid selection! There's no " << mark << " token at the specified position.\n";
        return false;
    }

    // Validate the move: check adjacency (horizontal or vertical) and ensure destination is empty
    if ((abs(x - old_x) == 1 && y == old_y) || (abs(y - old_y) == 1 && x == old_x)) {
        if (this->board[x][y] == ' ') { // Check if the destination is empty
            this->board[old_x][old_y] = ' '; // Clear the old position
            this->board[x][y] = mark;        // Move the token to the new position
            return true;
        } else {
            cout << "Invalid move! The destination square is not empty.\n";
        }
    } else {
        cout << "Invalid move! You can only move horizontally or vertically to an adjacent square.\n";
    }

    return false; // Move is invalid
}


template <typename T>
void X_OBoard<T>::display_board() {

    // Display the board
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n--------------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool X_OBoard<T>::is_win() {
    // Check for 3 consecutive tokens horizontally, vertically, or diagonally

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) { // Ensure room for 3 tokens
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j + 1] == this->board[i][j + 2]) {
                return true;
            }
        }
    }

    // Check columns
    for (int i = 0; i <= this->rows - 3; i++) { // Ensure room for 3 tokens
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i + 1][j] == this->board[i + 2][j]) {
                return true;
            }
        }
    }

    // Check diagonals (main diagonals and anti-diagonals)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            // Main diagonal
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j + 2]) {
                return true;
            }
            // Anti-diagonal
            if (this->board[i][j + 2] != ' ' &&
                this->board[i][j + 2] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j]) {
                return true;
            }
        }
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_OBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_OBoard<T>::game_is_over() {
    return is_win();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_OPlayer<T>::X_OPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_OPlayer<T>::getmove(int& x, int& y) {
    cout << "Enter the row and column of the destination (adjacent square): ";
    cin >> x >> y;

}


// Constructor for X_ORandom_Player
template <typename T>
X_ORandom_Player<T>::X_ORandom_Player(T symbol, X_OBoard<T>* board)
        : RandomPlayer<T>(symbol), board(board) {
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator once globally
}


template <typename T>
T X_OBoard<T>::get_symbol_at(int x, int y) {
    // Ensure the position is within bounds (optional check for safety)
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
        return this->board[x][y]; // Access the board to get the symbol
    }
    throw out_of_range("Position is out of bounds"); // Handle invalid positions
}

template <typename T>
bool X_OBoard<T>::is_empty(int x, int y) {
    return get_symbol_at(x, y) == ' '; // Check if the position is empty
}

template <typename T>
void X_ORandom_Player<T>::getmove(int& x, int& y) {
    vector<pair<pair<int, int>, pair<int, int>>> valid_moves;

    // Find all valid moves for the player's tokens
    for (int old_x = 0; old_x < board->get_rows(); old_x++) {
        for (int old_y = 0; old_y < board->get_columns(); old_y++) {
            if (board->get_symbol_at(old_x, old_y) == this->symbol) {
                int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                for (auto& dir : directions) {
                    int new_x = old_x + dir[0];
                    int new_y = old_y + dir[1];
                    if (new_x >= 0 && new_x < board->get_rows() &&
                        new_y >= 0 && new_y < board->get_columns() &&
                        board->is_empty(new_x, new_y)) {
                        valid_moves.push_back({{old_x, old_y}, {new_x, new_y}});
                    }
                }
            }
        }
    }

    // Randomly select a valid move
    if (!valid_moves.empty()) {
        srand(static_cast<unsigned int>(time(0)));
        int random_index = rand() % valid_moves.size();

        // Extract source and destination positions
        int old_x = valid_moves[random_index].first.first;
        int old_y = valid_moves[random_index].first.second;
        x = valid_moves[random_index].second.first;
        y = valid_moves[random_index].second.second;

        // Simulate user input for update_board()
        stringstream simulated_input;
        simulated_input << old_x << " " << old_y; // Simulate source input
        auto old_cin = cin.rdbuf();              // Save original cin buffer
        cin.rdbuf(simulated_input.rdbuf());      // Redirect cin to simulated input

        // Call update_board (will read from the simulated input)
        board->update_board(x, y, this->symbol);

        // Restore original cin
        cin.rdbuf(old_cin);

        cout << "Random Computer Player (" << this->symbol << ") moves token from ("
             << old_x << ", " << old_y << ") to (" << x << ", " << y << ").\n";
        board->display_board();
    } else {
        cout << "Random Computer Player (" << this->symbol << ") has no valid moves!\n";
    }
}








#endif //UNTITLED66_4X4_TICTACTOE_H