#include "graph.h"

graph::graph() : mapping(1000) {}

graph::vertex *graph::findVertex(const std::string &id) {
    bool found = false;
    vertex *pv = static_cast<vertex *>(mapping.getPointer(id, &found));
    if (found) {
        return pv;
    }
    vertex v;
    lookup.push_back(&v);
    pv = lookup.back();
    pv->id = id;
    lookup.insert(id, pv);
    return pv;
}