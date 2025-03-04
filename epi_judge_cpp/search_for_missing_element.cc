#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct DuplicateAndMissing {
  int duplicate, missing;
};

// Input: An unsorted vector A, filled with elements from 0 to N-1. Have a feeling this might be important.
// Output: There are two elements, a missing one and a duplicate one. Find them.

// My guess is that if we can find one, we can find the other. The problem statement mentions that if you XOR something by itself, it cancels. This means that if we XOR everything in the vector along with its index, then we should end up with the entanglement of: missing XOR duplicate XOR duplicate XOR duplicate == missing XOR duplicate. That gives us something to work with.

DuplicateAndMissing FindDuplicateMissing(const vector<int>& A) {
  auto entanglement = 0;
  for (int i = 0; i < std::size(A); ++i) {
  	entanglement ^= i;
  	entanglement ^= A[i];
  }
  // OK. What do we do from here? How can we get one of them? Let's extract the lowest set bit in the entanglement: that is something that *must* be different between the missing and duplicate numbers. One must have a zero at that bit, the other must have a one. 
  
// Let's go through the vector one more time. Any third number that happens to have the jth bit set as well will be XORed twice and will cancel out. When we stumble upon the one of the missing/duplicate pair that has a jth set bit, we will XOR it either once (the missing value) or three times (the duplicate value).
  auto LSB = (entanglement & ~(entanglement-1));
  auto jth_XOR = 0;
  for (int j = 0; j < std::size(A); ++j) {
  	if (j & LSB) { 
  		jth_XOR ^= j;
  	}
  	if (A[j] & LSB) {
  		jth_XOR ^= A[j];
  	}
  }
  return (std::find(std::begin(A), std::end(A), jth_XOR) == std::end(A)) ? DuplicateAndMissing{entanglement^jth_XOR, jth_XOR} : DuplicateAndMissing{jth_XOR, entanglement^jth_XOR};
}

// Time complexity: O(N).

namespace test_framework {
template <>
struct SerializationTrait<DuplicateAndMissing>
    : UserSerTrait<DuplicateAndMissing, int, int> {};
}  // namespace test_framework

bool operator==(const DuplicateAndMissing& lhs,
                const DuplicateAndMissing& rhs) {
  return std::tie(lhs.duplicate, lhs.missing) ==
         std::tie(rhs.duplicate, rhs.missing);
}

std::ostream& operator<<(std::ostream& out, const DuplicateAndMissing& x) {
  return out << "duplicate: " << x.duplicate << ", missing: " << x.missing;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "search_for_missing_element.cc", "find_missing_and_duplicate.tsv",
      &FindDuplicateMissing, DefaultComparator{}, param_names);
}
