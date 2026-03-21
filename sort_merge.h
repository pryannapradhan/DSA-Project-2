// Author: Pryanna Pradhan
// Date: 3.18.2026

#include <vector>
#include "Restaurant.h"

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

void merge(vector<Restaurant>& res, int left, int mid, int right, string type);
void mergeSort(vector<Restaurant>& res, int left, int right, string type);

#endif //SORT_MERGE_H
