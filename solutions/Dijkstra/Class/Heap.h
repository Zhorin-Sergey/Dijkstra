#ifndef SOLUTIONS_DIJKSTRA_CLASS_HEAP_H_
#define SOLUTIONS_DIJKSTRA_CLASS_HEAP_H_

#include <vector>

class heap {
private:
  int size;
  int d;
  std::pair<int, int>* arr;
  int n;
public:
  int min_child(int i);
  void up(int i);
  void down(int i);
  heap(int _size, int _d);
  ~heap();
  void hilling();
  void insert(int, int);
  std::pair<int, int> deletemin();
  void swap(int i, int p);
  void update(int, int);
  int IsEmpty();
};

#endif  //  SOLUTIONS_DIJKSTRA_CLASS_HEAP_H_
