#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Tower.hpp"

class Game {
public:
    Game();
    void display() const;
    void solve(int n, Tower& source, Tower& auxiliary, Tower& destination);
    Tower t1;
    Tower t2;
    Tower t3;
};

#endif