//
// Created by pryan on 3/18/2026.
//

#ifndef SORT_HEAP_H
#define SORT_HEAP_H
#include <vector>
#include "Restaurant.h"

void heapify(vector<Restaurant>& res, int i, int n, string type);
void heapSort(vector<Restaurant>& res, int n, string type);

#endif //SORT_HEAP_H
