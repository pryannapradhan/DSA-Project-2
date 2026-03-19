#include <iostream>
#include <vector>
#include "sort_merge.h"
using namespace std;


//
// Author: Pryanna Pradhan
// Date: 3.18.2026
//

void merge(vector<Restaurant>& res, int left, int mid, int right) {
    vector<Restaurant> leftArr = {};
    vector<Restaurant> rightArr = {};

    int sizeL = mid - left + 1;
    int sizeR = right - mid;

    //Creates vectors that store the left side of the vector and the right side.
    for (int i = 0; i < sizeL; i++) {
        leftArr.push_back(res[left + i]);
    }

    for (int i = 0; i < sizeR; i++) {
        rightArr.push_back(res[mid + 1 + i]);
    }

    int i = 0;
    int j = 0;
    int k = left;

    //Inserts the entries from each left and right vector based on alphabetical order.
    while (i < sizeL && j < sizeR) {
        if (leftArr[i].title <= rightArr[j].title) {
            res[k] = leftArr[i];
            i++;
        } else if (rightArr[j].title <= leftArr[i].title) {
            res[k] = rightArr[j];
            j++;
        }
        k++;
    }

    //Inputs leftover values into the sorted vector.
    if (i != sizeL) {
        while (i < sizeL) {
            res[k] = leftArr[i];
            i++;
            k++;
        }
    }
    if (j != sizeR) {
        while (j < sizeR) {
            res[k] = rightArr[j];
            j++;
            k++;
        }
    }

    }


void mergeSort(vector<Restaurant>& res, int left, int right) {

    //Splits the vector up recursively.

    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(res, left, mid);
        mergeSort(res, mid + 1, right);

        merge(res, left, mid, right);


    }
}


