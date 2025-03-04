#include "test_framework/generic_test.h"

// Input: an integer k.
// Output: the largest number with a square value that is less than or equal to k.

// Treat the discrete number line like a sorted vector.

int Searcher(int k, int left_idx, int right_idx) {
	// Terminal case: we've reached an empty solution space with no number that has a square equalling k. So we return the next best thing.
	if (left_idx > right_idx) return left_idx-1;
	long long mid_idx = left_idx + (right_idx-left_idx)/2; // Have to convert this.
	long long squared = mid_idx*mid_idx;
	// Decision logic: short-circuit if equal, the usual if not.
	return (squared == k) ? mid_idx : (squared > k) ? Searcher(k, left_idx, mid_idx-1) : Searcher(k, mid_idx+1, right_idx);
}

// Time complexity: O(log(k)).

int SquareRoot(int k) {
  return Searcher(k, 0, k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
