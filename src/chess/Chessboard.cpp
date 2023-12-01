#include "Chessboard.h"
#include <iostream>
#include "Figure.h"

using std::cout;
using std::endl;

#define sixth_row_col 6
#define seventh_row_col 7
#define fifth_row_col 5
#define second_row_col 2
#define third_row_col 3
#define fourth_row_col 4

Chessboard::Chessboard(int size) : size(size) {
    this->x = -1;
    this->y = -1;
    whites_turn = true;
    for(unsigned long i = 0; i < (unsigned long)size; i++) {
        std::vector<Chessman*> row;
        for(unsigned long j = 0; j < (unsigned long)size; j++) {
            row.push_back(nullptr);
        }
        board.push_back(row);
    }
    for(unsigned long i = 0; i < (unsigned long)size; i++) {
        board[1][i] = new Pawn('p', false);
        board[sixth_row_col][i] = new Pawn('P', true);
    }
    board[0][0] = new Rook('r', false);
    board[0][seventh_row_col] = new Rook('r', false);
    board[seventh_row_col][0] = new Rook('R', true);
    board[seventh_row_col][seventh_row_col] = new Rook('R', true);
    board[0][1] = new Knight('n', false);
    board[0][sixth_row_col] = new Knight('n', false);
    board[seventh_row_col][1] = new Knight('N', true);
    board[seventh_row_col][sixth_row_col] = new Knight('N', true);
    board[0][second_row_col] = new Bishop('b', false);
    board[0][fifth_row_col] = new Bishop('b', false);
    board[seventh_row_col][second_row_col] = new Bishop('B', true);
    board[seventh_row_col][fifth_row_col] = new Bishop('B', true);
    board[0][third_row_col] = new Queen('q', false);
    board[seventh_row_col][third_row_col] = new Queen('Q', true);
    board[0][fourth_row_col] = new King('k', false);
    board[seventh_row_col][fourth_row_col] = new King('K', true);
    cout << "board constructed" << endl;
}

Chessboard::~Chessboard() {

}

bool Chessboard::is_in_range(int row, int col) const {
    return row >= 0 && col >= 0 && row < this->size && col < this->size;
}

bool Chessboard::is_whites_turn() {
    return whites_turn = whites_turn ? false : true;
}

bool Chessboard::is_game_over() const {
    int k_row, k_col;
    for(unsigned long i = 0; i < (unsigned long)size; i++) {
        for (unsigned long j = 0; j < (unsigned long) size; j++) {
            if (board[i][j] != nullptr && board[i][j]->is_essential() && board[i][j]->get_color() == whites_turn) {
                k_row = i;
                k_col = j;
            }
        }
    }
    for(unsigned long i = 0; i < (unsigned long)size; i++) {
        for (unsigned long j = 0; j < (unsigned long) size; j++) {
            if (board[i][j] != nullptr && board[i][j]->get_color() != whites_turn) {
                if (board[i][j]->can_move(i, j, k_row, k_col, *this))
                    return true;
            }
        }
    }
    return false;
}

void Chessboard::show() const {
    cout << "   ";
    for(unsigned long i = 0; i < (unsigned long)size; i++)
        cout << " " << i << " ";
    cout << endl;

    for(unsigned long i = 0; i < (unsigned long)size; i++) {
        cout << " " << i << " ";
        for (unsigned long j = 0; j < (unsigned long) size; j++) {
            if (board[i][j] == nullptr) {
                cout << " . ";
            } else {
                bool is_active = i == this->x && j == this->y;
                if (is_active) {
                    cout << "(";
                } else cout << " ";
                cout << board[i][j]->get_symbol();
                if (is_active) {
                    cout << ")";
                } else
                    cout << " ";
            }
            if(j == (unsigned long) size - 1)
               cout << endl;
        }
    }
    cout << endl;
}

const Chessman *Chessboard::operator()(int row, int col) const {
    if (this->is_in_range(row, col)) {
        return this->board[row][col];
    } else {
        return nullptr;
    }
}

bool Chessboard::can_pass_over(int row, int col) const {
    if(board[row][col] == nullptr)
        return true;
    return false;
}

bool Chessboard::can_land_on(int row, int col, bool is_white) const {
    bool cur_col = board[row][col]->get_color();
    if(!can_pass_over(row, col)) {
        if(cur_col != is_white)
            return true;
    } else
        return true;
    return false;
}

void Chessboard::move_selection_to(int row, int col) {
     if(board[row][col] != nullptr)
        delete board[row][col];
    board[row][col] = board[this->x][this->y];
    board[this->x][this->y] = nullptr;
    this->x = -1;
    this->y = -1;
}

bool Chessboard::can_select_piece(int row, int col) const {
    if(board[row][col] != nullptr)
        return true;
    return false;
}

bool Chessboard::can_move_selection_to(int row, int col) const {
    if (board[row][col] != nullptr) {
        bool dest_col = board[row][col]->get_color();
        bool src_col = board[x][y]->get_color();
        if (dest_col != src_col)
            return can_move(this->x, this->y, row, col);
        else return false;
    }
    return can_move(this->x, this->y, row, col);
}

bool Chessboard::can_move(int from_row, int from_col, int to_row, int to_col) const {
    if (is_in_range(to_row, to_col)) {
        if (board[from_row][from_col]->can_move(from_row, from_col, to_row, to_col, *this)) {
            return true;
        } else
            cout << "Enter valid coordinates" << endl;
    }
    return false;
}

void Chessboard::select_piece(int row, int col) {
    if (can_select_piece(row, col)) {
        this->x = row;
        this->y = col;
    } else
        cout << "Please enter valid coordinates!" << endl;
}
