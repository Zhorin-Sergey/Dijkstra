#include "Heap.h"

heap::heap(int _size, int _d) {
  size = _size;
  d = _d;
  n = 0;
  arr = new std::pair<int, int> [size];
}

heap::~heap() {
  delete[]arr;
}

void heap::swap(int i, int p) {
  std::pair<int, int> tmp = arr[p];
  arr[p] = arr[i];
  arr[i] = tmp;
}

void heap::up(int i) {
  int p = (i - 1) / d;
  while (p >= 0 && arr[p].second > arr[i].second) {
    swap(i, p);
    i = p;
    p = (i - 1) / d;
  }
}

int heap::min_child(int i) {
  int f = i * d + 1;
  if (f > n - 1)
    return 0;
  int l = n - 1;
  if ((i * d + d) < (n - 1))
    l = i * d + d;
  int minc = f;
  for (int j = f; j <= l; j++)
    if (arr[minc].second > arr[j].second)
      minc = j;
  return minc;
}

void heap::down(int i) {
  int s = min_child(i);
  while (s != 0 && arr[i].second > arr[s].second) {
    swap(s, i);
    i = s;
    s = min_child(i);
  }
}

void heap::hilling() {
  for (int i = n - 1; i >= 0; i--) {
    down(i);
  }
}

void heap::insert(int vennumb, int ddist) {
  if (n == size)
    throw "heap is full";
  arr[n].first = vennumb;
  arr[n].second = ddist;
  up(n);
  n++;
}

std::pair<int, int> heap::deletemin() {
  std::pair<int, int> min = arr[0];
  swap(n - 1, 0);
  n = n - 1;
  hilling();
  return min;
}

void heap::update(int key, int newone) {
  int i = 0;
  while (arr[i].first != key && i <= n)
    i++;
  if (i > n)
    return;
  int old = arr[i].second;
  arr[i].second = newone;
  if (old >= newone)
    up(i);
  if (old < newone)
    down(i);
}

int heap::IsEmpty() {
  return(n == 0);
}
