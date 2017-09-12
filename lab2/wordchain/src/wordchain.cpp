#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include "wordchain.h"
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


int main() {
    vector<string> dict;

    fstream file("dictionary.txt");
    string input;
    while(getline(file, input))
        dict.push_back(input);

    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string w1, w2;
    cin >> w1 >> w2;

    stack<string> chain = wordChain(w1, w2, dict);
    string last = chain.top();
    chain.pop();
    for (int i = 0; i < chain.size(); i++) {
        cout << chain.top() << " -> ";
        chain.pop();
    }
    cout << last;
    return 0;
}

stack<string> wordChain(string w1, string w2, const vector<string>& dict) {
    queue<stack<string>> stacks;
    vector<string> checkedWords;
    checkedWords.push_back(w1);
    stacks.push(stack<string>({w1}));
    while (!stacks.empty()) {
        stack<string> partial = stacks.front();
        stacks.pop();

        if (partial.top() == w2)
            return partial;

        else {
            for (auto& n : getNeighbours(partial.top(), dict)) {
                if (find(checkedWords.begin(), checkedWords.end(), n) == checkedWords.end()) {
                    stack<string> newChain(partial);
                    checkedWords.push_back(n);
                    newChain.push(n);
                    stacks.push(newChain);
                    cout << n << endl;
                }
            }
        }

    }

}

vector<string> getNeighbours(string w, const vector<string>& dict) {
    vector<string> neighbours;
    for (int i = 0; i < w.size(); i++){
        for (auto& c: ALPHABET) {
            string w2 = w;
            w2[i] = c;
            if (find(dict.begin(), dict.end(), w2) != dict.end())
                neighbours.push_back(w2);
        }
    }

    return neighbours;

}
