#include "test_framework/generic_test.h"

// Input: an integer x.
// Output: the reversed integer, with signedness preserved.

// Why is this in the bit shifting chapter? The answer to that question is also the answer to this problem.

long long Reverse(int x) {
  long long reversed_x = 0;
  // If x is negative, then each modulus is a negative number: so we'll be *subtracting* from reversed_x, starting at zero, giving us our result. Number lines. They aren't just good for schoolchildren.
  while (x) {
  	reversed_x *= 10;
  	reversed_x += (x % 10); // Least significant digit will come first. And the next iteration will shift it like a right bit shift would previously... :)
  	x /= 10; // Onto the next one.
  }
  return reversed_x;
}

// Time complexity: O(k) for a k-digit number.

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
