#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "evilhangman.h"

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
const string path = "di.txt";
const char UNREVIELED = '_';

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
    string family;
    set<char> guessedLetters;

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
    family = string(len, UNREVIELED);

    while(true){
        map<string, vector<string>> families;
        string prev_fam;
        char guess;
        string output;
        cout << "\n" << endl;

        if (see_remaining)
            cout << "remaining words: "
                 << remainingWords.size() << endl;

        cout << "Guessed letters: ";
        for(auto& c : guessedLetters){
            cout << c;
        }

        cout << endl;

        cout << "Guesses left: " << guesses << endl
             << family << endl;

        cout << "Guess: ";
        cin >> guess;
        guessedLetters.insert(guess);

        // Place all remaining words into "word-families" based on the current guesses.
        for (auto& w : remainingWords) {
            vector<string>& fam = families[getFamily(w, family, guess)];
            fam.push_back(w);
        }

        prev_fam = family;

        // E1 addition
        if(guesses > 1 || families[prev_fam].size() == 0){
            //family = getLargestGroupKey(families); Org. impl.
            family = getMostUniqueFam(families, guess); // E2 Addition
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
            cout << endl << "Wow you lost!" << endl
                 << "The word was: " + remainingWords[0] << endl;
            break;
        }
    }
    return 0;
}

//E2 addition
string getMostUniqueFam(const map<string, vector<string>>& families, char guess) {
    string tagMostUniqFam;
    int mostUnique = -1;

    for (auto& fam: families) {
        int curUnique = getUniqueUnrevealed(fam.second, fam.first, guess);
        if (curUnique > mostUnique) {
            mostUnique = curUnique;
            tagMostUniqFam = fam.first;
        }
    }
    return tagMostUniqFam;

}

//E2 addition
int getUniqueUnrevealed(const vector<string>& fam, string famTag, char guess) {
    set<char> uniqUnrev;

    for (int i = 0; i < famTag.size(); i++) {
        if (famTag[i] == UNREVIELED) {
            for (auto& w: fam) {
                if (w[i] != guess)
                    uniqUnrev.insert(w[i]);
            }
        }
    }
    return uniqUnrev.size();

}


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


string getFamily(string w, string curFam, char guess) {
    string res = w;

    for (int i = 0; i < res.size(); i++) {
        if (curFam[i] == UNREVIELED && res[i] != guess) {
            res[i] = UNREVIELED;
        }
    }
    return res;
}
