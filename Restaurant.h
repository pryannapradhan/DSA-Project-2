// Author: Karen Liang and Pryanna Pradhan
// Date: 3.18.2026

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#ifndef RESTAURANT_H
#define RESTAURANT_H
// Helper function that takes a float in degrees and converts it to radians.
inline float toRad(float deg) {
    float rad = deg * (M_PI / 180);
    return rad;
}

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

    // Function that uses Haversine formula to use coordinates to find the distance between two points.
    // Uses arctan(x) instead of arcsin(x) because it is safer for calculations.
    // Updates the distance attribute of the object in miles, else distance is negative.
    void calculateDistance(float lat, float lon) {
        float latU = toRad(lat);
        float lonU = toRad(lon);
        float latR = toRad(latitude);
        float lonR = toRad(longitude);
        float latD = latR - latU;
        float lonD = lonR - lonU;

        float factorOne = 2 * 3959.0;
        float arg = pow(sin(latD / 2),  2) + (cos(latU) * cos(latR) * pow(sin(lonD / 2), 2));
        float factorTwo = atan2(sqrt(arg), sqrt(1 - arg));

        this->distance = factorOne * factorTwo;
    }
};

#endif //RESTAURANT_H
