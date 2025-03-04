#include "test_framework/generic_test.h"

// Input: an unsigned integer, x, and two indices, i and j.
// Output: x with the ith and jth bits swapped.
// We can immediately return x unchanged if the ith and jth bits are the same. If they aren't, then one must be set and the other unset, meaning they can both be flipped by an XOR with a set bit. We can create a bit mask where the ith and jth bits are 1 and all the others are zero, to preserve all the other bits.

long long SwapBits(long long x, int i, int j) {
  // Ternary statement does the following: isolates and compares the ith and jth bits. If they are different, create a bit mask that has the ith and jth bits set to 1 and the rest to 0, and XOR it with x. 
  return (((x >> i) & 1) == ((x >> j) & 1)) ? x : x ^ (1ULL << i | 1ULL << j);
}

// Time complexity: O(1).

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "i", "j"};
  return GenericTestMain(args, "swap_bits.cc", "swap_bits.tsv", &SwapBits,
                         DefaultComparator{}, param_names);
}
