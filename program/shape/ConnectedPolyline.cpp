#include "ConnectedPolyline.hpp"

#include "util/util.hpp"

using namespace std;
using namespace util;

namespace program::shape {
    ConnectedPolyline::ConnectedPolyline(std::vector<cv::Point> points) : Polyline(points) {
        if (points.size() <= 2) {
            setFailed();
        }
    }

    void ConnectedPolyline::draw(cv::Mat &mat) const {
        int i;
        for (i = 1; i < points.size(); ++i) {
            cv::line(mat, points[i - 1], points[i], color, thickness, getLineType());
        }
        assert(points.size() > 2);
        cv::line(mat, points[i - 1], points[0], color, thickness, getLineType());
    }

    double ConnectedPolyline::length() const {
        double len = 0.0;
        int i;
        for (i = 1; i < points.size(); ++i) {
            len += distance(points[i - 1], points[i]);
        }
        assert(points.size() > 2);
        len += distance(points[i - 1], points[0]);
        return len;
    }
}
