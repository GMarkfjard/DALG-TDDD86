#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
const string path = "/Users/bjorneman/Desktop/TDDD86/labb2/evilhangman/res/di.txt";
const char UNREVIELED = '_';

string getLargestGroupKey(map<a, vector<B> m);
string getFamily(string w, string curFam, char guess);
template <typename T>
T askUser(String message);

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
        len = askUser("Wordlength: ");
    }

    int guesses = 0;
    while (guesses < 1){
        guesses = askUser("Guess amount: ");
    }

    bool see_remaining;
    while(true) {
        char ans = askUser("Do you want to see the amount of remaining words?[y/n]: ");
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

        char guess = askUser("Guess: ");

        // Place all remaining words into "word-families" based on the current guesses.
        map<string, vector<string>> families;
        for (auto& w : remainingWords) {
            vector<string>& fam = families[getFamily(w, family, guess)];
            fam.push_back(w);
        }

        string prev_fam = family;
        // Find the largest "word-family" and store its words.
        family = getLargestGroupKey(families);
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

    }

    return 0;
}

template<typename A>
template<typename B>
string getLargestGroupKey(map<a, vector<B> m) {
    int largest_group_size = 0;
    A key;
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

template <typename T>
T askUser(string msg) {
    T ans;
    cout << msg;
    cin >> ans;
    return ans;
}

