// 
// This program implements dijkstra's algorithm, aligning with
// the instructions in the problem set.
//

#include <iostream>
#include <string>
#include <ctime>
#include "graph.h"

using namespace std;


int main()
{
  graph g;
  string filename;

  cout << "Enter name of graph file: ";
  getline(cin, filename);
  if (!g.load(filename)) {
    cerr << "Erorr: could not open " << filename << "\n";
    return -1;
  }

  string start_vertex;
  cout <<"Enter name of starting vertex: ";
  do {
    getline(cin, start_vertex);
  } while (!g.contains(start_vertex));

  clock_t start_time = clock();
  g.dijkstra(start_vertex);
  clock_t end_time = clock();
  double runtime = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << fixed << runtime << "\n";

  cout << "Enter name of output file: ";
  getline(cin, filename);
  if (!g.displayPath(filename)) {
    cerr << "Error: could not open " << filename << "\n";
    return -2;
  }
  return 0;
}

