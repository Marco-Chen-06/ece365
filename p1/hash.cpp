#include "hash.h"
#include <utility>

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
    item.pv = pv;
    int hash_index = hash(key);

    while ((data[hash_index].isOccupied) || data[hash_index].isDeleted) {
        if (data[hash_index].key == key) {
            return 1;
        }
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
    return data[index].pv;
}

int hashTable::setPointer(const std::string &key, void *pv) {
    int index = findPos(key);
    if (index == -1) {
        return 1;
    }
    data[index].pv = pv;
    return 0;
}
bool hashTable::remove(const std::string &key) {
    // as recommended in lecture, I chose not to decrement filled on deletion since 
    // i am doing lazy deletion
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
    unsigned int hash_val = 5381;

    for (unsigned char c : key) {
        hash_val = ((hash_val << 5) + hash_val) + c;
    }
    return hash_val % capacity;

}

int hashTable::findPos(const std::string &key) {
    int hash_index = hash(key);
    while (data[hash_index].isOccupied || data[hash_index].isDeleted) {
        if ((data[hash_index].key == key) && !data[hash_index].isDeleted){
            return hash_index;
        }
        hash_index = (hash_index + 1) % capacity;
    }
    return -1;
}

bool hashTable::rehash() {
    std::vector<hashItem> new_data;
    int new_capacity = getPrime(capacity * 2);
    // if getPrime returns 0, that means no prime number was found
    if (new_capacity == 0) {
        return false;
    }

    try {
        new_data.resize(new_capacity);
    } catch (const std::bad_alloc&) {
        return false;
    }
    capacity = new_capacity;

    int hash_index;
    int new_filled = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].isOccupied && !data[i].isDeleted) {
            hash_index = hash(data[i].key);
            while (new_data[hash_index].isOccupied) {
                hash_index = (hash_index + 1) % capacity;
            }
            new_data[hash_index] = data[i];
            new_filled++;
        }
    }
    filled = new_filled;
    data = std::move(new_data);
    return true;
}

// Return a prime number at least as large as size.
// Uses a precomputed sequence of selected prime numbers.
unsigned int hashTable::getPrime(int size) {
    size_t primes_len = sizeof(primes) / sizeof(primes[0]);
    for (size_t i = 0; i < primes_len; i++) {
        if (size <= primes[i]) {
            return primes[i];
        }
    }
    return 0; // return 0 on error
}