#include "test_framework/generic_test.h"

// Input: An unsigned 64 bit integer, x.
// Output: A short value reflecting whether x has an odd or even number of set bits. Aka, a boolean.
// Detection problem: we can recycle the previous approach and use an XOR with 1 to flip between a return value of 1 and 0 with each set bit.

short Parity(unsigned long long x) {
  short is_odd = 0;
  while (x) {
  	is_odd ^= 1; // XOR with one toggles a bit, XOR with zero preserves it. Remember that.
  	x &= (x-1);
  }
  return is_odd;
}

// Time complexity: O(k) for k set bits.

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
