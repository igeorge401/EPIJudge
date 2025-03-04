#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// Input: A k-shifted sorted vector, A.
// Output: The index of the smallest element in the vector. Note that there will always be some smallest element.
// So... we can set up the recursion so that the terminal condition will be when only one element remains: the smallest one.

int Searcher(const vector<int>& A, int left_idx, int right_idx) {
	if (left_idx == right_idx) return left_idx;
	int mid_idx = left_idx + (right_idx-left_idx)/2;
	// Decision logic: our comparison is going to be between the current rightmost index and the pivot index to see *whether or not we are in the shifted part of the vector*. That's what we need to know to see what elements to flush from the solution space. Note that if A[mid_idx] < A[right_idx], i.e, we are in the unshifted part of the vector, that the pivot index can still be the answer and must remain in the solution space.
	return (A[mid_idx] > A[right_idx]) ? Searcher(A, mid_idx+1, right_idx) : Searcher(A, left_idx, mid_idx);
}

// Time complexity: O(log(N)).

int SearchSmallest(const vector<int>& A) {
  return Searcher(A, 0, std::size(A)-1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
