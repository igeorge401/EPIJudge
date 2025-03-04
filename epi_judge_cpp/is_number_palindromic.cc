#include "test_framework/generic_test.h"

// Input: An integer x.
// Output: Detect whether x is palindromic.

// For an integer to be palindromic, the least significant and most significant digits must be the same. If they aren't, we short-circuit and return false. If they are, onto the next pair, and so on and so forth...

bool IsPalindromeNumber(int x) {
  // Edge case: negative number is automatically not palindromic.
  if (x < 0) return false;
  int d = log10(x) + 1; // Number of digits.
  int msd_mask = pow(10, d-1);
  // We're slicing two digits at a time, so we iterate by twos.
  for (int i = 0; i < d; i += 2) {
  	int LSD = (x % 10);
  	int MSD = (x / msd_mask);
  	if (LSD != MSD) return false;
  	// Slice off the outermost digits. Don't forget to alter the msd_mask.
  	x %= msd_mask;
  	x /= 10;
  	msd_mask /= 100;	
  	
  }
  return true;
}

// Time complexity: O(N).


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
