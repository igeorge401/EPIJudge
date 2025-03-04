#include <random>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.

// Well, the above explains the problem well enough, IMO. This is a quickselect implementation.


// Everything between left_idx and right_idx is unsorted, pivot_idx lies somewhere in between. Everything less than whatever is at the pivot_idx should end up to its left, everything greater, to its right. We don't care *how* sorted the vector is: only that everything to the left and right is lesser than and greater than the kth element, respectively.
int PartitionMove(vector<int>& A, int left_idx, int right_idx, int pivot_idx) {
	int pivot_element = A[pivot_idx];
	std::swap(A[pivot_idx], A[right_idx]); // Store this at the end of the interval for safekeeping.
	pivot_idx = left_idx; // We are finding the new pivot index.
	for (int i = left_idx; i < right_idx; ++i) {
		if (A[i] > pivot_element) { // We can safely store this at the beginning of the window, and shrink it.
			std::swap(A[i], A[pivot_idx++]);
		}
	}
	// OK. Now swap back the original pivot element...
	std::swap(A[pivot_idx], A[right_idx]);
	return pivot_idx;
}

int QuickSelect(vector<int>& A, int k, int left_idx, int right_idx) {
    std::random_device rd;  // Seed for the random number engine
    std::mt19937 gen(rd()); 
    while (left_idx <= right_idx) {
    	std::uniform_int_distribution<> distrib(left_idx, right_idx); // Uniform distribution between the current boundaries of the solution space.
    	int pivot_idx = distrib(gen);
    	if (int new_partition_idx = PartitionMove(A, left_idx, right_idx, pivot_idx); new_partition_idx == k-1) {
    		return A[new_partition_idx]; // We've found the kth largest element.
    	} else if (new_partition_idx > k-1) { 
    		right_idx = new_partition_idx;
    	} else {
    		left_idx = new_partition_idx;
    	}
    }
    // Failure. This shouldn't happen, assuming there's no boundary issues.
    return -1;
}

int FindKthLargest(int k, vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  int kth_largest_element = QuickSelect(A, k, 0, std::size(A)-1);
  return kth_largest_element;
}

// Time complexity: O(n^2) worst case, but should be amortized to linear.

int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
