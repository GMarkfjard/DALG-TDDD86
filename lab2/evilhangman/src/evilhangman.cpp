#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
const string path = "/Users/bjorneman/Desktop/TDDD86/labb2/evilhangman/res/di.txt";
const char UNREVIELED = '_';

string getFamily(string w, string curFam, char guess);

int main() {
    cout << "Welcome to Hangman." << endl;
    map<int, vector<string>> dict;
    string input;
    ifstream file(path);

    while(getline(file, input)) {
        vector<string>& vec = dict[input.size()];
        vec.push_back(input);
    }

    int len = 0;
    while (len == 0 || dict.count(len) < 1){
        cout << "wordlength: ";
        cin >> len;
    }

    int guesses = 0;
    while (guesses < 1){
        cout << "guesses: ";
        cin >> guesses;
    }

    bool see_remaining;
    while(true) {
        char ans;
        cout << "See remaining words? [y/n]: ";
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

    vector<string>& words = dict[len];
    string family(len, UNREVIELED);

    while(true){
        for (auto& w : words) {
            cout << w << ", ";
        }
        cout << endl;

        cout << "Guesses left: " << guesses << endl
             << family << endl;
        if (see_remaining)
            cout << "remaining words: " << words.size() << endl;

        char guess;
        cout << "guess: ";
        cin >> guess;

        map<string, vector<string>> families;
        for (auto& w : words) {
            vector<string>& fam = families[getFamily(w, family, guess)];
            fam.push_back(w);
        }

        string prev_fam = family;
        int largest_fam_size = 0;
        for (auto& fam : families) {
            if (fam.second.size() > largest_fam_size) {
                family = fam.first;
                cout << fam.first << endl;
                largest_fam_size = fam.second.size();
            }
        }

        words = families[family];

        if(family.find(UNREVIELED) == string::npos){
            cout << "Grattis, du vann!" << endl;
            return 0;
        }

        if (family == prev_fam) {
            guesses -= 1;
        }


    }

    return 0;
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

