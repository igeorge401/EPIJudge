#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// Input: You are given a sorted container A and an integer k.
// Output: Find the index with the first occurrence of k. If it does not exist, return -1.

// Sorted container is an automatic hint at binary search. I like to think of any searching problem in terms of solution spaces. In this case, we have to continue our recursion until the solution space is empty, because we may have other, more optimal instances of k. We'll pass an auxiliary parameter along, initially set to -1, that we update if and when we find an instance of k.

int Searcher(const vector<int>& A, int k, int left_idx, int right_idx, int first_occurrence = -1) {
	// Terminal case: empty solution space.
	if (left_idx > right_idx) return first_occurrence;
	int mid_idx = left_idx + (right_idx-left_idx)/2;
	// Do we have an instance of k?
	first_occurrence = (A[mid_idx] == k) ? mid_idx : first_occurrence;
	// Decision logic: if our pivot index has a value that is greater than or equal to k, any other solutions must be at a lesser index, so only those elements will remain in the solution space, and vice versa.
	return (A[mid_idx] >= k) ? Searcher(A, k, left_idx, mid_idx-1, first_occurrence) : Searcher(A,  k, mid_idx+1, right_idx, first_occurrence);
}

// Time complexity: we shrink our solution space by half with each recursion. O(log(N)).

int SearchFirstOfK(const vector<int>& A, int k) {
  return Searcher(A, k, 0, std::size(A)-1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
