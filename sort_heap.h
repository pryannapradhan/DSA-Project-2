// Author: Jasmine Escandor
// Date: 3.19.2026

#ifndef SORT_HEAP_H
#define SORT_HEAP_H
#include <vector>
#include "Restaurant.h"

void heapifyUp(vector<Restaurant>& res, int idx, string type);
void heapifyDown(vector<Restaurant>& res, int idx, int n, string type);
void buildHeap(vector<Restaurant>& res, string type);
void heapSort(vector<Restaurant>& res, int n, string type);

#endif //SORT_HEAP_H
