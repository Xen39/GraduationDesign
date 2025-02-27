#include "Circle.hpp"

#include <cmath>

using namespace std;
using namespace util;

namespace program::shape {
    Circle::Circle(const cv::Point &v1, const cv::Point &v2, const cv::Point &v3) {
        assert(v1 != v2 && v1 != v3 && v2 != v3);
        int x1 = v1.x, y1 = v1.y;
        int x2 = v2.x, y2 = v2.y;
        int x3 = v3.x, y3 = v3.y;
        double a = x1 - x2;
        double b = y1 - y2;
        double c = x1 - x3;
        double d = y1 - y3;
        double e = ((x1 * x1 - x2 * x2) - (y2 * y2 - y1 * y1)) / 2.0;
        double f = ((x1 * x1 - x3 * x3) - (y3 * y3 - y1 * y1)) / 2.0;
        double x0 = (e * d - b * f) / (a * d - b * c);
        double y0 = (a * f - e * c) / (a * d - b * c);
        center = cv::Point(static_cast<int>(x0), static_cast<int>(y0));
        radius = static_cast<int>(round((distance(v1, center) + distance(v2, center) + distance(v3, center)) / 3.0));
    }

    void Circle::draw(cv::Mat &mat) const {
        cv::circle(mat, center, radius, color, thickness,getLineType());
    }
}