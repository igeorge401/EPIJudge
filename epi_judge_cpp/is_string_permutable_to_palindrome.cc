#include <string>

#include "test_framework/generic_test.h"
using std::string;

// Input: A string s.
// Output: Detect whether it can form a palindrome.

// A palindrome needs to have each character-except a maximum of one for an odd-lettered word-occur an even amount of times. Even. Not two.

bool CanFormPalindrome(const string& s) {
  std::unordered_set<char> odd_freqs;
  for (const auto& ch : s) {
  	if (odd_freqs.count(ch)) odd_freqs.erase(ch);
  	else odd_freqs.emplace(ch);
  }
  return std::size(odd_freqs) <= 1;
}

// O(N).

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
