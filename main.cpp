#include <iostream>
#include "BoardGame_Classes.h"
#include "Pyramic_tic-tac-toe.h"
#include "Connect_Four.h"
#include "Word_tic-tac-toe.h"
#include "Numerical_TicTacToe.h"
#include "4x4_tictactoe.h"
#include "SUS_GAME.h"
#include "Ultimate_X_O.h"
#include "5x5X_O.h"
#include "MisereTicTacToe.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>


using namespace std;

// Function to display the available numbers for a player
void display_available_numbers(const vector<int>& numbers) {
    cout << "Available numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
}
int PyramicTicTacToe(){
    int choice;
    Player<char>* players[2];
    X_O_Board<char>* B = new X_O_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new X_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    return 0;
}
int connectFour(){
    int choice;
    Player<char>* players[2];
    ConnectFourBoard<char>* B = new ConnectFourBoard<char>();

    string playerXName, player2Name;

    cout << " ** Welcome to FCAI Connect 4 Board Game ** \n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new ConnectFourPlayer<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new ConnectFourRandomPlayer<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new ConnectFourPlayer<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new ConnectFourRandomPlayer<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> connect4game(B, players);
    connect4game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
int FivexFiveTicTacToe(){
    int choice;
    Player<char>* players[2];
    X_O_Board_5x5<char>* B = new X_O_Board_5x5<char>();
    string player1Name, player2Name;

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new X_O_Player_5x5<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player_5x5<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new X_O_Player_5x5<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player_5x5<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
int WordTicTacToee(){
    cout << "Enter Player1 name: ";
    string player1_name;
    cin >> player1_name;
    cout << "Choose Player1 type:\n1. Human\n2. Random Computer\n";
    int player1_type;
    cin >> player1_type;

    cout << "Enter Player2 name: ";
    string player2_name;
    cin >> player2_name;
    cout << "Choose Player2 type:\n1. Human\n2. Random Computer\n";
    int player2_type;
    cin >> player2_type;

    WordTicTacToeBoard<char> board;

    // Using smart pointers for polymorphic behavior
    unique_ptr<Player<char>> player1;
    unique_ptr<Player<char>> player2;

    // Create player1 based on the selected type
    if (player1_type == 1) {
        player1 = make_unique<WordTicTacToePlayer<char>>(player1_name, 'X', &board);
    } else if (player1_type == 2) {
        player1 = make_unique<WordTicTacToeRandom_Player<char>>('X', &board);
    } else {
        cout << "Invalid option for Player1 type. Exiting.\n";
        return 1;
    }

    // Create player2 based on the selected type
    if (player2_type == 1) {
        player2 = make_unique<WordTicTacToePlayer<char>>(player2_name, 'O', &board);
    } else if (player2_type == 2) {
        player2 = make_unique<WordTicTacToeRandom_Player<char>>('O', &board);
    } else {
        cout << "Invalid option for Player2 type. Exiting.\n";
        return 1;
    }

    bool player1_turn = true;

    while (!board.game_is_over()) {
        board.display_board();
        int x, y;

        if (player1_turn) {
            cout << "\n" << player1_name << "'s turn:";
            player1->getmove(x, y);
        } else {
            cout << "\n" << player2_name << "'s turn:";
            player2->getmove(x, y);
        }

        if (board.is_win()) {
            board.display_board();
            cout << "\nCongratulations! " << (player1_turn ? player1_name : player2_name) << " is the winner!";

            return 0;
        }


        player1_turn = !player1_turn; // Switch turns
    }

    if (board.is_draw()) {
        board.display_board();
        cout << "\nIt's a draw!\n";
    }
    return 0;
}
void NumericalTicTacToe(){
    cout << "Welcome to Numerical Tic-Tac-Toe!" << endl;
    cout << "Rules: Players take turns placing numbers on the grid." << endl;
    cout << "Odd numbers are for Player 1, and even numbers are for Player 2." << endl;
    cout << "The goal is to get a row, column, or diagonal to sum up to 15!" << endl;
    cout << endl;

    // Create the board
    Numerical_Board<int> board;

    // Create the players
    string player1Name, player2Name;
    char choice1, choice2;

    // Set up Player 1 (Odd numbers)
    cout << "Enter Player 1 name (Odd numbers): ";
    cin >> player1Name;

    cout << "Choose Player 1 type (Human or Computer)? (h/c): ";
    cin >> choice1;
    Numerical_Player<int>* player1;
    if (choice1 == 'h' || choice1 == 'H') {
        player1 = new Numerical_Player<int>(player1Name, 1); // Odd numbers for Player 1 (Human)
    } else {
        player1 = reinterpret_cast<Numerical_Player<int> *>(new Numerical_Random_Player<int>(1)); // Random Computer Player 1
        cout << "Player 1 will be a computer." << endl;
        srand(static_cast<unsigned int>(time(0))); // Seed random number generator
    }

    // Set up Player 2 (Even numbers)
    cout << "Enter Player 2 name (Even numbers): ";
    cin >> player2Name;

    cout << "Choose Player 2 type (Human or Computer)? (h/c): ";
    cin >> choice2;
    Numerical_Player<int>* player2;
    if (choice2 == 'h' || choice2 == 'H') {
        player2 = new Numerical_Player<int>(player2Name, 2); // Even numbers for Player 2 (Human)
    } else {
        player2 = reinterpret_cast<Numerical_Player<int> *>(new Numerical_Random_Player<int>(2)); // Random Computer Player 2
        cout << "Player 2 will be a computer." << endl;
    }

    // Assign the board to players
    player1->setBoard(&board);
    player2->setBoard(&board);

    // Available numbers for players
    vector<int> player1Numbers = {1, 3, 5, 7, 9};
    vector<int> player2Numbers = {2, 4, 6, 8};

    // Game loop
    board.display_board();
    while (!board.game_is_over()) {
        // Player 1's turn
        cout << "\n" << player1Name << "'s Turn (Odd numbers):" << endl;
        display_available_numbers(player1Numbers);

        int x, y, number;
        bool validMove = false;
        do {
            cout << "Enter the row and column (x y) of an empty cell: ";
            cin >> x >> y;
            cout << "Choose a number from your available numbers: ";
            cin >> number;

            if (!board.is_cell_empty(x, y)) {
                cout << "Error: Cell (" << x << ", " << y << ") is already occupied!" << endl;
            } else if (find(player1Numbers.begin(), player1Numbers.end(), number) == player1Numbers.end()) {
                cout << "Error: Number " << number << " is not available!" << endl;
            } else {
                validMove = board.update_board(x, y, number);
            }
        } while (!validMove);

        player1Numbers.erase(find(player1Numbers.begin(), player1Numbers.end(), number));
        board.display_board();

        if (board.is_win()) {
            cout << player1Name << " wins!" << endl;
            break;
        }

        if (board.is_draw()) {
            cout << "It's a draw!" << endl;
            break;
        }

        // Player 2's turn
        cout << "\n" << player2Name << "'s Turn (Even numbers):" << endl;
        display_available_numbers(player2Numbers);

        validMove = false;
        if (choice2 == 'h' || choice2 == 'H') {
            do {
                cout << "Enter the row and column (x y) of an empty cell: ";
                cin >> x >> y;
                cout << "Choose a number from your available numbers: ";
                cin >> number;

                if (!board.is_cell_empty(x, y)) {
                    cout << "Error: Cell (" << x << ", " << y << ") is already occupied!" << endl;
                } else if (find(player2Numbers.begin(), player2Numbers.end(), number) == player2Numbers.end()) {
                    cout << "Error: Number " << number << " is not available!" << endl;
                } else {
                    validMove = board.update_board(x, y, number);
                }
            } while (!validMove);
            player2Numbers.erase(find(player2Numbers.begin(), player2Numbers.end(), number));
        } else {
            while (!validMove) {
                x = rand() % 3;
                y = rand() % 3;
                for (int num : player2Numbers) {
                    if (board.update_board(x, y, num)) {
                        cout << "Computer placed " << num << " at (" << x << ", " << y << ")" << endl;
                        player2Numbers.erase(find(player2Numbers.begin(), player2Numbers.end(), num));
                        validMove = true;
                        break;
                    }
                }
            }
        }

        board.display_board();

        if (board.is_win()) {
            cout << player2Name << " wins!" << endl;
            break;
        }

        if (board.is_draw()) {
            cout << "It's a draw!" << endl;
            break;
        }
    }

    delete player1;
    delete player2;
}
int MisereTicTacToe(){
    int choice;
    Player<char>* players[2];
    MisereTicTacToeBoard<char>* board = new MisereTicTacToeBoard<char>();
    string player1Name, player2Name;

    cout << "Welcome to Misere Tic Tac Toe!\n";
    cout << "=== RULES ===\n";
    cout << "1. Players take turns placing their marks (X or O) on the board\n";
    cout << "2. The goal is to AVOID getting three marks in a row\n";
    cout << "3. If you make three in a row (horizontally, vertically, or diagonally), YOU LOSE!\n";
    cout << "4. If the board fills up with no three in a row, it's a draw\n\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new MisereTicTacToePlayer<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new MisereTicTacToeRandomPlayer<char>('X');
            players[0]->setBoard(board);
            break;

        default:
            cout << "Invalid choice. Exiting game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new MisereTicTacToePlayer<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new MisereTicTacToeRandomPlayer<char>('O');
            players[1]->setBoard(board);
            break;

        default:
            cout << "Invalid choice. Exiting game.\n";
            return 1;
    }

    GameManager<char> game(board, players);
    game.run();

    // Cleanup
    delete board;
    delete players[0];
    delete players[1];

    return 0;
}
int FourxFourTicTacToe(){
    int choice;
    Player<char>* players[2];
    X_OBoard<char>* B = new X_OBoard<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new X_OPlayer<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_ORandom_Player<char>('X', B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new X_OPlayer<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_ORandom_Player<char>('O', B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Game loop
    int currentPlayer = 0;
    while (!B->game_is_over()) {
        int x, y;
        B->display_board();

        cout << players[currentPlayer]->getname() << "'s turn ("
             << players[currentPlayer]->getsymbol() << "):\n";

        // Get the move
        players[currentPlayer]->getmove(x, y);

        // Update the board only if the player is human
        if (dynamic_cast<X_OPlayer<char>*>(players[currentPlayer])) {
            if (!B->update_board(x, y, players[currentPlayer]->getsymbol())) {
                cout << "Invalid move! Try again.\n";
                continue; // Retry the same player's turn
            }
        }

        // Switch to the next player
        currentPlayer = (currentPlayer + 1) % 2;
    }

    // Display final board
    B->display_board();

    // Check the result
    if (B->is_win()) {
        cout << "Congratulations! "
             << players[(currentPlayer + 1) % 2]->getname()
             << " wins the game!\n";
    } else if (B->is_draw()) {
        cout << "The game is a draw!\n";
    }

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
int UltimateTicTacToe(){
    int choice;
    Player<char>* players[2];
    Ultimate_X_O_Board<char>* B = new Ultimate_X_O_Board<char>();

    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Ultimate_X_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Ultimate_X_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Ultimate_X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Ultimate_X_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> Ultimate_x_o_game(B, players);
    Ultimate_x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
int SUS(){
    int choice;
    Player<char>* players[2]; // Array to hold the two players
    Sus_Board<char>* B = new Sus_Board<char>(); // Create the board
    string player1Name, player2Name;

    cout << "Welcome to FCAI SUS Game. :)\n";

    // Set up Player 1
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new Sus_Player<char>(player1Name, 'S'); // Human player
            break;
        case 2:
            players[0] = new Sus_Random_Player<char>('S'); // Random computer player
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up Player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new Sus_Player<char>(player2Name, 'U'); // Human player
            break;
        case 2:
            players[1] = new Sus_Random_Player<char>('U'); // Random computer player
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> sus_game(B, players);
    sus_game.run();

    // Clean up
    delete B; // Delete the board
    for (int i = 0; i < 2; ++i) {
        delete players[i]; // Delete the players
    }

    return 0;
}



int main() {
    while(true){
        cout << "\nwelcome to tic tac toa games :)\nchoose the game you want to play\n"
             <<"1- Pyramic Tic-Tac-Toe\n"
               "2- connect Four \n"
               "3- 5 x 5 Tic Tac Toe\n"
               "4- Word Tic-tac-toe\n"
               "5- Numerical Tic-Tac-Toe\n"
               "6- Misere Tic Tac Toe\n"
               "7- 4x4 Tic-Tac-Toe\n"
               "8- Ultimate Tic Tac Toe\n"
               "9- SUS word Tic Tac Toe\n"
               "10- Exit\n"
               "choose a number please: ";
        int c;
        cin >> c;
        if(c == 1){
            PyramicTicTacToe();
        }
        else if(c == 2){
            connectFour();
        }
        else if(c == 3){
            FivexFiveTicTacToe();
        }
        else if(c == 4){
            WordTicTacToee();
        }
        else if(c == 5){
            NumericalTicTacToe();
        }
        else if(c == 6){
            MisereTicTacToe();
        }
        else if(c == 7){
            FourxFourTicTacToe();
        }
        else if(c == 8){
            UltimateTicTacToe();
        }
        else if(c == 9){
            SUS();
        }
        else if(c == 10){
            cout << "thanks for using our program :)\n";
            break;
        }else{
            cout << "invalid input! please enter a valid number\n";
            continue;
        }
    }


    return 0;
}



