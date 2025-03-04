#include "test_framework/generic_test.h"

#include <limits>

// Input: a double value, x.
// Output: the square root of x, within a tolerance level of episilon.

// Another binary search. This one, I'm doing iteratively, due to the additional complexity...

double SquareRoot(double x) {
  // Edge case: if x is less than 1, we need to set up our interval window differently. The square root will be greater than x. 
  double left_idx = (x < 1.0) ? x : 1.0;
  double right_idx = (x < 1.0) ? 1.0 : x;
  double eps = std::numeric_limits<double>::epsilon();
  // This lambda function will detect whether two doubles are within an epsilon of each other.
  auto cmp = [eps](double x, double y) {
  	double normalized_diff = (y-x)/std::max(std::abs(x), std::abs(y));
  	return (normalized_diff > eps) ? 1 : (normalized_diff < -eps) ? -1 : 0;
  };
  // Keep going until the window is so small, there's less than an eps difference between the left and right bounds.
  while (cmp(left_idx, right_idx) != 0) {
  	double mid_idx = left_idx + 0.5*(right_idx-left_idx);
  	// Three possibilities...
  	if (int result = cmp(mid_idx*mid_idx, x); result == 0) {
  		return mid_idx;
  	} else if (result == 1) {
  		left_idx = mid_idx;
  	} else {
  		right_idx = mid_idx;
  	}
  }
  return left_idx;
}

// Time complexity: O(log(number of iterations == x/eps)). 

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
