// Author: Jasmine Escandor
// Date: 3.19.2026

#include "sort_heap.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void heapifyUp(vector<Restaurant>& res, int idx, string type){
    //new element is inserted at the bottom of the heap and is compared to its parent 
    //until the heap property is satisfied

    int parent = (idx - 1) / 2; //define parent-child relationship

    //compare elements based on type of sorting
    while (idx > 0) {
        bool willSwap = false;
        //min heap for name and distance, max heap for rating
        if (type == "name") {
            willSwap = res[idx].title < res[parent].title;
        } 
        else if(type == "rating") {
            willSwap = res[idx].rating > res[parent].rating;
        }
        else if (type == "distance") {
            willSwap = res[idx].distance < res[parent].distance;
        }

        if (!willSwap) break;

        // if the child is smaller than the parent, swap and heapify up
        swap(res[idx], res[parent]);
        idx = parent;
        parent = (idx - 1) / 2;
    }
}

void heapifyDown(vector<Restaurant>& res, int idx, int n, string type){
    // restores heap rpoperty after root is swapped with the last element and removed from the heap

    //define parent-child relationships
    int parent = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    //min heap for name and distance, max heap for rating
    if (type == "name") {
        if (left <= n && res[left].title < res[parent].title) {
            parent = left;
        }
        if (right <= n && res[right].title < res[parent].title) {
            parent = right;
        }
    } 
    else if(type == "rating") {
        if (left <= n && res[left].rating > res[parent].rating) {
            parent = left;
        }
        if (right <= n && res[right].rating > res[parent].rating) {
            parent = right;
        }
    }
    else if (type == "distance") {
        if (left <= n && res[left].distance < res[parent].distance) {
            parent = left;
        }
        if (right <= n && res[right].distance < res[parent].distance) {
            parent = right;
        }
    }
    // if the largest is not the root, swap and heapify
    if (parent != idx){
        swap(res[idx], res[parent]);
        heapifyDown(res, parent, n, type);
    }
}

void buildHeap(vector<Restaurant>& res, string type){
    // builds heap by inserting each element and heapifying up
    for (int i = 0; i <= res.size() - 1; i++){
        heapifyUp(res, i, type);
    }
}

void heapSort(vector<Restaurant>& res, int n, string type){
    // builds heap
    buildHeap(res, type);
    
    vector<Restaurant> sorted;
    sorted.reserve(res.size()); // allocate memory

    // sorts elements based on name, rating, or distance
    while (n >= 0){
        sorted.push_back(res[0]);
        swap(res[0], res[n]);
        n--;
        heapifyDown(res, 0, n, type);
    }

    //copy sorted vector back into res
    for (int i = 0; i < sorted.size(); i++) {
        res[i] = sorted[i];
    }
}
