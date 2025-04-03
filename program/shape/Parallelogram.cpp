#include "Parallelogram.hpp"

#include "util/util.hpp"
#include "LineSegment.hpp"

using namespace std;
using namespace util;
using namespace program::shape;

namespace {
    /// 循环交换
    void circularSwap(cv::Point &v1, cv::Point &v2, cv::Point &v3, cv::Point &v4) {
        cv::Point tmp = v1;
        v1 = v2;
        v2 = v3;
        v3 = v4;
        v4 = tmp;
    }
}

namespace program::shape {
    Parallelogram::Parallelogram(const cv::Point &p1, const cv::Point &p2, const cv::Point &p3, const cv::Point &p4) {
        LineSegment l12(p1, p2);
        LineSegment l13(p1, p3);
        LineSegment l14(p1, p4);
        LineSegment l23(p2, p3);
        LineSegment l24(p2, p4);
        LineSegment l34(p3, p4);
        // 平行四边形 v1v2v3v4
        if (l12.isAlmostParallel(l34) && l23.isAlmostParallel(l14)) {
            v1 = p1, v2 = p2, v3 = p3, v4 = p4;
        } else if (l12.isAlmostParallel(l34) && l13.isAlmostParallel(l24)) {
            v1 = p1, v2 = p2, v3 = p4, v4 = p3;
        } else if (l13.isAlmostParallel(l24) && l23.isAlmostParallel(l14)) {
            v1 = p1, v2 = p3, v3 = p2, v4 = p4;
        } else {
            setFailed();
            return;
        }
        // 对边边长相等
        if (abs(distance(v1, v2) - distance(v3, v4)) > 10 || abs(distance(v1, v4) - distance(v2, v3)) > 10) {
            setFailed();
            return;
        }
        // 确保边长v1v2 > v2v3
        if (distance(v1, v2) > distance(v2, v3)) {
            circularSwap(v1, v2, v3, v4);
        }
        length = roundToInt((distance(v1, v2) + distance(v3, v4)) / 2.0);
        width = roundToInt((distance(v1, v4) + distance(v2, v3)) / 2.0);
    }

    void Parallelogram::draw(cv::Mat &mat) const {
        cv::line(mat, v1, v2, color, thickness, getLineType());
        cv::line(mat, v2, v3, color, thickness, getLineType());
        cv::line(mat, v3, v4, color, thickness, getLineType());
        cv::line(mat, v4, v1, color, thickness, getLineType());
    }
}