#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Restaurant.h"
#include "sort_merge.h"
//#include "sort_heap.h"

using namespace std;



vector<Restaurant> load_file(string file_name) {
    vector<Restaurant> restaurants;
    ifstream restaurant_file(file_name);
    string line;

    if (!restaurant_file.is_open()) {
        cout << "File could not be opened\n";
        return restaurants;
    }

    getline(restaurant_file, line);

    int line_count = 0;
    while (getline(restaurant_file, line)) {
        line_count++;
        stringstream ss(line);
        string temp;
        Restaurant rest;

        // note: using "\t" as delimiter since the addresses had commas in them
        getline(ss, rest.title, '\t');
        getline(ss, rest.category, '\t');

        getline(ss, temp, '\t');
        rest.rating = stof(temp);

        getline(ss, rest.address, '\t');

        getline(ss, temp, '\t');
        rest.latitude = stof(temp);
        getline(ss, temp, '\t');
        rest.longitude = stof(temp);

        restaurants.push_back(rest);
    }

    restaurant_file.close();
    return restaurants;
}


int main() {
    int answer;
    string category;
    int numRecs;
    float latitude;
    float longitude;

    cout << "-----------------------\n";
    cout << "     ARE U HUNGRY?     \n";
    cout << "-----------------------\n";

    cout << "Are you ready to start? Please enter 1 or 2.\n";
    cout << "1. yes\n";
    cout << "2. no\n";

    cin >> answer;

    if (answer == 2) {
        cout << "No worries! See you next time!\n";
        return 0;
    }

    cout << "Amazing, let us begin!\n\n";

    // load in data somehow
        vector<Restaurant> restaurant_data = load_file("150K_Restaurants_Cleaned.csv");

    cout << "Here is a the format of the data:\n";
    for (int i = 0; i < 3; i++) {
        restaurant_data [i].display();
        cout << endl;
    }

    cout << "\nWhat category would you like to sort by? Please enter a number 1-3.\n";
    cout << "1. Restaurant Name\n";
    cout << "2. Rating\n";
    cout << "3. Distance\n";

    cin >> answer;

    if (answer == 1) {
        category = "name";
    }
    else if (answer == 2) category = "rating";
    else if (answer == 3) {
        category = "distance";

        cout << "Please enter your latitude:\n";
        cin >> latitude;

        cout << "Please enter your longitude:\n";
        cin >> longitude;

        for (Restaurant& res : restaurant_data) {
            res.calculateDistance(latitude, longitude);
        }
    }

    cout << "Sorting by " << category << "!\n\n";

    cout << "\nHow many restaurants do you want recommended? Please enter a number.\n";

    cin >> numRecs;


    cout << "Which algorithm would you like to sort by? Please enter 1 or 2.\n";
    cout << "1. Heap Sort\n";
    cout << "2. Merge Sort\n";

    cin >> answer;

    if (answer == 1) {
        cout << "Calling heap sort\n"; //replace later with heap sort algorithm
    }
    else if (answer == 2) {
        cout << "Calling merge sort\n";
        if (category == "name"){
            mergeSort(restaurant_data, 0, restaurant_data.size() - 1, "name");
        } else if (category == "rating") {
            mergeSort(restaurant_data, 0, restaurant_data.size() - 1, "rating");
        } else if (category == "distance") {
            mergeSort(restaurant_data, 0, restaurant_data.size() - 1, "distance");
        }
    }


    for (int i = 0; i < numRecs; i++) {
        restaurant_data [i].display();
        cout << endl;
    }

    return 0;
}