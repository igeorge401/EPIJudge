#include "test_framework/generic_test.h"

// Input: An unsigned integer, x.
// Output: The number of set bits in x.
// Warmup problem: just loop through x, one bit at a time. We can optimize this problem by shifting automatically to the next set bit in x instead.

short CountBits(unsigned int x) {
  short num_bits = 0;
  // Edge case: if x has no set bits, aka it is 0, then this loop is skipped and num_bits returns 0.
  while (x) {
  	++num_bits;
  	x &= (x-1);
  }
  return num_bits;
}

// Time complexity: O(k) for k set bits in x.

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "count_bits.cc", "count_bits.tsv", &CountBits,
                         DefaultComparator{}, param_names);
}
