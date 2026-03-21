// Author: Pryanna Pradhan
// Date: 3.18.2026

#include <iostream>
#include <vector>
#include "sort_merge.h"
using namespace std;

// Takes parameters with restaurants vector, first index, middle index, right index, and the type to sort by.
void merge(vector<Restaurant>& res, int left, int mid, int right, string type) {

    // Creates vectors that store the left side of the vector and the right side.
    vector<Restaurant> leftArr = {};
    vector<Restaurant> rightArr = {};

    int sizeL = mid - left + 1;
    int sizeR = right - mid;

    for (int i = 0; i < sizeL; i++) {
        leftArr.push_back(res[left + i]);
    }

    for (int i = 0; i < sizeR; i++) {
        rightArr.push_back(res[mid + 1 + i]);
    }

    // Establishes indicies for rightArr and leftArr, so we can move through and place sorted values in the res vector.
    int i = 0;
    int j = 0;
    int k = left;

    if (type == "name") {
        // Inserts the entries from each left and right vector based on alphabetical order.
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

        // Inserts the entries from each left and right vector based on rating (numerical) order.
    } else if (type == "rating") {
        while (i < sizeL && j < sizeR) {
            if (leftArr[i].rating >= rightArr[j].rating) {
                res[k] = leftArr[i];
                i++;
            } else if (rightArr[j].rating >= leftArr[i].rating) {
                res[k] = rightArr[j];
                j++;
            }
            k++;
        }

        // Inserts the entries from each left and right vector based on calculated distance (closest is first).
    } else if (type == "distance") {
        while (i < sizeL && j < sizeR) {
            if (leftArr[i].distance <= rightArr[j].distance) {
                res[k] = leftArr[i];
                i++;
            } else if (rightArr[j].distance <= leftArr[i].distance) {
                res[k] = rightArr[j];
                j++;
            }
            k++;
        }
    }

    // Inputs leftover values into the sorted vector.
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

// Takes parameters with restaurants vector, first index, right index, and the type to sort by.
void mergeSort(vector<Restaurant>& res, int left, int right, string type) {

    // Divides the vector recursively in half until only one value is inside vector.
    // Then calls merge, which takes two portions and combines them in the sorted way.
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(res, left, mid, type);
        mergeSort(res, mid + 1, right, type);

        merge(res, left, mid, right, type);
    }
}


