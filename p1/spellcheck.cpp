#include "hash.h"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("wordlist_small.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::string word;

    hashTable ht(100000);

    while (std::getline(file, word)) {
        ht.insert(word);
        // std::cout << word << std::endl;
    }

    std::cout << "done\n";
    return 0;

}