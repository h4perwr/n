#include <iostream> // standard input/output library
#include <algorithm> // for shuffle function
#include <random> // for random number generator
#include <thread> // for the this_thread::sleep_for method (pauses in the program)
#include <chrono> // to set time intervals

using namespace std;

// Global variables
int rounds = 1; // current round number
int matches = 0; // number of matches (in total you need to find 5 pairs)

int cards[10]; // array of 10 numbers that the game will work with
bool reveal[10] = { false }; // variable for storing the card status (true - guessed, false – not guessed)

// Function of clean the screen
void clearScreen() {
    this_thread::sleep_for(chrono::seconds(1)); // pause after which the screen will be cleaned
    // checking whether the program working on Windows or other OS
#ifdef _WIN32
    system("cls"); // for windows
#else
    system("clear"); // for MacOS or Linux systems
#endif
}

// The function clears the standard input stream.
void clearInputBuffer() {
    cin.clear(); // Reset the error flag if it is set
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer to the end of the line
}

// Function that generates random array and shuffles 
void generateRandomArray() {
    for (int i = 0; i < 5; i++) {
        int j = rand() % 11; // random number from 0 to 10

        cards[i] = j; // first half of the array
        cards[10 - 1 - i] = j; // second half of the array for pairs
    }

    int seed = time(0); // seed for random number generation
    shuffle(begin(cards), end(cards), default_random_engine(seed)); //shuffling numbers
    // random_shuffle(numbers, numbers + 10); // another method for shuffling

}

// Function to display the current state of the array
void showRandomArray() {
    cout << "Here is the array: ";
    for (int i = 0; i < 10; i++) {
        if (reveal[i] == true) {
            cout << cards[i] << " "; // showing the card if reveal == true
        }
        else {
            cout << "? ";  // otherwise show a question mark
        }
    }
    cout << "\n";
}

// Function for initially displaying the array
void startShowArray() {
    cout << "Here is the array: ";
    for (int i = 0; i < 10; i++) {
        cout << cards[i] << " "; // displaying all cards
    }
    cout << "\n";
    this_thread::sleep_for(chrono::seconds(1)); // and pause for memorization
    clearScreen();
}

// Function for displaying the whole array if guessed 
void congratsShowArray() {
    for (int i = 0; i < 10; i++) {
        cout << cards[i] << " "; // displaying all cards
    }
    cout << "\n";
}

// The function from which the program starts working
int main() {
    srand(time(0)); // initializing the random number generator

    generateRandomArray(); // creating an array of maps
    int firstIndex, secondIndex; // the variables of indexes

    startShowArray(); // showing the array at the beginning of the game to memorize

    // Main game loop
    while (matches < 5) { // the game continues until all 5 pairs are found
        cout << "Round: " << rounds << "\n";
        showRandomArray(); // showing the current state of the cards

        // An input of the first index
        cout << "Enter the first index to show: ";
        cin >> firstIndex;
        cout << "The card at index " << firstIndex << " is: " << cards[firstIndex] << "\n" << "\n";

        // An input of the second index
        cout << "Enter the second index to show: ";
        cin >> secondIndex;
        cout << "The card at index " << secondIndex << " is: " << cards[secondIndex] << "\n" << "\n";

        if (cin.fail()) {
            cout << "Invalid input. Try again. You input either a letter or any symbol!" << "\n" << "\n";
            clearScreen();
            clearInputBuffer();
            continue;
        }

        // checking the indexes for correct input
        if (firstIndex < 0 || secondIndex < 0 || firstIndex >= 10 || secondIndex >= 10) {
            cout << "Invalid input. Try again! Indexes are out of range" << "\n" << "\n";
            clearScreen();
            continue;
        }

        if (firstIndex == secondIndex) { // checking whether the indexes are the same
            cout << "You can't enter the same indexes!!!" << "\n" << "\n";
            clearScreen();
        }
        else if (reveal[firstIndex] == true && reveal[secondIndex] == true) { // checking whether the indexes are gueseed
            cout << "You can't enter the guessed indexes!!!" << "\n" << "\n";
            clearScreen();
        }
        else if (cards[firstIndex] == cards[secondIndex]) { // checking for matches
            cout << "Great! The cards are matched! Continue..." << "\n" << "\n";
            reveal[firstIndex] = true;
            reveal[secondIndex] = true;

            rounds++;
            matches++;

            clearScreen();
            clearInputBuffer();
        }
        else {
            cout << "The cards do not match. Try again!" << "\n" << "\n";
            rounds++;
            clearScreen();
        }

        // The pause before next round
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        clearScreen();
    }


    cout << "You Won! \nHere is the whole array you guessed! --> ";
    congratsShowArray();
    return 0;
}
