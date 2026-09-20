#include "hash.h"
#include <iostream>
#include <fstream>
#include <cctype>

void print_formatted_output(const std::string &word, bool has_digit, bool long_word, int line_count, hashTable &dict, std::ofstream &out) {
    if (word.empty()) {
        return;
    }
    if (long_word) {
        out << "Long word at line " << line_count << ", starts: " << word << '\n';
        return;
    }
    if (has_digit) {
        return;
    }
    if (!dict.contains(word)) {
        out << "Unknown word at line " << line_count << ": " << word << '\n';
    }
}

int main() {
    // small wordlist is around 25000 words 
    std::ifstream dict("wordlist_small.txt");
    if (!dict.is_open()) {
        std::cerr << "Failed to open dictionary\n";
        return -1;
    }

    std::ofstream out_file("outfile.txt");

    std::string word;
    // assume avg dictionary contains 50k words
    hashTable ht(50000);

    while (std::getline(dict, word)) {
        for (size_t i = 0; i < word.length(); i++) {
              word[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(word[i])));
        }
        ht.insert(word);
    }
    dict.close();

    std::ifstream input_file("lyrics.txt");
    if (!input_file.is_open()) {
        std::cerr << "Failed to open input file\n";
    }

    std::string line;
    int line_count = 1;
    bool has_digit;
    bool long_word;
    char c;
    while (std::getline(input_file, line)) {
        has_digit = false;
        long_word = false;
        for (size_t i = 0; i < line.length(); i++) {
            c = line[i];
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '-') || (c == '\'')) {
                // we haven't reached a separator yet
                if (c >= '0' && c <= '9') {
                    has_digit = true;
                }
                if (word.length() >= 20) {
                    long_word = true;
                } else {
                    word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                }
            } else {
                // we have reached a separator
                print_formatted_output(word, has_digit, long_word, line_count, ht, out_file);
                word = "";
                has_digit = false;
                long_word = false;
            }
        }
        // print accordingly if there is a number in the word or it's too long
        print_formatted_output(word, has_digit, long_word, line_count, ht, out_file);
        word = "";
        has_digit = false;
        long_word = false;
        line_count++;
    }

    std::cout << "done checking contains, no issues\n";

    return 0;

}