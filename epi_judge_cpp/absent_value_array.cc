#include <stdexcept>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::invalid_argument;
using std::vector;

// Input: A massive input stream of files with IP addresses. In this massive pile of files, one address is missing. Can you find it?
// Output: Explained above.

// I think it's safe to say that brute force is out, and the problem explicitly rules out an external sort. So we'll need to be clever.

// Key insight: we have been talking all this time in terms of solution spaces, thinking in terms of them. Continue to do so. We can rule out half of the addresses in one go to begin with by looking exclusively at the first 16 bits: if a certain arrangement of the first 16 bits is missing, we know that this is what we must exclusively look for.

int FindMissingElement(vector<int>::const_iterator stream_begin,
                       const vector<int>::const_iterator& stream_end) {
  const int power = (1 << 16); // 2 ^ 16
  auto original_begin = stream_begin;
  std::vector<int> upper_half_bits(power, 0);
  while (stream_begin != stream_end) {
  	// Extract the first 16 bits.
  	auto cur_entry = *stream_begin++;
  	auto top_half = (cur_entry >> 16);
  	++upper_half_bits[top_half];
  }
  auto missing_top_half = 0;
  for (int i = 0; i < std::size(upper_half_bits); ++i) {
  	if (upper_half_bits[i] == 0) {
  		missing_top_half = i;
  		break;
  	}
  }
  // OK, we've identified half of the bits we need. Now we need to find all entries with this top half sequence.
  std::bitset<power> lower_half_bits; 
  stream_begin = original_begin;
  
  while (stream_begin != stream_end) {
  	// Extract the first 16 bits and compare...
  	auto cur_entry = *stream_begin++;
  	if (auto top_half = (cur_entry >> 16); top_half == missing_top_half) {
  		// Get the lower 16 bits by ANDing all them with 1 and clearing the top 16.
  		auto lower_16 = (cur_entry & (power-1));
  		lower_half_bits.set(lower_16);
  	}
  	
  }
  // Find the bitset entry that is equal to zero.
  for (int i = 0; i < std::size(lower_half_bits); ++i) {
  	if (lower_half_bits[i] == 0) {
  		// If I didn't have severe electronics induced ADHD, I would have figured this out earlier.
  		return (missing_top_half << 16) | i;
  	}
  }
  return -1;
}

// Time complexity: Linear. More interesting for this problem is the spatial complexity, which is on the order of 2^16.
void FindMissingElementWrapper(const vector<int>& stream) {
  try {
    int res = FindMissingElement(cbegin(stream), cend(stream));
    if (std::find(stream.begin(), stream.end(), res) != stream.end()) {
      throw TestFailure(std::to_string(res) + " appears in stream");
    }
  } catch (invalid_argument&) {
    throw TestFailure("Unexpected no missing element exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "absent_value_array.cc",
                         "absent_value_array.tsv", &FindMissingElementWrapper,
                         DefaultComparator{}, param_names);
}
