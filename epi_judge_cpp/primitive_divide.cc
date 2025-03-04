#include "test_framework/generic_test.h"

// Input: two integers, x and y. 
// Output: the quotient, x/y.

// This time, we can use arithmetic operators, so let's do so.

int Divide(int x, int y) {
  int quotient = 0;
  int cur_power = 32;
  // I kept running into problems because I didn't think of casting this until I looked at previous problems in the chapter again.
  unsigned long long y_raised = static_cast<unsigned long long>(y) << 32;
  
  // OK: the basic idea here is that I'm seeing what multiples of y "fit" into x. If we start with the biggest ones that can be reached by bit shifting, then we can reach the answer faster. Keep in mind, this is integer division: only "whole" divisions contribute. 
  while (x >= y) {
  	while (y_raised > x) {
  		y_raised >>= 1;
  		--cur_power;
  	}
  	// Example: Let's divide 12 (1100) by 3 (0011). Note that this is an even division: intuitively, the whole loop should only iterate once. If 3 is left shifted some n amount of times, what is the largest amount that goes into 12? 3 * 2^2 == 12: and 2^2 is 4, the quotient.
  	quotient += (1 << cur_power); 
  	x -= y_raised;
  }
  return quotient;
}

// Time complexity: O(n) since it's all primitive operations inside and outside the hot loop.

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_divide.cc", "primitive_divide.tsv",
                         &Divide, DefaultComparator{}, param_names);
}
