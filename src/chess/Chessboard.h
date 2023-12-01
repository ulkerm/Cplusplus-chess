#pragma once

#include <iostream>
#include <vector>


class Chessman;

class Chessboard {

private:
    std::vector<std::vector<Chessman*>> board;
    bool is_in_range(int row, int col) const;
    int x;
    int y;
    int size;
    bool whites_turn;
public:
    Chessboard(int size = 8);
    ~Chessboard();
    bool is_whites_turn();
    bool is_game_over() const;
    int get_size() const { return size; }
    const Chessman* operator() (int row, int col) const;

    bool can_pass_over(int row, int col) const;
    bool can_land_on(int row, int col, bool is_white) const;

    bool can_select_piece(int row, int col) const;
    bool can_move_selection_to(int row, int col) const;
    bool can_move(int from_row, int from_col,
                  int to_row, int to_col) const;

    void select_piece(int row, int col);
    void move_selection_to(int row, int col);
    void show() const;
};
