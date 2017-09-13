#ifndef EVILHANGMAN_H
#define EVILHANGMAN_H
#include <string>
#include <vector>
#include <map>
#endif // EVILHANGMAN_H

using namespace std;




/**
 * @brief iterates over the families and finds the family with most unique unreviealed characters.
 * @param families the "word-families"
 * @param guess the current guess given by the user
 * @return the tag of the "word-family" with the most unique unrevealed characters.
 */
string getMostUniqueFam(const map<string, vector<string>>& families, char guess);

/**
 * @brief getUniqueUnrevealed iterates over the words of the family and counts the amount of unique unrevealed characters of all words,
 * besides the ones that matches the given guess.
 * @param fam the family to check
 * @param famTag the current "word-family" that the word is placed in.
 * @param guess the guess given by the user.
 * @return the amount of unique unrevealed characters (besides the ones that matches the given guess)
 */
int getUniqueUnrevealed(const vector<string>& fam, string famTag, char guess);

/**
 * @brief getLargestGroupKey Gets the largest groupkey i.e family
 * @param m The map of the current families
 * @return The largest family. E.g "--G-"
 */
string getLargestGroupKey(const map<string, vector<string>>& m);


/**
 * @brief getFamily returns the word family for a word based on a given character,
 * for example ada has the word-family "a_a" for the character 'a'.
 * @param w the word for which to get the family
 * @param curFam the current created word-family that the word is placed in
 * @param guess the guess to base the new word-family on.
 * @return the resulting word-family for the word.
 */
string getFamily(string w, string curFam, char guess);
