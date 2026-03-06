#include <iostream>
using namespace std;

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