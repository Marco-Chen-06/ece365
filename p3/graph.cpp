#include "graph.h"
#include "heap.h"
#include <fstream>
#include <iostream>
#include <limits>

graph::graph() : mapping(1000) {}

graph::vertex *graph::findVertex(const std::string &id) {
    bool found = false;
    vertex *pv = static_cast<vertex *>(mapping.getPointer(id, &found));
    if (found) {
        return pv;
    }
    vertex v;
    lookup.push_back(v);
    pv = &lookup.back();
    pv->id = id;
    mapping.insert(id, pv);
    return pv;
}

bool graph::load(const std::string &filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: File" << filename << "failed to open \n";
        return false;
    }

    std::string src, dest;
    int cost;
    while (file >> src >> dest >> cost) {
        vertex *pSrc = findVertex(src);
        vertex *pDest = findVertex(dest);
        edge tempEdge;
        tempEdge.dest = pDest;
        tempEdge.cost = cost;
        pSrc->edges.push_back(tempEdge);
    }
    return true;
}

bool graph::contains(const std::string &id) {
    if (mapping.contains(id)) {
        return true;
    }
    return false;
}

void graph::dijkstra(const std::string &start) {
    // get maximum int value in a type safety way
    // Source: https://stackoverflow.com/questions/1855459/maximum-value-of-int
    int max_int = std::numeric_limits<int>::max();

    // initialize all vertexes with distances to infinity
    for (vertex &v : lookup) {
        v.dist = max_int;
        v.known = false;
        v.prev = nullptr;
    }

    heap bin_heap(lookup.size());

}
