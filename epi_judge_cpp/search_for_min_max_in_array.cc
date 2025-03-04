#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
struct MinMax {
  int smallest, largest;
};

// Input: an unsorted vector A. 
// Output: Find the global minimum and maximum in the vector.

// How can we reduce the solution space when we don't have any sortedness? Let's have more modest ambitions than reducing whole swathes of the vector. If we compare two elements together, one will usually be greater than the other. That greater number can't be the global minimum, and the lesser number cannot be a global maximum. We need two solutions. Two solution spaces. Each time we encounter a pair of numbers, they are eliminated from one solution space before we even do a comparison to the existing candidate solutions.

MinMax FindMinMax(const vector<int>& A) {
  // Edge case: one element, one answer.
  if (std::size(A) == 1) return {A[0], A[0]};
  const int N = std::size(A);
  // Auto casts this to const.
  std::pair<int, int> global_minmax = std::minmax(A[0], A[1]);
  for (int i = 3; i < N; i += 2) {
  	std::pair<int, int> local_minmax = std::minmax(A[i-1], A[i]);
  	global_minmax.first = std::min(global_minmax.first, local_minmax.first);
  	global_minmax.second = std::max(global_minmax.second, local_minmax.second);
  }
  // Edge case: An odd numbered vector will not have the last element covered by the previous loop. And that could be either a minimum or a maximum.
  if (N % 2) {
  	global_minmax.first = std::min(global_minmax.first, A.back());
  	global_minmax.second = std::max(global_minmax.second, A.back());
  }
  return {global_minmax.first, global_minmax.second};
}
// Time complexity: O(N).

namespace test_framework {
template <>
struct SerializationTrait<MinMax> : UserSerTrait<MinMax, int, int> {};
}  // namespace test_framework

bool operator==(const MinMax& lhs, const MinMax& rhs) {
  return std::tie(lhs.smallest, lhs.largest) ==
         std::tie(rhs.smallest, rhs.largest);
}

std::ostream& operator<<(std::ostream& out, const MinMax& x) {
  return out << "min: " << x.smallest << ", max: " << x.largest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_for_min_max_in_array.cc",
                         "search_for_min_max_in_array.tsv", &FindMinMax,
                         DefaultComparator{}, param_names);
}
