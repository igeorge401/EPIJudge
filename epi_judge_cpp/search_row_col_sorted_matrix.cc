#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// Input: A 2D vector A filled with sorted integer values, and an integer x.
// Output: A boolean value denoting whether x exists in A.

// Just think of this as binary search, only we are ruling out whole columns or rows based on whether our pivot index is lesser or greater than x. And of course, we short-circuit if we find x.

bool Searcher(const vector<vector<int>>& A, int x, int row_id, int col_id) {
	// Terminal case: empty solution space-we are out of bounds. x isn't present.
	if (row_id >= std::size(A) || col_id < 0) return false;
	else return (A[row_id][col_id] == x) ? x : (A[row_id][col_id] > x) ? Searcher(A, x, row_id, col_id-1) : Searcher(A, x, row_id+1, col_id);
}

bool MatrixSearch(const vector<vector<int>>& A, int x) {
  // Top row, rightmost entry gives you the maximum information you need when you compare it to x.
  return Searcher(A, x, 0, std::size(A[0])-1);
}

// Time complexity: O(m+n) for m rows and n columns.

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "x"};
  return GenericTestMain(args, "search_row_col_sorted_matrix.cc",
                         "search_row_col_sorted_matrix.tsv", &MatrixSearch,
                         DefaultComparator{}, param_names);
}
