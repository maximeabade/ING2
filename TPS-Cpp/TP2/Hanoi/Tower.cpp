#include "Tower.hpp"

Tower::Tower(const std::string& name) : name(name) {}

void Tower::pushDisk(int size) {
    //on veut rajouter un disk en tete de liste
}

Disk Tower::popDisk() {
    Disk disk = disks.back();
    disks.pop_back();
    return disk;
}


