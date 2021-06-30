/**
* @file cartalk_puzzle.cpp
* Holds the function which solves a CarTalk puzzler.
*
* @author Matt Joras
* @date Winter 2013
*/

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

/**
* Solves the CarTalk puzzler described here:
* http://www.cartalk.com/content/wordplay-anyone.
* @return A vector of (string, string, string) tuples
* Returns an empty vector if no solutions are found.
* @param d The PronounceDict to be used to solve the puzzle.
* @param word_list_fname The filename of the word list to be used.
*/
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
  const std::string& word_list_fname)
  {
    vector<std::tuple<std::string, std::string, std::string>> ret;
    vector<std::string> pot_words;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    std::string word;
    if (wordsFile.is_open()) {
      /* Reads a line from `wordsFile` into `word` until the file ends. */
      while (getline(wordsFile, word)) {
        if (word.length() == 5) {
          pot_words.push_back(word);
        }
      }
    }
    for (auto& word : pot_words) {
      string word1 = word; string word2 = word;
      word1.erase(0, 1);
      word2.erase(1, 1);
      if (d.homophones(word, word1) && d.homophones(word, word2)) {
        auto answer = make_tuple(word, word1, word2);
        ret.push_back(answer);
      }
    }
    return ret;
  }
