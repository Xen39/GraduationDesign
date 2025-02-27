#include "Arc.hpp"

#include <cmath>

#include "util/util.hpp"

using namespace std;
using namespace util;

namespace program::shape {
    Arc::Arc(const cv::Point &v1, const cv::Point &v2, const cv::Point &v3)
            : Circle(v1, v2, v3) {
        this->startAngle = calcAngle(center, v1);
        this->endAngle = calcAngle(center, v3);
        bool isClockwise = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x) < 0; // 是否顺时针
        if (isClockwise) {
            if (startAngle < endAngle) {
                startAngle += 360;
            }
        } else {
            if (startAngle > endAngle) {
                endAngle += 360;
            }
        }
    }

    void Arc::draw(cv::Mat &mat) const {
        cv::ellipse(mat, center, cv::Size(radius, radius), 0, startAngle, endAngle, color, thickness, getLineType());
    }
}