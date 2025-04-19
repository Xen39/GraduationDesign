#include "Polyline.hpp"

#include "util/util.hpp"

using namespace std;
using namespace util;

namespace program::shape {
    Polyline::Polyline(std::vector<cv::Point> points) : points(points) {
        if (points.size() <= 1) {
            setFailed();
        }
    }

    void Polyline::draw(cv::Mat &mat) const {
        for (int i = 1; i < points.size(); ++i) {
            cv::line(mat, points[i - 1], points[i], color, thickness, getLineType());
        }
    }

    double Polyline::length() const {
        double len = 0.0;
        for (int i = 1; i < points.size(); ++i) {
            len += distance(points[i - 1], points[i]);
        }
        return len;
    }
}
