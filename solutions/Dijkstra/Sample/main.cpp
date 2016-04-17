#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include "Heap.h"
#include <limits.h>
#include <iostream>

void main(int argc, char *argv[]) {
  int N, M;
  if (argv[1] != 0) {
    std::ifstream in(argv[1]);
    in >> N >> M;
  } else {
    N = 3;
    M = 3;
  }
  std::vector<std::list<std::pair<int, int>>> graph(N + 1);
  if (argv[1] != 0) {
    std::ifstream in(argv[1]);
    in >> N >> M;
    for (int i = 0; i < M; ++i) {
      int a, b, w;
      in >> a >> b >> w;
      graph[a].push_back(std::make_pair(b, w));
      graph[b].push_back(std::make_pair(a, w));
    }
  } else {
    graph[1].push_back(std::make_pair(2, 1));
    graph[2].push_back(std::make_pair(1, 1));
    graph[1].push_back(std::make_pair(3, 2));
    graph[3].push_back(std::make_pair(2, 2));
    graph[2].push_back(std::make_pair(3, 1));
    graph[3].push_back(std::make_pair(2, 1));
  }
  int* up = new int[N + 1];
  int* dist = new int[N + 1];
  int* dist1 = new int[N + 1];
  heap och(N, 2);
  dist[1] = 0;
  dist1[1] = 0;
  up[1] = 0;
  och.insert(1, 0);
  for (int k = 2; k < N + 1; k++) {
    up[k] = 0;
    dist[k] = INT_MAX;
    dist1[k] = 0;
    och.insert(k, INT_MAX);
  }
  while (!och.IsEmpty()) {
    std::pair<int, int> tmp = och.deletemin();
    int j = tmp.first;
    for (auto i = graph[j].begin(); i != graph[j].end(); ++i) {
      if ((dist[j] + i->second) < dist[i->first]) {
        dist[i->first] = dist[j] + i->second;
        up[i->first] = j;
        dist1[i->first] = dist1[j] + 1;
        och.update(i->first, dist[j] + i->second);
      }
      if (((dist[j] + i->second) == dist[i->first])
      && ((dist1[j] + 1) > dist1[i->first])) {
        up[i->first] = j;
        dist1[i->first] = dist1[j] + 1;
      }
    }
  }
  std::cout << dist[N] << " " << dist1[N] << std::endl;
}
