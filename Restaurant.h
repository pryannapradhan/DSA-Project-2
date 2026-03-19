#include <iostream>
#include <vector>

using namespace std;
//
// Created by pryan on 3/18/2026.
//

#ifndef RESTAURANT_H
#define RESTAURANT_H

// create restaurant struct to read in csv file data

struct Restaurant {
    string title;
    string category;
    float rating;
    string address;
    float latitude;
    float longitude;
    float distance = -1.0;

    void display() {
        cout << "Title: " << title << endl;
        cout << "Category: " << category << endl;
        cout << "Rating: " << rating << endl;
        cout << "Address: " << address << endl;
        cout << "Latitude: " << latitude << endl;
        cout << "Longitude: " << longitude << endl;
    }
};

#endif //RESTAURANT_H
