#include "Rectangle.hpp"

#include "util/util.hpp"
#include "InfiniteLine.hpp"

using namespace std;
using namespace util;

namespace program::shape {
    Rectangle::Rectangle(const cv::Point &p1, const cv::Point &p2, const cv::Point &p3, const cv::Point &p4)
            : Parallelogram(p1, p2, p3, p4) {
        InfiniteLine l12(v1, v2);
        InfiniteLine l23(v2, v3);
        InfiniteLine l34(v3, v4);
        InfiniteLine l41(v4, v1);
        if (!l12.isAlmostPerpendicular(l23) && l23.isAlmostPerpendicular(l34) && l34.isAlmostPerpendicular(l41) &&
            l41.isAlmostPerpendicular(l12)) {
            setFailed();
            return;
        }
    }
}