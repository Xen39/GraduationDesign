#include "LineSegment.hpp"

namespace program::shape {
    LineSegment::LineSegment(const cv::Point &v1, const cv::Point &v2)
            : InfiniteLine(v1, v2) {
        if (v1.x < v2.x) {
            this->v1 = v1;
            this->v2 = v2;
        } else {
            this->v1 = v2;
            this->v2 = v1;
        }
    }

    void LineSegment::draw(cv::Mat &mat) const {
        cv::line(mat, v1, v2, color, thickness, getLineType());
    }
}
