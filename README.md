# R U HUNGRY (DSA P2) 🍕🍔🍜

### <u> Repository Contents </u>
* `data_cleaning.txt`: Contains the Python code we used in PyCharm to clean the original Kaggle dataset of 380K restaurants
* `Restaurant_Cleaned.csv`:  Cleaned dataset containing ~130K restaurants and their metadata, output from the data cleaning python script
* `main.cpp`: Reads in csv file, sets up terminal interface, and integrates the heap sort/merge sort code
* `Restaurant.h`: Defines the `Restaurant` struct (How each row of the csv file is represented)
    * **Attributes**: `string title`, `string category`, `float rating`, `string address`, `float latitude`, `float longitude`, `float distance`
    * `display()`: Manages how the restaurant data is displayed in the terminal
    * `calculateDistance()`: Calculates the distance between two points (the user and the Restaurant)
* `sort_heap.h/cpp`: Implementation of heap sort
* `sort_merge.h/.cpp`: Implementation of merge sort

### <u> Usage Instructions </u>
1. **Begin Program:** Press the play button to compile the files and run the script in the terminal
2. **Preliminary Inputs**: You will be prompted to set specific variables that will remain constant throughout your session:
   1. Current latitude and longitude
   2. Number of recommendations you would like to receive
4. **Beginning of Loop**: For each iteration, you may choose a unique combination of:
   1. **Category:** sort results by Name, Rating, or Type
      1. If type is chosen, you will be asked to enter a category
   2. **Sorting Algorithm**: select Heap Sort or Merge Sort
7. **Output:** The program will then display your list of personalize restaurant recommendations and the time it took to sort.
   1. If there are not enough restaurants that meet the user's criteria, the program will display what it has.
8. **Exit:** The program will return to the category selection. Enter `0` here whenever you would like to exit the program.

> **Thank you for trying out R U HUNGRY! We hope you got some yummy food recs :)**