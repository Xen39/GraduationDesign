#include "InfiniteLine.hpp"

using namespace std;

namespace program::shape {
    InfiniteLine::InfiniteLine(const cv::Point &v1, const cv::Point &v2) {
        assert(v1 != v2);
        if (v1.x == v2.x) {
            a = 1;
            b = 0;
            c = v1.x;
        } else if (v1.y == v2.y) {
            a = 0;
            b = 1;
            c = v1.y;
        } else {
            a = v2.y - v1.y;
            b = v1.x - v2.x;
            c = v2.x * v1.y - v1.x * v2.y;
            if (a < 0) {
                a = -a;
                b = -b;
                c = -c;
            }
        }
    }

    void InfiniteLine::draw(cv::Mat &mat) const {
        int width = mat.cols;
        int height = mat.rows;
        if (a == 0) { // 水平
            cv::line(mat, cv::Point(0, -c / b), cv::Point(width, -c / b), color, thickness, cv::LINE_AA);
            return;
        } else if (b == 0) { // 垂直
            cv::line(mat, cv::Point(-c / a, 0), cv::Point(-c / a, height), color, thickness, cv::LINE_AA);
            return;
        }

        auto xToY = [this](int x) {
            return static_cast<int>(round((double) (-a * x - c) / b));
        };
        auto yToX = [this](int y) {
            return static_cast<int>(round((double) (-b * y - c) / a));
        };
        cv::Point leftBoundaryPoint(0, xToY(0));
        cv::Point rightBoundaryPoint(width, xToY(width));
        cv::Point upBoundaryPoint(yToX(0), 0);
        cv::Point downBoundaryPoint(yToX(height), height);
        cv::Point leftPoint, rightPoint;
        if (0 <= leftBoundaryPoint.y && leftBoundaryPoint.y <= height) {
            leftPoint = leftBoundaryPoint;
        } else if (upBoundaryPoint.x < downBoundaryPoint.x) {
            leftPoint = upBoundaryPoint;
        } else {
            leftPoint = downBoundaryPoint;
        }

        if (0 <= rightBoundaryPoint.y && rightBoundaryPoint.y <= height) {
            rightPoint = rightBoundaryPoint;
        } else if (upBoundaryPoint.x > downBoundaryPoint.x) {
            rightPoint = upBoundaryPoint;
        } else {
            rightPoint = downBoundaryPoint;
        }
        cv::line(mat, leftPoint, rightPoint, color, thickness, getLineType());
    }

    bool InfiniteLine::isAlmostParallel(const InfiniteLine &that) const {
        if (this->isAlmostHorizontal() && that.isAlmostHorizontal())
            return true;
        if (this->isAlmostVertical() && that.isAlmostVertical())
            return true;
        return abs(this->a * that.b - this->b * that.a) <= 10;
    }

    bool InfiniteLine::isAlmostPerpendicular(const InfiniteLine &that) const {
        if (this->isAlmostHorizontal() && that.isAlmostVertical())
            return true;
        if (this->isAlmostVertical() && that.isAlmostHorizontal())
            return true;
        return abs(this->a * that.a + this->b * that.b) <= 10;
    }
}