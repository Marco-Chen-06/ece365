#include "hash.h"
#include <iostream>
#include <fstream>

int main() {
    // small wordlist is around 25000 words 
    std::ifstream file("wordlist_small.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::string word;

    // cause as much rehashing as possible
    hashTable ht(0);

    while (std::getline(file, word)) {
        ht.insert(word);
        // std::cout << word << std::endl;
    }

    std::cout << "done inserting\n";

    // traverse small wordlist again and check contains() for every key
    file.clear();
    file.seekg(0, std::ios::beg);
    while (std::getline(file, word)) {
        if (ht.contains(word) == false) {
            std::cout << "error\n";
            return -1;
        }
    }

    std::cout << "done checking contains, no issues\n";

    return 0;

}