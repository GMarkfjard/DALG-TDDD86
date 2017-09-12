#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
const string path = "di.txt";
const char UNREVIELED = '_';

string getLargestGroupKey(const map<string, vector<string>>& m);
string getFamily(string w, string curFam, char guess);

/**
 * @brief main An implementation of the game hangman.
 * @return whether the program executed without errors.
 */
int main()
{
    cout << "Welcome to Hangman." << endl;

    // Load the words into a dictionary where the words are categorized by length
    map<int, vector<string>> dict;
    string input;
    ifstream file(path);
    while(getline(file, input)) {
        vector<string>& vec = dict[input.size()];
        vec.push_back(input);
    }

    int len = 0;
    while (len == 0 || dict.count(len) < 1){
        cout << "Wordlength: ";
        cin >> len;
    }

    int guesses = 0;
    while (guesses < 1){
        cout << "Guess amount: ";
        cin >> guesses;
    }

    bool see_remaining;
    while(true) {
        char ans;
        cout << "Do you want to see the amount of remaining words?[y/n]: ";
        cin >> ans;
        if (ans == 'y') {
            see_remaining = true;
            break;
        }
        else if(ans == 'n') {
            see_remaining = false;
            break;
        }
    }

    // The vector containing the words that matches the length.
    vector<string>& remainingWords = dict[len];

    // The current "word-family" is the family containing all defined words of given length;
    string family(len, UNREVIELED);

    while(true){
        cout << "Guesses left: " << guesses << endl
             << family << endl;

        if (see_remaining)
            cout << "remaining words: " << remainingWords.size() << endl;

        for(auto& w : remainingWords){
            cout << w + " ";
        }
        cout << endl;

        char guess;
        cout << "Guess: ";
        cin >> guess;

        // Place all remaining words into "word-families" based on the current guesses.
        map<string, vector<string>> families;
        for (auto& w : remainingWords) {
            vector<string>& fam = families[getFamily(w, family, guess)];
            fam.push_back(w);
        }

        string prev_fam = family;
        // Find the largest "word-family" and store its words.
        // Implementation of E1: The family will be set to the previous family,
        // i.e no character will be revealed if the amount of remaining guesses is 0
        // And the previous family still contains some words.
        if(guesses > 1 || families[prev_fam].size() == 0){
            family = getLargestGroupKey(families);
        }
        remainingWords = families[family];

        // If the word is finished, the player has won.
        if(family.find(UNREVIELED) == string::npos){
            cout << "Grattis, du vann!" << endl;
            return 0;
        }

        // If the family did not change, the user has given a wrong guess.
        if (family == prev_fam) {
            guesses -= 1;
        }

        if(guesses == 0){
            cout << "Wow you lost" << endl;
            for(auto& w : remainingWords){
                cout << w + " " << endl;
            }
            break;
        }

    }

    return 0;
}


/**
 * @brief getLargestGroupKey Gets the largest groupkey i.e family
 * @param m The map of the current families
 * @return The largest family. E.g "--G-"
 */
string getLargestGroupKey(const map<string, vector<string>>& m) {
    int largest_group_size = 0;
    string key;
    for (auto& group : m) {
        if (group.second.size() > largest_group_size) {
            key = group.first;
            largest_group_size = group.second.size();
        }
    }

    return key;
}

/**
 * @brief getFamily returns the word family for a word based on a given character,
 * for example ada has the word-family "a_a" for the character 'a'.
 * @param w the word for which to get the family
 * @param curFam the current created word-family that the word is placed in
 * @param guess the guess to base the new word-family on.
 * @return the resulting word-family for the word.
 */
string getFamily(string w, string curFam, char guess) {
    string res = w;
    for (int i = 0; i < res.size(); i++) {
        if (curFam[i] == UNREVIELED && res[i] != guess) {
            res[i] = UNREVIELED;
        }
    }

    return res;

}

