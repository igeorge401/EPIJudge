#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

// Input: a sorted container A with unique elements.
// Output: An entry equal to its index, if it exists, -1 if it doesn't. Note that since the elements are all unique, there can only be at most one solution.

// Binary search. This time, since the solution is unique, we can short circuit immediately if we find it, and if we hit the base case, we'll know we've failed.

int Searcher(const vector<int>& A, int left_idx, int right_idx) {
	// Terminal case: if we never short-circuit before this, we've failed.
	if (left_idx > right_idx) return -1;
	int mid_idx = left_idx + (right_idx-left_idx)/2;
	// Decision logic: First, check to see if we have an answer. If we don't, then what can we eliminate from the solution space? Here is wisdom-since the elements are unique, if the element is greater than its index, any element at a higher index will be as well, and vice versa.
	return (A[mid_idx] == mid_idx) ? mid_idx : (A[mid_idx] > mid_idx) ? Searcher(A, left_idx, mid_idx-1) : Searcher(A, mid_idx+1, right_idx);
}

// Time complexity: O(log(N)).

int SearchEntryEqualToItsIndex(const vector<int>& A) {
  return Searcher(A, 0, std::size(A)-1);
}
void SearchEntryEqualToItsIndexWrapper(TimedExecutor& executor,
                                       const vector<int>& A) {
  int result = executor.Run([&] { return SearchEntryEqualToItsIndex(A); });

  if (result != -1) {
    if (A[result] != result) {
      throw TestFailure("Entry does not equal to its index");
    }
  } else {
    for (int i = 0; i < A.size(); ++i) {
      if (A[i] == i) {
        throw TestFailure("There are entries which equal to its index");
      }
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "search_entry_equal_to_index.cc", "search_entry_equal_to_index.tsv",
      &SearchEntryEqualToItsIndexWrapper, DefaultComparator{}, param_names);
}
