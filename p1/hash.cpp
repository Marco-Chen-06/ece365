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
int hashTable::insert(const std::string &key, void *pv) {
    // 0.5 load factor
    if (filled >= capacity / 2) {
        if (!rehash()) {
            return 2;
        }
    }

    hashItem item;
    item.key = key;
    item.isOccupied = true;
    item.isDeleted = false;
    item.pv = nullptr;
    int hash_index = hash(key);

    while ((data[hash_index].isOccupied) || data[hash_index].isDeleted) {
        hash_index = (hash_index + 1) % capacity;
    }

    data[hash_index] = item;
    filled++;
    return 0;
}

bool hashTable::contains(const std::string &key) {
    if (findPos(key) == -1) {
        return false;
    }
    return true;
}

void *hashTable::getPointer(const std::string &key, bool *b) {
    int index = findPos(key);
    if (index == -1) {
        if (b) {
            *b = false;
        }
        return nullptr;
    }

    if (b) {
        *b = true;
    }
    return &data[index];
}

int hashTable::setPointer(const std::string &key, void *pv) {
    int index = findPos(key);
    if (index == -1) {
        return 1;
    }
    pv = &data[index];
    return 0;
}
bool hashTable::remove(const std::string &key) {
    int index = findPos(key);
    if (index == -1) {
        return false;
    }
    data[index].isDeleted = true;
    return true;
}

// private implementation code

// hash function
int hashTable::hash(const std::string &key) {
    // I chose djb2 hash algorithm because I thought the bit shifting 
    // to multiply by 33 was cool. Implementation followed:
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned int hash = 5381;

    for (unsigned char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;

}

int hashTable::findPos(const std::string &key) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i].key == key) {
            return i;
        }
    }
    return -1;
}

bool hashTable::rehash() {
    std::vector<hashItem> new_data;
    capacity = getPrime(capacity * 2);
    try {
        new_data.resize(capacity); // Request a huge size
    } catch (const std::bad_alloc& e) {
        return false;
    }
    new_data.resize(capacity);

    int hash_index;
    for (int i = 0; i < data.size(); i++) {
        if (data[i].isOccupied) {
            hash_index = hash(data[i].key);
            while (new_data[i].isOccupied) {
                hash_index = (hash_index + 1) % capacity;
            }
            new_data[hash_index] = data[i];
        }
    }
    data = std::move(new_data);
    return true;
}

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