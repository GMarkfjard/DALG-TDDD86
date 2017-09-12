#ifndef WORDCHAIN_H
#define WORDCHAIN_H

#endif // WORDCHAIN_H
#include <string>
#include <queue>
#include <stack>

using namespace std;

vector<string> getNeighbours(string w, const vector<string>& dict);
stack<string> wordChain(string w1, string w2, const vector<string>& dict);
