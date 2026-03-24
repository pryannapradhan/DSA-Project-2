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
    float time_duration = 0.0;

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
        vector<Restaurant> restaurant_file = load_file("150K_Restaurants_Cleaned.csv");

    cout << "Here is a the format of the data:\n";
    restaurant_file [0].display();
    cout << endl;


    cout << "Please enter your latitude:\n";
    cin >> latitude;

    cout << "Please enter your longitude:\n";
    cin >> longitude;

    for (Restaurant& res : restaurant_file) {
        res.calculateDistance(latitude, longitude);
    }

    cout << "How many restaurants do you want recommended? Please enter a number.\n";

    cin >> numRecs;

    bool continueSorting = true;

    while (continueSorting) {
        vector<Restaurant> restaurant_data = restaurant_file; // restore original vector of restaurants
        genreMatches.clear(); // Empties genreMatches for multiple runs

        cout << "\nWhat category would you like to sort by? Please enter a number 1-3.\n";
        cout << "1. Restaurant Name\n";
        cout << "2. Rating\n";
        cout << "3. Type\n";
        cout << "0. End Program\n";

        cin >> answer;

        if (answer == 0) {
            continueSorting = false;
            break;
        }

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
            // if (genreMatches.size() == 0) {
            //     cout << "Our apologies, but we could not find any restaurants with that category " << proximity << " miles away. We will return the closest " << numRecs << " restaurants to you instead." << endl;
            //     // If genreMatches is less thn numRes, then will return all of genreMatches, plus numRecs - genreMatches.size restaurants sorted by that distance.
            // } else if (genreMatches.size() < numRecs) {
            //     cout << "We could only find " << genreMatches.size() << " restaurants in that category " << proximity << " miles away. We will display those, then give you the " << numRecs - genreMatches.size() << " restaurants closest to you." << endl;
            // }


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

            // sort name and rating by distance first, then sort numRecs by name or rating
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
            } 
            // If genreMatches is greater than or equal to numRecs, sort genreMatches based on distance
            // If genreMatches is smaller than numRecs, add the closest restaurants to genreMatches
            // If genreMatches is empty, sort restaurants based on distance
            else if (category == "type") {
                if (genreMatches.size() == 0){
                    heapSort(restaurant_data, restaurant_data.size() - 1, "distance");
                } else if (genreMatches.size() >= numRecs || genreMatches.size() < numRecs) {
                    heapSort(genreMatches, genreMatches.size() - 1, "distance");
                }

            }

            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            time_duration = (float)duration.count();
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
                if (genreMatches.size() == 0) {
                    mergeSort(restaurant_data, 0, restaurant_data.size() - 1, "distance");
                } else if (genreMatches.size() >= numRecs || genreMatches.size() < numRecs) {
                    mergeSort(genreMatches, 0, genreMatches.size() - 1, "distance");                }
            }
            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            time_duration = (float)duration.count();
        }

        // If sorting by type, print the genreMatches vector.
        /*if (category == "type") {
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
        }*/

        if (category == "type") {
            if (!genreMatches.empty()) {
                // print number of restaurants user requests, if not enough, print what we have
                int outputLimit = min(numRecs, (int)genreMatches.size());
                for (int i = 0; i < outputLimit; i++) {
                    genreMatches[i].display();
                    cout << endl;
                }
                cout << "Full genre matches" << endl;
            } else {
                // if nothing matches type, print restaurants ordered by distance
                int outputLimit = min(numRecs, (int)restaurant_data.size());
                for (int i = 0; i < outputLimit; i++) {
                    restaurant_data[i].display();
                    cout << endl;
                }
                cout << "Our apologies, but we could not find any restaurants with that category " << proximity << " miles away. We returned the closest " << numRecs << " restaurants to you instead." << endl;

            }
        }



        // If sorting by name or rating, print the sortedByDistance vector.
        if (category == "name" || category == "rating") {
            for (int i = 0; i < numRecs; i++) {
                sortedByDistance[i].display();
                cout << endl;
            }
        }

        cout << "Sorting time completed in: " << time_duration << " microseconds \n\n";
        cout << "Returning back to category selection... \n";

        sortedByDistance.clear();
    }

    cout << "Thank you for trying out 'ARE U HUNGRY?' BYEEEEEE :)" << endl;
    return 0;
}