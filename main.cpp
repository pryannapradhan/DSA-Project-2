#include <iostream>
#include <cctype>
#include <vector>
#include <fstream>
#include <sstream>
#include "Restaurant.h"
#include "sort_merge.h"
#include "sort_heap.h"
#include <chrono>

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
    float latitude;
    float longitude;
    string genre;
    vector<Restaurant> genreMatches;
    int numRecs;
    float time_duration;

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
    restaurant_data [0].display();
    cout << endl;


    cout << "Please enter your latitude:\n";
    cin >> latitude;

    cout << "Please enter your longitude:\n";
    cin >> longitude;

    for (Restaurant& res : restaurant_data) {
        res.calculateDistance(latitude, longitude);
    }

    cout << "How many restaurants do you want recommended? Please enter a number.\n";

    cin >> numRecs;

    cout << "\nWhat category would you like to sort by? Please enter a number 1-3.\n";
    cout << "1. Restaurant Name\n";
    cout << "2. Rating\n";
    cout << "3. Type\n";

    cin >> answer;

    if (answer == 1) {
        category = "name";
    }
    else if (answer == 2) {
        category = "rating";
    }
    else if (answer == 3) {
        category = "type";
        cout << "Please enter the type of restaurant:\n";
        cin >> genre;

        string cleanedGenre = "";

        for (char c : genre) {
            char lower = tolower(c);
            cleanedGenre += lower;
        }
        for (Restaurant& res : restaurant_data) {
            string cleanedCategory = "";

            for (char c : res.category) {
                char lower = tolower(c);
                cleanedCategory += lower;
            }

            if (cleanedCategory.find(cleanedGenre) != string::npos) {
                genreMatches.push_back(res);
            }
        }

        if (genreMatches.size() == 0) {
            cout << "Our apologies, but we could not find any restaraunts with that category. We will return the closest " << numRecs << " restaurants to you instead." << endl;
        } else if (genreMatches.size() < numRecs) {
            cout << "We could only find " << genreMatches.size() << " restaurants in that category. We will display those, then give you the " << numRecs - genreMatches.size() << " restaurants closest to you." << endl;
        }

    }

    cout << "Sorting by " << category << "!\n\n";


    cout << "Which algorithm would you like to sort by? Please enter 1 or 2.\n";
    cout << "1. Heap Sort\n";
    cout << "2. Merge Sort\n";

    cin >> answer;
    vector<Restaurant> sortedByDistance;

    if (answer == 1) {
        cout << "Calling heap sort\n";

        auto start = chrono::high_resolution_clock::now();

        if (category == "name"){
            heapSort(restaurant_data, restaurant_data.size() - 1, "name");
        } else if (category == "rating") {
            heapSort(restaurant_data, restaurant_data.size() - 1, "rating");
        } else if (category == "distance") {
            heapSort(restaurant_data, restaurant_data.size() - 1, "distance");
        }

        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<float> duration_secs = stop - start;
        time_duration = duration_secs.count();
    }

    else if (answer == 2) {
        cout << "Calling merge sort\n";
        //Name and Rating get sorted based on distance first, then on name and rating so that way it will perserve

        auto start = chrono::high_resolution_clock::now();

        if (category == "name"){
            mergeSort(restaurant_data, 0, restaurant_data.size() - 1, "distance");
            for (int i = 0; i < numRecs; i++) {
                sortedByDistance.push_back(restaurant_data[i]);
            }
            mergeSort(sortedByDistance, 0, sortedByDistance.size() - 1, "name");
        }
        else if (category == "rating") {
            mergeSort(restaurant_data, 0, restaurant_data.size() - 1, "distance");
            for (int i = 0; i < numRecs; i++) {
                sortedByDistance.push_back(restaurant_data[i]);
            }
            mergeSort(sortedByDistance, 0, sortedByDistance.size() - 1, "rating");
        } else if (category == "genre") {
            if (genreMatches.size() >= numRecs) {
                mergeSort(genreMatches, 0, genreMatches.size() - 1, "distance");
            } else if (genreMatches.size() < numRecs) {
                int diff = numRecs - genreMatches.size();
                mergeSort(genreMatches, 0, genreMatches.size() - 1, "distance");
                mergeSort(restaurant_data, 0, restaurant_data.size() - 1, "distance");
                for (int i = 0; i < diff; i++) {
                    genreMatches.push_back(restaurant_data[i]);
                }

            }
        }
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<float> duration_secs = stop - start;
        time_duration = duration_secs.count();
    }


    if (category == "type") {
        for (int i = 0; i < numRecs; i++) {
            genreMatches[i].display();
            cout << endl;
        }
    }

    if (category == "name" || category == "rating") {
        for (int i = 0; i < numRecs; i++) {
            sortedByDistance[i].display();
            cout << endl;
        }
    }

    cout << "Sorting time completed in: " << time_duration << " seconds" << endl;
    return 0;
}