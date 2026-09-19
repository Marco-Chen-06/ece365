#include "hash.h"

// prime numbers taken from http://my.core.com/~katiemarie10/prime/prime.htm
static const unsigned int primes[] = {
    11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421,
    12853, 25717, 51437, 102877, 205759, 411527, 823117,
    1646237, 3292489, 6584983
};

// constructor implementation
hashTable::hashTable(int size) {
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);
}

// public functions
int hashTable::getCapacity() {
    return capacity;
}

// private implementation code

// Return a prime number at least as large as size.
// Uses a precomputed sequence of selected prime numbers.
unsigned int hashTable::getPrime(int size) {
    int primes_len = sizeof(primes) / sizeof(primes[0]);
    for (int i = 0; i < primes_len; i++) {
        if (size < primes[i]) {
            return primes[i];
        }
    }
    return 0; // return 0 on error
}