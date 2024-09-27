#include "Game.hpp"

Game::Game() : t1("A"), t2("B"), t3("C") {
    // Call pushDisk without checking for errors for now
    t1.pushDisk(4);
    t1.pushDisk(3);
    t1.pushDisk(2);
    t1.pushDisk(1);
}

void Game::display() const {
    // Implement meaningful display using Tower::display()
}

void Game::solve(int n, Tower& source, Tower& auxiliary, Tower& destination) {
    if (n > 0) {
        solve(n - 1, source, destination, auxiliary);
        Disk disk = source.popDisk();
        destination.pushDisk(disk.getSize());  // Call pushDisk without checking for errors
        display();  // Call display after successful disk movement
        solve(n - 1, auxiliary, source, destination);
    }
}