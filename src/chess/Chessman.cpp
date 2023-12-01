#include "Chessman.h"
#include <iostream>

using std::cout;
using std::endl;

Chessman::Chessman(char symbol, bool is_white) : symbol(symbol), is_white(is_white){
    //cout << "Data(" << symbol << ") constructed" << endl;
}

char Chessman::get_symbol() const {
    return symbol;
}

bool Chessman::get_color() const {
    return is_white;
}
