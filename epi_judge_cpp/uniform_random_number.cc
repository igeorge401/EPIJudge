#include <functional>
#include <random>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// Input: two integers, a lower bound and a higher bound. Let's call them x and y. You have a function that can produce zeroes and ones at random. (Hint, hint.)
// Output: a number in the range [x, y], inclusive, that is equiprobabilistically, randomly produced. 
// Zeroes and ones. Bits. OK. We can look at any number as a sequence of zeros and ones, each bit having a 50/50 percent shot of turning out either. That means we need to figure out how many bits to produce, and how to make it so that each number has an equal chance of being produced. 

// It'd be easier to deal with a range from [0, upper_bound-lower_bound], conceptually, to figure out the number of bits we need to produce. 0 can always be represented as 0....0, 1 as 0....1, 2 as 0....10, and so on. So let's do that, so long as we remember to adjust the boundary at the end. We can iterate by using the bit shift (the power of 2) of the loop count: 1, 2, 4, and so on. The number of iterations will translate into the amount of bits we need to represent all possibilities.

int ZeroOneRandom() {
  default_random_engine gen((random_device())());
  uniform_int_distribution<int> dis(0, 1);
  return dis(gen);
}

// Example: [0, 10]. (1 << i) == 1, 2, 4, 8: four iterations. Acceptable highest value: 1010.

int UniformRandom(int lower_bound, int upper_bound) {
  int upper_adjusted_bound = upper_bound-lower_bound+1; // Total number of possibilities. Don't forget the offset like I originally did.
  
  // Just slapping on a ZeroOneRandom that we left shift doesn't work. That was my first approach. What we need is a loop that makes this random, and if we get a result that is out of the range, we throw it out and try again.
  int result = 0;
  while (true) {
  	for (int i = 0; (1 << i) < upper_adjusted_bound; ++i) {
  		result |= (ZeroOneRandom() << i);
  	}
  	if (result < upper_adjusted_bound) break;
  	else result = 0;
  }
  return result + lower_bound;
}

// Time complexity: Something logorithmic, given we are iterating over the number of bits which is a power of two. log(upper_adjusted_bound), maybe?

bool UniformRandomRunner(TimedExecutor& executor, int lower_bound,
                         int upper_bound) {
  using namespace test_framework;
  vector<int> result;
  executor.Run([&] {
    std::generate_n(back_inserter(result), 100000,
                    std::bind(UniformRandom, lower_bound, upper_bound));
  });

  vector<int> sequence;
  std::transform(begin(result), end(result), back_inserter(sequence),
                 [lower_bound](int result) { return result - lower_bound; });
  return CheckSequenceIsUniformlyRandom(result, upper_bound - lower_bound + 1,
                                        0.01);
}

void UniformRandomWrapper(TimedExecutor& executor, int lower_bound,
                          int upper_bound) {
  RunFuncWithRetries(
      bind(UniformRandomRunner, std::ref(executor), lower_bound, upper_bound));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "lower_bound",
                                       "upper_bound"};
  return GenericTestMain(args, "uniform_random_number.cc",
                         "uniform_random_number.tsv", &UniformRandomWrapper,
                         DefaultComparator{}, param_names);
}
