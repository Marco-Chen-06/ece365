#include "hash.h"
#include <iostream>

int main() {
    std::cout << "Hi" << std::endl;
    hashTable ht(100);
    int capacity = ht.getCapacity();
    std::cout << capacity;
}