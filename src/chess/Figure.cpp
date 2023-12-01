#include "Figure.h"
#include <iostream>

using std::cout;
using std::endl;

King::King(char symbol, bool is_white) : Chessman(symbol, is_white) {
    is_essential_m = true;
    cout << "King " << symbol << endl;
}

King::~King() {

}

bool King::can_move(int from_row, int from_col, int to_row, int to_col, const Chessboard &cb) const {
    if (abs(to_row - from_row) <= 1 && abs(to_col - from_col) <= 1 ) {
        return true;
    }
    return false;
}

Rook::Rook(char symbol, bool is_white) : Chessman(symbol, is_white) {
    is_essential_m = false;
}

Rook::~Rook() {

}

bool Rook::can_move(int from_row, int from_col, int to_row, int to_col, const Chessboard &cb) const {
    if (from_row == to_row) {
        int col_offset = (to_col - from_col > 0) ? 1 : -1;
        for (int check_col = from_col + col_offset; check_col !=  to_col; check_col = check_col + col_offset) {
            if (cb(from_row, check_col) != nullptr) {
                return false;
            }
        }
        return true;
    } else if (to_col == from_col) {
        int row_offset = (to_row - from_row > 0) ? 1 : -1;
        for (int check_row = from_row + row_offset; check_row !=  to_row; check_row = check_row + row_offset) {
            if (cb(check_row, from_col) != nullptr) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Pawn::Pawn(char symbol, bool is_white) : Chessman(symbol, is_white) {
    is_essential_m = false;
}

Pawn::~Pawn() {

}

bool Pawn::can_move(int from_row, int from_col, int to_row, int to_col, const Chessboard &cb) const {
    if (cb(to_row, to_col) == nullptr) {
        if (from_col == to_col) {
            if (get_color() == true) {
                if (to_row == from_row - 1) {
                    return true;
                }
            } else {
                if (to_row == from_row + 1) {
                    return true;
                }
            }
        }
    } else {
        if ((from_col == to_col + 1) || (from_col == to_col - 1)) {
            if (get_color() == true) {
                if (to_row == from_row - 1) return true;
            } else {
                if (to_row == from_row + 1) return true;
            }
        }
    }
    return false;
}

Queen::Queen(char symbol, bool is_white) : Chessman(symbol, is_white) {
    is_essential_m = false;
}

Queen::~Queen() {

}

bool Queen::can_move(int from_row, int from_col, int to_row, int to_col, const Chessboard &cb) const {
    if (from_row == to_row) {
        int col_offset = (to_col - from_col > 0) ? 1 : -1;
        for (int check_col = from_col + col_offset; check_col !=  to_col; check_col = check_col + col_offset) {
            if (cb(from_row, check_col) != nullptr) {
                return false;
            }
        }
        return true;
    } else if (to_col == from_col) {
        int row_offset = (to_row - from_row > 0) ? 1 : -1;
        for (int check_row = from_row + row_offset; check_row !=  to_row; check_row = check_row + row_offset) {
            if (cb(check_row, from_col) != nullptr) {
                return false;
            }
        }
        return true;
    } else if (abs(to_row - from_row) == abs(to_col - from_col)) {
        int row_offset = (to_row - from_row > 0) ? 1 : -1;
        int col_offset = (to_col - from_col > 0) ? 1 : -1;
        int check_row;
        int check_col;
        for (check_row = from_row + row_offset, check_col = from_col + col_offset; check_row !=  to_row;
             check_row = check_row + row_offset, check_col = check_col + col_offset) {
            if (cb(check_row, check_col) != nullptr) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Bishop::Bishop(char symbol, bool is_white) : Chessman(symbol, is_white) {
    is_essential_m = false;
}

Bishop::~Bishop() {

}

bool Bishop::can_move(int from_row, int from_col, int to_row, int to_col, const Chessboard &cb) const {
    if (abs(to_row - from_row) == abs(to_col - from_col)) {
        int row_offset = (to_row - from_row > 0) ? 1 : -1;
        int col_offset = (to_col - from_col > 0) ? 1 : -1;
        int check_row;
        int check_col;
        for (check_row = from_row + row_offset, check_col = from_col + col_offset;
             check_row !=  to_row;
             check_row = check_row + row_offset, check_col = check_col + col_offset)
        {
            if (cb(check_row, check_col) != nullptr) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Knight::Knight(char symbol, bool is_white) : Chessman(symbol, is_white) {
    is_essential_m = false;
}

Knight::~Knight() {

}

bool Knight::can_move(int from_row, int from_col, int to_row, int to_col, const Chessboard &cb) const {
    if ((abs(to_row - from_row) == 2 && abs(to_col - from_col) == 1) || (abs(to_row - from_row) == 1 && abs(to_col - from_col) == 2)) {
        return true;
    }
    return false;
}
