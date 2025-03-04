#include "test_framework/generic_test.h"

// Second insight: add two bits together. What do you get? Four possibilities. Two 0s: 0. Two 1s: 0. One each: 1. Aka, XOR. For three out of four cases, that's all you need to know. If you have two 1s-something that can be detected with an AND-you need to carry over a 1.

unsigned long long Add(unsigned long long direct_product, unsigned long long carry_bits) {
	// For pedogogical purposes, the iterative version.
	
	/*
	auto direct_product = (product_so_far ^ y); // In the iterative version, I gave the input parameters these names.
	auto carry_bits = (product_so_far & y);
	// If we don't have anything to carry over, we are done. If we do...
	while (carry_bits) {
		carry_bits <<= 1;
		auto old_product = direct_product;
		direct_product ^= carry_bits;
		carry_bits &= old_product; // We have to use the value of the product before we apply XOR. Look at why recursion is better for this...
		
	}
	return direct_product;
	*/
	//Much more elegantly stated... 
	return (!carry_bits) ? direct_product : Add(direct_product ^ carry_bits, ((direct_product & carry_bits) << 1));
}

// Input: two unsigned 64 bit integers, x and y.
// Output: the product. Done only using primitive operators.
// OK... this one is fun. First insight: a multiplication is a succession of additions. Take care of the addition operation first.


unsigned long long Multiply(unsigned long long x, unsigned long long y) {
  unsigned long long product = 0;
  // Third insight: we now have an operation that adds two unsigned longs. An invariant could be looping through one of the inputs and applying that operation any time we have a set bit representing a power of two: it'll be a subproduct of the time.
  while (x) {
  	if (x & 1) {
  		// We'll be looping or recursing through y.
  		product = Add(product, y);
  	}
  	// Final insight: what about the power of two? How do we keep track of that as we right shift through x, diminishing its value? Simple: by reminding ourselves that a left shift is equivalent to multiplying by two. Left shift y. It'll keep all the bits, but multiply each by two. 
  	x >>= 1;
  	y <<= 1;
  }
  return product;
}

// Time complexity: O(n^2).

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_multiply.cc",
                         "primitive_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
