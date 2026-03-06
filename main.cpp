#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// create restaurant struct to read in csv file data
struct Restaurant {
    string title;
    string category;
    float rating;
    string address;
    float latitude;
    float longitude;
};

vector<Restaurant> load_file(string file_name) {
    vector<Restaurant> restaurants;
    ifstream restaurant_file(file_name);
    string line;

    if (!restaurant_file.is_open()) {
        cout << "File could not be opened\n";
        return restaurants;
    }

    getline(restaurant_file, line);

    while (getline(restaurant_file, line)) {
        stringstream ss(line);
        string temp;
        Restaurant rest;

        // note: using "|" as delimiter since the addresses had commas in them
        getline(ss, rest.title, '|');
        getline(ss, rest.category, '|');

        getline(ss, temp, '|');
        rest.rating = stof(temp);

        getline(ss, rest.address, '|');

        getline(ss, temp, '|');
        rest.latitude= stof(temp);
        getline(ss, temp, '|');
        rest.longitude= stof(temp);

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

    // load in data somehow

    cout << "Amazing, let us begin!\n\n";

    cout << "What category would you like to sort by? Please enter a number 1-3.\n";
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
    }

    cout << "Sorting by " << category << "!\n\n";

    cout << "Which algorithm would you like to sort by? Please enter 1 or 2.\n";
    cout << "1. Heap Sort\n";
    cout << "2. Merge Sort\n";

    cin >> answer;

    if (answer == 1) {
        cout << "Calling heap sort\n"; //replace later with heap sort algorithm
    }
    else if (answer == 2) {
        cout << "Calling merge sort\n"; //replace later with merge sort algorithm
    }

    return 0;
}