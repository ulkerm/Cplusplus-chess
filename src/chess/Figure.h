#pragma once

#include <ostream>
#include "Chessman.h"

class King : public Chessman {
public:
    King(char symbol, bool is_white);
    virtual ~King();

    virtual bool can_move(int from_row, int from_col,
                          int to_row, int to_col,
                          const Chessboard &cb) const override;
};

class Queen : public Chessman {
public:
    Queen(char symbol, bool is_white);
    virtual ~Queen();
    virtual bool can_move(int from_row, int from_col,
                          int to_row, int to_col,
                          const Chessboard &cb) const override;
};

class Bishop : public Chessman {
public:
    Bishop(char symbol, bool is_white);
    virtual ~Bishop();
    virtual bool can_move(int from_row, int from_col,
                          int to_row, int to_col,
                          const Chessboard &cb) const override;
};

class Rook : public Chessman {
public:
    Rook(char symbol, bool is_white);
    virtual ~Rook();
    virtual bool can_move(int from_row, int from_col,
                          int to_row, int to_col,
                          const Chessboard &cb) const override;
};

class Knight : public Chessman {
public:
    Knight(char symbol, bool is_white);
    virtual ~Knight();
    virtual bool can_move(int from_row, int from_col,
                          int to_row, int to_col,
                          const Chessboard &cb) const override;
};

class Pawn : public Chessman {
public:
    Pawn(char symbol, bool is_white);
    virtual ~Pawn();
    virtual bool can_move(int from_row, int from_col,
                          int to_row, int to_col,
                          const Chessboard &cb) const override;
};