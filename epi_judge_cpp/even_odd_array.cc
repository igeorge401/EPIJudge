#include <set>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

// Input: An array of integers.
// Output: The array of integers with all even numbers coming before the odd ones.
// Classic partition problem.

void EvenOdd(vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  int cur_even_idx = 0;
  for (int i = 0; i < std::size(A); ++i) {
	if (A[i] % 2 == 0) {
		std::swap(A[i], A[cur_even_idx++]);
	}
  }
}

// O(N).

void EvenOddWrapper(TimedExecutor& executor, vector<int> A) {
  std::multiset<int> before(begin(A), end(A));

  executor.Run([&] { EvenOdd(&A); });

  bool in_odd = false;
  for (int a : A) {
    if (a % 2 == 0) {
      if (in_odd) {
        throw TestFailure("Even elements appear in odd part");
      }
    } else {
      in_odd = true;
    }
  }

  std::multiset<int> after(begin(A), end(A));
  if (before != after) {
    throw TestFailure("Elements mismatch");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "even_odd_array.cc", "even_odd_array.tsv",
                         &EvenOddWrapper, DefaultComparator{}, param_names);
}
