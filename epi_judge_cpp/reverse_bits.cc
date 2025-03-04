#include "test_framework/generic_test.h"

// Input: A 64 bit unsigned integer, x.
// Output: x, with all bits reversed.

// You could naively do 32 swaps, one for each pair of bits. But you can also do this in five steps if you are willing to work with whole groups of bits at a time. RMB: F == 1111

unsigned long long ReverseBits(unsigned long long x) {
  // First, we swap the 32 bit halves of x. The first part of the command preserves the first 32 bits while clearing the remaining 32 bits, and shifts those first 32 bits to the right. The second does the converse with the second 32 bits, shifting them to the left. Each bit is now on its mirror half.
  x = (((x & 0xFFFFFFFF00000000) >> 32) | ((x & 0x00000000FFFFFFFF) << 32)); 
  // Now we do the same process, but with each 16 bit quarter within the halves. And so on and so forth until each bit is within a couple places of where it is supposed to be.
  x = (((x & 0xFFFF0000FFFF0000) >> 16) | ((x & 0x0000FFFF0000FFFF) << 16)); 
  x = (((x & 0xFF00FF00FF00FF00) >> 8) | ((x & 0x00FF00FF00FF00FF) << 8)); 
  x = (((x & 0xF0F0F0F0F0F0F0F0) >> 4) | ((x & 0x0F0F0F0F0F0F0F0F) << 4)); 
  // C == 1100, A == 1010.
  x = (((x & 0xCCCCCCCCCCCCCCCC) >> 2) | ((x & 0x3333333333333333) << 2)); 
  x = (((x & 0xAAAAAAAAAAAAAAAA) >> 1) | ((x & 0x5555555555555555) << 1)); 
  return x;
}

// Time complexity: O(1).

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
