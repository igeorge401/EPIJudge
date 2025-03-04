#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

// Input: You are given a vector of words.
// Output: Group the words by anagram and return a 2D vector with each group of anagrams.

// Intro to hash tables: use the sorted word as your key.

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
  std::unordered_map<string, vector<string>> anagram_groups;
  for (const auto& word : dictionary) {
  	std::string sorted_word = word;
  	std::sort(std::begin(sorted_word), std::end(sorted_word));
  	anagram_groups[sorted_word].emplace_back(word);
  }
  
  vector<vector<string>> anagrams;
  for (const auto& [key, group] : anagram_groups) {
  	if (std::size(group) >= 2) {
  		anagrams.emplace_back(group);
  	}
  }
  return anagrams;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
