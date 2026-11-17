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

        // dijkstra as a private function in the graph class, as said during lecture
        void dijkstra(const std::string&start);

        // function from midterm to display results
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

        void displayPathHelper(std::ostream &out, vertex *v);
};

#endif