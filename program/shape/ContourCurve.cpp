#include "ContourCurve.hpp"

using namespace std;

namespace program::shape {
    ContourCurve::ContourCurve(const vector <cv::Point> &contour)
            : contour(contour) {}

    void ContourCurve::draw(cv::Mat &mat) const {
        cv::drawContours(mat, vector<vector<cv::Point>>{contour}, 0, color, thickness, getLineType());
    }
}
