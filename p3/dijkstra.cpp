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
    return -1;
  }

  string start_vertex;
  do {
    // user re-prompted until they enter a valid vertex
    cout <<"Enter name of starting vertex: ";
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
    return -2;
  }
  return 0;
}

