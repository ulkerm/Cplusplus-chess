#pragma once

#include <iostream>
#include <string>
#include "Chessboard.h"

class Chessboard;

class Chessman {

private:
    char symbol;
    bool is_white;
protected:
    bool is_essential_m;
public:
    Chessman(char symbol, bool is_white);
    virtual ~Chessman() {}

    char get_symbol() const;
    bool get_color() const;

    virtual bool is_essential() const { return is_essential_m; };
    virtual bool can_move(
            int from_row, int from_col,
            int to_row, int to_col,
            const Chessboard &cb) const = 0;
};