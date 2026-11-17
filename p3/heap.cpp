#include "heap.h"

heap::heap(int capacity) : capacity(capacity), currentSize(0), mapping(capacity * 2) {
    data.resize(capacity + 1);
}

int heap::insert(const std::string &id, int key, void *pv) {
    // heap is full
    if (currentSize >= capacity) {
        return 1;
    }
    if (mapping.insert(id, &data[currentSize + 1]) == 1) {
        return 2;
    }
    currentSize++;
    data[currentSize].id = id;
    data[currentSize].key = key;
    data[currentSize].pData = pv;
    percolateUp(currentSize);
    return 0;
}

int heap::setKey(const std::string &id, int key) {
    bool ret;
    node *pn = static_cast<node *>(mapping.getPointer(id, &ret));
    if (!ret) {
        return 1;
    }

    int pos = getPos(pn);
    // if key is the same as before then nothing changes
    if (key == data[pos].key) {
        return 0;
    }
    int old_key = data[pos].key;
    data[pos].key = key;

    if (key < old_key) {
        // if key got smaller then percolate up toward the top
        percolateUp(pos);
    } else { 
        // otherwise percolate down
        percolateDown(pos);
    }
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (currentSize == 0) {
        return 1;
    }

    if (pId) {
        *pId = data[1].id;
    }
    if (pKey) {
        *pKey = data[1].key;
    }
    if (ppData) {
        *(static_cast<void **>(ppData)) = data[1].pData;
    }
    mapping.remove(data[1].id);

    data[1] = data[currentSize];
    currentSize--;
    percolateDown(1);
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {
    bool ret;
    node *pn = static_cast<node *>(mapping.getPointer(id, &ret));
    if (!ret) {
        return 1;
    }
    int pos = getPos(pn);

    if (pKey) {
        *pKey = data[pos].key;
    }
    if (ppData) {
        *(static_cast<void **>(ppData)) = data[pos].pData;
    }

    mapping.remove(id);
    int removed_key = data[pos].key;
    data[pos] = data[currentSize];
    currentSize--;

    // if we removed the last node then we dont have to do anything
    if (pos > currentSize) {
        return 0;
    }
    if (data[pos].key < removed_key) {
        percolateUp(pos);
    } else {
        percolateDown(pos);
    }
    return 0;
}

void heap::percolateUp(int posCur) {
    node temp_node = data[posCur];
    while (posCur > 1 && (temp_node.key < data[posCur / 2].key)) {
        data[posCur] = data[posCur / 2];
        mapping.setPointer(data[posCur].id, &data[posCur]);
        posCur /= 2;
    }
    data[posCur] = temp_node;
    mapping.setPointer(data[posCur].id, &data[posCur]);
 }

void heap::percolateDown(int posCur) {
    node temp_node = data[posCur];
    while (posCur * 2 <= currentSize) {  
        int child = posCur * 2;
        if ((child + 1 <= currentSize) && (data[child + 1].key < data[child].key)) {
            child++;                  
        }
        if (data[child].key >= temp_node.key) {
            break;  
        }
        data[posCur] = data[child];
        mapping.setPointer(data[posCur].id, &data[posCur]);
        posCur = child;
    }
    data[posCur] = temp_node;
    mapping.setPointer(data[posCur].id, &data[posCur]);
}

// identical to the useHeap_bits.pdf example and in class
int heap::getPos(node *pn) {
    return pn - &data[0];
}

