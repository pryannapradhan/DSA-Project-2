#include "sort_heap.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void heapifyMin(vector<Restaurant>& res, int i, int n, string type){
    int smallest = i; // root is the smallest element in a min heap
    
    //define parent-child relationships
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //compare elements based on type of sorting
    if (type == "name") {
        if (left <= n && res[left].title < res[smallest].title) {
            smallest = left;
        }
        if (right <= n && res[right].title < res[smallest].title) {
            smallest = right;
        }
    } 
    
    else if (type == "distance") {
        if (left <= n && res[left].distance < res[smallest].distance) {
            smallest = left;
        }
        if (right <= n && res[right].distance < res[smallest].distance) {
            smallest = right;
        }
    }
    // if the smallest is not the root, swap and heapify
    if (smallest != i) {
        swap(res[i], res[smallest]);
        heapifyMin(res, smallest, n, type);
    }
}

void heapifyMax(vector<Restaurant>& res, int i, int n, string type){
    int largest = i; // root is the largest element in a max heap

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (type == "rating") {
        if (left <= n && res[left].rating > res[largest].rating) {
            largest = left;
        }
        if (right <= n && res[right].rating > res[largest].rating) {
            largest = right;
        }
    } 
    // if the largest is not the root, swap and heapify
    if (largest != i){
        swap(res[i], res[largest]);
        heapifyMax(res, largest, n, type);
    }
}

void heapSort(vector<Restaurant>& res, int n, string type){
    // builds heap
    for (int i = n / 2; i >= 0; i--) {
        if (type == "rating") {
            heapifyMax(res, i, n, type);
        } else {
            heapifyMin(res, i, n, type);
        }
    }
    //rearranges heap
    for (int i = n; i > 0; i--) {
        swap(res[0], res[i]);
        if (type == "rating") {
            heapifyMax(res, i-1, n, type);
        } else {
            heapifyMin(res, i-1, n, type);
        }
    }
}
