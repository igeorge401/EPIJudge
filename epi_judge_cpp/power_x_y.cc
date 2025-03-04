#include "test_framework/generic_test.h"

// Input: a double x and an integer y.
// Output: x^y.

// Recycle the approach from the primitive product problem. x^y is the same as x multiplied by itself y times. We can use y this time as our invariant: each time we encounter a set bit in y, that contributes to however we are calculating this exponential. 

double Power(double x, int y) {
  double exponential = 1.0; 
  // Edge case: y might be negative.
  if (y < 0) {
  	x = 1.0/x;
  	y *= -1;
  }
  while (y) {
  	// Another factor of x...
  	if (y & 1) {
  		exponential *= x;
  	}
  	// No matter what, we multiply x by itself. Each new bit in y is a power of 2 greater than the last. If y is equal to (101), i.e 5, then x^5 = (x^4 * x^1). We have to reflect that with x, just as we left shifted y in the product problem.
  	x *= x;
  	y >>= 1;
  	
  }
  return exponential;
}

// Time complexity: O(N).

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
