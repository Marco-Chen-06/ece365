#include "graph.h"
#include "heap.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <stack>

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

    // starting vertex is 0 distance
    vertex *start_vertex = static_cast<vertex *>(mapping.getPointer(start));
    start_vertex->dist = 0;

    heap bin_heap(lookup.size());
    for (vertex &v : lookup) {
        bin_heap.insert(v.id, v.dist, &v);
    }

    vertex *cur_vertex;
    while (bin_heap.deleteMin(nullptr, nullptr, &cur_vertex) == 0) {
        if (cur_vertex->dist == max_int) {
            break;
        }
        cur_vertex->known = true;
    }

    for (edge &e : cur_vertex->edges) {
        vertex *neighbor = e.dest;
        if (neighbor->known) {
            continue;
        }
        int new_dist = cur_vertex->dist + e.cost;
        if (new_dist < neighbor->dist) {
            neighbor->dist = new_dist;
            neighbor->prev = cur_vertex;
            // heap decreaseKey
            bin_heap.setKey(neighbor->id, new_dist);
        }
    }
}

// given the output file, display the path
bool graph::displayPath(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: file " << filename << " fialted to open\n";
        return false;
    }

    int max_int = std::numeric_limits<int>::max();

    for (vertex &v : lookup) {
        file << v.id << ": ";
        if (v.dist == max_int) {
            file << "NO PATH\n";
            continue;
        }
        file << v.dist << " [";
        displayPathHelper(file, &v);
        file << "]\n";
    }
    return true;
}

// this function is essentially what I wrote for the iterative
// solution on the midterm
void graph::displayPathHelper(std::ostream &out, vertex *t) {
    std::stack<vertex *> path;
    vertex *v = t;
    path.push(v);
    while (v->prev != nullptr) {
        path.push(v->prev);
        v = v->prev;
    }

    // display everything
    bool first = true;
    while (!path.empty()) {
        vertex *temp = path.top();
        path.pop();
        if (!first) {
            out << ", ";
        }
        out << temp->id;
        first = false;
    }

}
