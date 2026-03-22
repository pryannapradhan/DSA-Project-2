// Author: Karen Liang, Pryanna Pradhan, Jasmine Escandor
// Date: 3.18.2026

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
    int proximity;
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

        cout << "How close do you want these restaurants to be (in miles!)?\n";
        cin >> proximity;

        string cleanedGenre = "";

        // Changes the input into all lowercase to make it uniform.
        for (char c : genre) {
            char lower = tolower(c);
            cleanedGenre += lower;
        }

        // Empties genreMatches for multiple runs.
        genreMatches.clear();
        // Makes each restaurants category uniform, then checks if user input is within the category.
        // Then adds the restaurant, if the input is within the category, to genre matches.
        for (Restaurant& res : restaurant_data) {
            string cleanedCategory = "";

            for (char c : res.category) {
                char lower = tolower(c);
                cleanedCategory += lower;
            }

            if (cleanedCategory.find(cleanedGenre) != string::npos && res.distance <= proximity) {
                genreMatches.push_back(res);
            }
        }

        // If genreMatches is empty, will return numRes restaurants closest to the user.
        if (genreMatches.size() == 0) {
            cout << "Our apologies, but we could not find any restaurants with that category " << proximity << " miles away. We will return the closest " << numRecs << " restaurants to you instead." << endl;
        // If genreMatches is less thn numRes, then will return all of genreMatches, plus numRecs - genreMatches.size restaurants sorted by that distance.
        } else if (genreMatches.size() < numRecs) {
            cout << "We could only find " << genreMatches.size() << " restaurants in that category " << proximity << " miles away. We will display those, then give you the " << numRecs - genreMatches.size() << " restaurants closest to you." << endl;
        }

        cout << "size: " << genreMatches.size() << endl;

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
            heapSort(restaurant_data, restaurant_data.size() - 1, "distance");
            for (int i = 0; i < numRecs; i++) {
                sortedByDistance.push_back(restaurant_data[i]);
            }
            heapSort(sortedByDistance, sortedByDistance.size() - 1, "name");
        }
        else if (category == "rating") {
            heapSort(restaurant_data, restaurant_data.size() - 1, "distance");
            for (int i = 0; i < numRecs; i++) {
                sortedByDistance.push_back(restaurant_data[i]);
            }
            heapSort(sortedByDistance, sortedByDistance.size() - 1, "rating");
        } else if (category == "type") {
            if (genreMatches.size() >= numRecs) {
                heapSort(genreMatches, genreMatches.size() - 1, "distance");
            } else if (genreMatches.size() < numRecs) {
                int diff = numRecs - genreMatches.size();
                heapSort(genreMatches, genreMatches.size() - 1, "distance");
                heapSort(restaurant_data, restaurant_data.size() - 1, "distance");
                for (int i = 0; i < diff; i++) {
                    genreMatches.push_back(restaurant_data[i]);
                }

            }
        }

        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<float> duration_secs = stop - start;
        time_duration = duration_secs.count();
    }

    else if (answer == 2) {
        cout << "Calling merge sort\n";
        auto start = chrono::high_resolution_clock::now();

        // Name and Rating get sorted based on distance first, then on name or rating so that way it returns the
        // numRecs closest restaurants sorted based on name or rating.
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
        // If genreMatches is greater than or equal to numRecs, then it will sort based on genreMatches and return the numRecs.
        // If genreMatches is smaller, then sort res based on distance and add numRecs - genreMatches.size() restaurants to genreMatches.
        } else if (category == "type") {
            if (genreMatches.size() >= numRecs) {
                mergeSort(genreMatches, 0, genreMatches.size() - 1, "distance");

            } else if (genreMatches.size() == 0){
                mergeSort(restaurant_data, 0, restaurant_data.size() - 1, "distance");
            } else if (genreMatches.size() < numRecs) {
                int diff = numRecs - genreMatches.size();
                mergeSort(genreMatches, 0, genreMatches.size() - 1, "distance");
                mergeSort(restaurant_data, 0, restaurant_data.size() - 1, "distance");
                for (int i = 0; i < diff; i++) {
                    bool added = false;
                    for (Restaurant& match : genreMatches) {
                        if (match.title == restaurant_data[i].title) {
                            added = true;
                            break;
                        }
                    }

                    if (added == false) {
                        genreMatches.push_back(restaurant_data[i]);
                    }
                }

            }
        }
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<float> duration_secs = stop - start;
        time_duration = duration_secs.count();
    }

    // If sorting by type, print the genreMatches vector.
    if (category == "type") {
        if (genreMatches.size() != 0) {
            for (int i = 0; i < numRecs; i++) {
                genreMatches[i].display();
                cout << endl;
            }
        } else {
            for (int i = 0; i < numRecs; i++) {
                restaurant_data[i].display();
                cout << endl;
            }
        }
    }


    // If sorting by name or rating, print the sortedByDistance vector.
    if (category == "name" || category == "rating") {
        for (int i = 0; i < numRecs; i++) {
            sortedByDistance[i].display();
            cout << endl;
        }
    }

    cout << "Sorting time completed in: " << time_duration << " seconds" << endl;
    return 0;
}