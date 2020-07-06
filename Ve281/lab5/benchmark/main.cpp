#include "binary_heap.h"
#include "fib_heap.h"
#include "unsorted_heap.h"
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>

using namespace std;

class point {
public:
  int x;
  int y;
  int cellweight = 0;
  int pathcost = 0;
  bool reached = false;
  point *predecessor = nullptr;
  point(int x_i, int y_i, int w) : x(x_i), y(y_i), cellweight(w) {}
  bool operator==(const point &p2) const {
    return (x == p2.x && y == p2.y);
  }
};

struct compare {
  bool operator()(const point *a, const point *b) const {
    return (a->pathcost < b->pathcost) ||
           ((a->pathcost == b->pathcost) && (a->x < b->x)) ||
           ((a->pathcost == b->pathcost) && (a->x == b->x) && (a->y < b->y));
  }
};

void trace_back_path(point *p, point *start);

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  bool verbose = false;
  string implement;
  static option long_options[] = {
      {"verbose", no_argument, NULL, 'v'},
      {"implementation", required_argument, NULL, 'i'},
      {0, 0, 0, 0}};
  int opt = 0;
  while ((opt = getopt_long(argc, argv, "vi:", long_options, NULL)) != -1) {
    if (opt == -1)
      break;
    if (opt == 'v') {
      verbose = true;
    } else if (opt == 'i') {
      implement = optarg;
    }
  }
  priority_queue<point *, compare> *PQ;
  if (implement == "BINARY")
    PQ = new binary_heap<point *, compare>();
  else if (implement == "UNSORTED")
    PQ = new unsorted_heap<point *, compare>();
  else if (implement == "FIBONACCI")
    PQ = new fib_heap<point *, compare>();
  else
    return 0;

  int width, height, start_x, start_y, end_x, end_y;
  cin >> width >> height >> start_x >> start_y >> end_x >> end_y;
  vector<vector<point>> grid(height);
  for (int ii = 0; ii < height; ii++) {
    for (int jj = 0; jj < width; jj++) {
      int w;
      cin >> w;
      grid[ii].push_back(point(jj, ii, w));
    }
  }
  point *start = &grid[start_y][start_x];
  point *end = &grid[end_y][end_x];
  start->pathcost = start->cellweight;
  start->reached = true;
  PQ->enqueue(start);
  bool flag = true;
  unsigned step = 0;
  while (!PQ->empty() && flag) {
    cout<<"fk"<<endl;
    point *C = PQ->dequeue_min();
    if (verbose) {
      cout << "Step " << step << endl;
      cout << "Choose cell "
           << "(" << C->x << ", " << C->y << ")"
           << " with accumulated length " << C->pathcost << "." << endl;
    }
    int pos_x[] = {1, 0, -1, 0};
    int pos_y[] = {0, -1, 0, 1};
    for (int ii = 0; ii < 4; ii++) {
      int n_x = C->x + pos_x[ii];
      int n_y = C->y + pos_y[ii];
      if (n_x < 0 || n_x >= width || n_y < 0 || n_y >= height)
        continue;
      point *N = &grid[n_y][n_x];
      cout<<n_x<<n_y<<endl;
      if (N->reached)
        continue;
      N->pathcost = C->pathcost + N->cellweight;
      N->reached = true;
      N->predecessor = C;
      if (*end == *N) {
        if (verbose) {
          cout << "Cell "
               << "(" << N->x << ", " << N->y << ")"
               << " with accumulated length " << N->pathcost
               << " is the ending point." << endl;
        }
        cout << "The shortest path from (" << start->x << ", " << start->y
             << ") to (" << N->x << ", " << N->y << ") is " << N->pathcost
             << "." << endl;
        trace_back_path(N, start);
        flag = false;
        break;
      } else {
        if (verbose) {
          cout << "Cell "
               << "(" << N->x << ", " << N->y << ")"
               << " with accumulated length " << N->pathcost
               << " is added into the queue." << endl;
        }
        PQ->enqueue(N);
      }
    }
    step++;
  }
  delete PQ;
  return 0;
}

void trace_back_path(point *p, point *start) {
  if ((*p == *start)) {
    cout << "Path:" << endl;
    cout << "(" << p->x << ", " << p->y << ")" << endl;
    return;
  }
  trace_back_path(p->predecessor, start);
  cout << "(" << p->x << ", " << p->y << ")" << endl;
}
