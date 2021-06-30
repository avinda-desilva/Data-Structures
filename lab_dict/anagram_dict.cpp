/**
* @file anagram_dict.cpp
* Implementation of the AnagramDict class.
*
* @author Matt Joras
* @date Winter 2013
*/

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <iostream>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
* Constructs an AnagramDict from a filename with newline-separated
* words.
* @param filename The name of the word list file.
*/
AnagramDict::AnagramDict(const string& filename)
{
  /* Your code goes here! */
  string line;
  ifstream infile (filename);
  vector<string> words;
  vector<string> anagrams;
  string key_word;
  if (infile.is_open()) {
    while (getline(infile, line)) {
      words.push_back(line);
    }
  }
  for (auto& word : words) {
    key_word = word;
    std::sort(key_word.begin(), key_word.end());
    auto key = dict.find(key_word);
    if (key == dict.end()) {
      anagrams.push_back(word);
      dict[key_word] = anagrams;
    } else {
      key->second.push_back(word);
    }
    anagrams.clear();
  }
}

/**
* Constructs an AnagramDict from a vector of words.
* @param words The vector of strings to be used as source words.
*/
AnagramDict::AnagramDict(const vector<string>& words)
{
  /* Your code goes here! */
  string key_word;
  vector<string> anagrams;
  for (auto& word : words) {
    key_word = word;
    std::sort(key_word.begin(), key_word.end());
    auto key = dict.find(key_word);
    if (key == dict.end()) {
      anagrams.push_back(word);
      dict.insert(std::pair<string, vector<string>>(key_word, anagrams));
    } else {
      key->second.push_back(word);
    }
    anagrams.clear();
  }
}

/**
* @param word The word to find anagrams of.
* @return A vector of strings of anagrams of the given word. Empty
* vector returned if no anagrams are found or the word is not in the
* word list.
*/
vector<string> AnagramDict::get_anagrams(const string& word) const
{
  /* Your code goes here! */
  string key_word = word;
  std::sort(key_word.begin(), key_word.end());
  auto key = dict.find(key_word);
  if (key == dict.end()) {
    return vector<string>();
  } else {
    return key->second;
  }
}

/**
* @return A vector of vectors of strings. Each inner vector contains
* the "anagram siblings", i.e. words that are anagrams of one another.
* NOTE: It is impossible to have one of these vectors have less than
* two elements, i.e. words with no anagrams are ommitted.
*/
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
  /* Your code goes here! */
  vector<vector<string>> ret;
  vector<string> anagrams;
  for (auto& key : dict) {
    if (key.second.size() >= 2) {
      ret.push_back(key.second);
    }
  }
  return ret;
}
