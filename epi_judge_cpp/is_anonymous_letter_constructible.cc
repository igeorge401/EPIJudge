#include <string>

#include "test_framework/generic_test.h"
using std::string;

// Input: Two strings, one a letter

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
  std::unordered_map<char, int> letter_freqs;
  for (const auto& letter : letter_text) {
  	++letter_freqs[letter];
  }
  
  for (const auto& ch : magazine_text) {
  	if (letter_freqs.count(ch) && --letter_freqs[ch] == 0) {
  		letter_freqs.erase(ch);
  		if (std::empty(letter_freqs)) return true;
  	}
  }
  return std::empty(letter_freqs);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
