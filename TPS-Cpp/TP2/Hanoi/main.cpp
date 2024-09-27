#include "Disk.hpp"
#include "Tower.hpp"
#include "Game.hpp"
#include <iostream>

using namespace std;

int main() {
    Game game = Game();
    game.display();
    game.solve(4, game.t1, game.t2, game.t3);
    return 0;
}
