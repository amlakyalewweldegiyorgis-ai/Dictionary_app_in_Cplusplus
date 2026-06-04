// Developing Dictionary using C++

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

struct Dictionary {
    string word;
    string definition;
};

// Function one _ Add new word on the dictionary:
void addWord(vector<Dictionary>& dict) {
    string word, definition;
    Dictionary newEntry;

    cout << "Enter a word: ";
    cin >> word;
    newEntry.word = word;

    cout << "Enter its definition: ";
    getline(cin >> ws, definition);
    newEntry.definition = definition;

    dict.push_back(newEntry);
    cout << "Word '" << word << "' is added sucessfully!";
}

// Function two _ Display all words in the dictionary:
void readDictionary(const vector<Dictionary>& dict) {
    if (dict.empty()) {
        cout << "The dictionary is empty, please add some words and definition." << endl;
        return;
    }

    cout << "\n ---------------- Existing Words ----------------" << endl;
    for (int i = 0; i < dict.size(); i++) {
        cout << "Word: " << dict[i].word << endl;
        cout << "Definition: " << dict[i].definition << endl;
        cout << "------------------------------------------------" << endl;
    }
}

// Funtion three _ Read from file 
void loadFromFile(string filename, vector<Dictionary>& dict) {
    dict.clear();

    ifstream inputfile(filename);

    if (!inputfile.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    
    cout << "The file '" << filename << "' opened successfully." << endl;
    string word, definition;
    int counter = 0;

    while (getline(inputfile, word) && getline(inputfile, definition)) {
        Dictionary entry;

        entry.word = word;
        entry.definition = definition;
        dict.push_back(entry);  
        counter++;
    }

    inputfile.close();
    cout << counter << " words loaded from file '" << filename << "'." << endl;
    cout << endl;
}

// Funtion four _ Save the words and definition on the file
void saveToFile(string filename, vector<Dictionary>& dict) {

    if (dict.empty()) {
        cout << "The dictionary is empty, have nothing to save." << endl;
        cout << "please, add some word and difinition, thanks.";
        return;
    }

    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "We can't access the file '" << filename << "' provided.";
        return;
    }

    cout << "The file '" << filename << "' opened successfully." << endl;
    int counter = 0; 

    for (int i = 0; i < dict.size(); i++) {
        outFile << dict[i].word << "\n";
        outFile << dict[i].definition << "\n";
        counter++;
    }

    outFile.close();
    cout << counter << " words are save to file '" << filename << "' successfully."; 
    cout << endl;
    cout << endl;
}


// Fun 5 _ find words
void findWord(vector<Dictionary> dict) {
    string word;
    cout << "Enter the word you want to find: ";
    cin >> word;
    for (int i = 0; i < dict.size(); i++) {
        if (word == dict[i].word) {
            cout << "Word: " << dict[i].word << "\n";
            cout << "Definition: " << dict[i].definition << "\n";
            return;
        }
    }

    cout << "The word '"<< word << "' is not found in the dictionary." << endl;
    cout << endl;
}

// function six _ sort the words alphabetically 
void sortWords(vector<Dictionary>& dict) {
    for (int i = 0; i < dict.size() - 1; i++) {
        for (int j = i + 1; j < dict.size(); j++) {
            if (dict[i].word > dict[j].word) {
                swap(dict[i], dict[j]);
            }
        }
    }
}

// function seven _ delete words
void deletWord(vector<Dictionary>& dict) {
    string word;

    cout << "Enter a word to delete: ";
    cin >> word;

    for ( auto it = dict.begin(); it != dict.end(); ++it) {
        if ( it-> word == word) {
            dict.erase(it);
            cout << "The word '" << word << "' deleted successfully."; 
            return;
        }
    }
    cout << "The word '" << word << "' is not found."; 
}

int menu() {
    cout << "---------------------- Wel come to Happy Dictionary ----------------------" << endl;
    cout << "Press:" << endl;
    cout << "1. To see all list on Happy Dictionary" << endl;
    cout << "2. To find word" << endl;
    cout << "3. To add word" << endl;
    cout << "4. To delete word" << endl;
    cout << "5. To Exit" << endl;
    return 0;
}


int main(){

    vector<Dictionary> dictionary;
    string filename = "dictionary.txt";
    loadFromFile(filename, dictionary);

    menu();

    int choice;
    while (true){
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number." << endl;
            continue;
        }
        cout << "----------------------" << endl;

       if (choice == 1){
        readDictionary(dictionary);
       }
       else if (choice == 2){
        findWord(dictionary);
       }
       else if (choice == 3){
        addWord(dictionary);
       }
       else if (choice == 4){
        deletWord(dictionary);
       }
       else if (choice == 5){
        sortWords(dictionary);
        saveToFile(filename, dictionary);
        cout << "Exiting the Dictionary, Thanks for using me." << endl;
        return 5;
       }
       else {
        cout << "Invalid choice, please try again." << endl;
       }
    }

    return 0;
}

