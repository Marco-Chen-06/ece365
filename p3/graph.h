#ifndef _GRAPH_H
#define _GRAPH_H

#include <string>
#include <list>
#include <vector>
#include <ostream>
#include "hash.h"

class graph {
    public:
        graph();

        // returns false if file doesn't open
        bool load(const std::string &filename);

        // return true if a vertex with id exists
        bool contains(const std::string &id);

        // run dijkstra starting from start vertex
        void dijkstra(const std::string&start);

        // write vertex distance and path in the format the pset asks for (into the output file)
        // returns false if file fails to open
        bool displayPath(const std::string&filename);

    private:
        class vertex;
        class edge {
            public:
                vertex *dest;
                int cost;
        };
        class vertex {
            public:
                std::string id;
                std::vector<edge> edges;
                int dist;
                bool known;
                vertex *prev;
        };

        std::list<vertex> lookup;
        hashTable mapping;

        vertex *findVertex(const std::string &id);

        void displayPathHelper(std::ostream &out, vertex *t);
};

#endif