#include "hash.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <ctime>

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
    std::string dict_file_str;
    std::cout << "Please enter the name of your dictionary file: ";
    std::getline(std::cin, dict_file_str);

    std:: string input_file_str;
    std::cout << "Please enter the name of the file you want to spellcheck: ";
    std::getline(std::cin, input_file_str);

    std::string out_file_str;
    std::cout << "Please enter the name of your output file: ";
    std::getline(std::cin, out_file_str);
    
    // small wordlist is around 25000 words 
    std::ifstream dict_file(dict_file_str);
    if (!dict_file.is_open()) {
        std::cerr << "Failed to open dictionary\n";
        return -1;
    }

    std::ofstream out_file(out_file_str);
    if (!out_file.is_open()) {
        std::cerr << "Failed to open output file\n";
        return -1;
    }

    std::string word;
    // assume avg dictionary contains 50k words (I did test rehashing before submitting)
    hashTable dict(50000);

    auto start_time = std::clock();
    while (std::getline(dict_file, word)) {
        for (size_t i = 0; i < word.length(); i++) {
              word[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(word[i])));
        }
        if (dict.insert(word) == 2) {
            std::cerr << "Rehash failed when inserting into dictionary\n";
            return -1;
        }
    }
    dict_file.close();
    auto end_time = std::clock();
    double cpu_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Time taken to read dictionary: " << cpu_time << " s" << std::endl;

    std::ifstream input_file(input_file_str);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open the file to be spellchecked\n";
        return -1;
    }

    std::string line;
    int line_count = 1;
    start_time = std::clock();
    while (std::getline(input_file, line)) {
        bool has_digit = false;
        bool long_word = false;
        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];
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
                print_formatted_output(word, has_digit, long_word, line_count, dict, out_file);
                word = "";
                has_digit = false;
                long_word = false;
            }
        }
        // print accordingly if there is a number in the word or it's too long
        print_formatted_output(word, has_digit, long_word, line_count, dict, out_file);
        word = "";
        has_digit = false;
        long_word = false;
        line_count++;
    }
    end_time = std::clock();
    cpu_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Time taken to spell check the document: " << cpu_time << " s" << std::endl;
    return 0;
}