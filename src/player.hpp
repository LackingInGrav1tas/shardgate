#ifndef SHRD_PLA
#define SHRD_PLA


#include "common.hpp"

struct Player {
    int x;
    int y;
    int hp;
    Player() {
        x = X_LEN/2;
        y = Y_LEN/2;
        hp = 2;
    }
};

#endif