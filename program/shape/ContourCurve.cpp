#include "ContourCurve.hpp"

using namespace std;

namespace program::shape{
    ContourCurve::ContourCurve(shared_ptr<vector<vector<cv::Point>>> contours, const cv::Point &target)
    :contours(contours) {
        contourIdx = -1;
        for (int i = 0;i<contours->size();++i) {
            for (const auto &p: contours->at(i)) {
                if (p == target) {
                    contourIdx = i;
                }
            }
        }
        if (contourIdx == -1) {
            setFailed();
        }
    }

    void ContourCurve::draw(cv::Mat &mat) const {
        cv::drawContours(mat, *contours, contourIdx, color, thickness, getLineType());
    }
}