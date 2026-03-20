#include "sort_heap.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void heapify(vector<Restaurant>& res, int i, int n, string type){
    int largest = i; // root is the largest element in a max heap
    
    //define parent-child relationships
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //compare elements based on type of sorting
    if (type == "name") {
        if (left <= n && res[left].title < res[largest].title) {
            largest = left;
        }
        if (right <= n && res[right].title < res[largest].title) {
            largest = right;
        }
    } else if (type == "rating") {
        if (left <= n && res[left].rating >= res[largest].rating) {
            largest = left;
        }
        if (right <= n && res[right].rating >= res[largest].rating) {
            largest = right;
        }
    } else if (type == "distance") {
        if (left <= n && res[left].distance <= res[largest].distance) {
            largest = left;
        }
        if (right <= n && res[right].distance <= res[largest].distance) {
            largest = right;
        }
    }
    // if the largest is not the root, swap and heapify
    if (largest != i) {
        swap(res[i], res[largest]);
        heapify(res, largest, n, type);
    }
}

void heapSort(vector<Restaurant>& res, int n, string type){
    // builds max heap
    for (int i = n / 2; i >= 0; i--) {
        heapify(res, i, n, type);
    }
    //rearranges heap
    for (int i = n; i > 0; i--) {
        swap(res[0], res[i]);
        heapify(res, 0, i, type);
    }
}
