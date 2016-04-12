#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include "Heap.h"
#include <limits.h>
#include <iostream>

void main() {
  std::ifstream in("016");
  int N, M;
  in >> N >> M;
  std::vector<std::list<std::pair<int, int>>> graph(N + 1);  // 0-ый элемент всегда будет пустой
  for (int i = 0; i < M; ++i) {
    int a, b, w;
    in >> a >> b >> w;
    graph[a].push_back(std::make_pair(b, w));
    graph[b].push_back(std::make_pair(a, w));
  }
  int* up = new int[N + 1];
  int* dist = new int[N + 1];
  int* dist1 = new int[N + 1]; // максимальное кол-во дорог из 1 вершины в остальные
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
      if (((dist[j] + i->second) == dist[i->first]) && ((dist1[j] + 1) > dist1[i->first])) {
        up[i->first] = j;
        dist1[i->first] = dist1[j] + 1;
      }
    }
  }
  std::cout << dist[N] << " " << dist1[N] << std::endl;
}
