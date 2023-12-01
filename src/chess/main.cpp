#include <iostream>
#include <string>
#include "Figure.h"
#include "Chessboard.h"

using namespace std;

int main() {
    int row = -1;
    int col = -1;
    int dest_row, dest_col;
    string alt_turn;
    Chessboard board;

    board.show();

    do {
        cout << "Select a piece. Enter the row:" << endl;
        cin >> row;
        cout << "Enter the column:" << endl;
        cin >> col;

        board.select_piece(row,col);
        board.show();
        do {
            cout << "Enter the destination row:" << endl;
            cin >> dest_row;
            cout << "Enter the destination column:" << endl;
            cin >> dest_col;
        } while (!board.can_move_selection_to(dest_row,dest_col));

        board.move_selection_to(dest_row, dest_col);
        board.show();
        alt_turn = board.is_whites_turn() ? "First" : "Second";
        cout << alt_turn << " player turn: " << endl;

    } while (!board.is_game_over());
    cout << " Game over!" << endl;
    return 0;
}