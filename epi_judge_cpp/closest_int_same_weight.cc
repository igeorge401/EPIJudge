#include "test_framework/generic_test.h"

// Input: An unsigned 64 bit integer x.
// Output: The closest integer that has the same number of set bits as x.

// This problem requires a bit of thinking: how do you minimize the difference when swapping bits? The answer has two parts to it:
	// a) You want to swap adjacent bits. The difference between 2^k and 2^k+1 for any value of k will be smaller than any 2^k and 2^k+2 for the same k. You can do the math yourself.
	// b) You'll want to focus on the least significant bits first and short-circuit immediately when you find two adjacent bits with different parities.

unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  for (int i = 1; i < 64; ++i) {
  	int prev_bit_idx = i-1;
  	// Are the bits different? First time this happens: that's our answer.
  	if (((x >> i) & 1) != ((x >> prev_bit_idx) & 1)) {
  		x ^= (1ULL << i | 1ULL << prev_bit_idx);
  		break;
  	}
  }
  return x;
}

// Time complexity: O(N) worst case.

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
