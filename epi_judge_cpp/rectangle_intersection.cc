#include <tuple>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
struct Rect {
  int x, y, width, height;
};

// Input: Two Rect structs.
// Output: Detect whether the two rects have a nonempty intersection. If they do, return the rectangle formed by the intersection, if not, throw an "error" rect.

// What is the criterion for a nonempty intersection? Take (x, y) as an origin. r1.x+r1.width is how much the r1 rectangle spans horizontally to one side... just pumped out a Python script to visualize the triangles. We've got to encompass each point within bounds.

bool DoesIntersect(const Rect& r1, const Rect& r2) {
	return (r1.x+r1.width >= r2.x && r2.x+r2.width >= r1.x && r1.y+r1.height >= r2.y && r2.y+r2.height >= r1.y);
}

// Suppose we have an intersection: what Rect would that product be? 
	// The origin of the rectangle would have to encompass both rectangles: that means that it is as the border of the bigger one?
	// The width and the height are tricker. To achieve this one, I thought in terms of generating the total and subtracting the offset. Has to encompass everything, right? So the minimum minus the maximum.

Rect IntersectRectangle(const Rect& r1, const Rect& r2) {
  return DoesIntersect(r1, r2) ? Rect{std::max(r1.x, r2.x), std::max(r1.y, r2.y), std::min(r1.x+r1.width, r2.x+r2.width)-std::max(r1.x, r2.x), std::min(r1.y+r1.height, r2.y+r2.height)-std::max(r1.y, r2.y)} : Rect{0, 0, -1, -1};
}

// Time complexity: O(1)?

bool operator==(const Rect& r1, const Rect& r2) {
  return std::tie(r1.x, r1.y, r1.width, r1.height) ==
         std::tie(r2.x, r2.y, r2.width, r2.height);
}

namespace test_framework {
template <>
struct SerializationTrait<Rect> : UserSerTrait<Rect, int, int, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("height({})", arg_name), FmtStr("width({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Rect& x) {
    return {x.height, x.width};
  }
};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const Rect& r) {
  return PrintTo(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"r1", "r2"};
  return GenericTestMain(args, "rectangle_intersection.cc",
                         "rectangle_intersection.tsv", &IntersectRectangle,
                         DefaultComparator{}, param_names);
}
