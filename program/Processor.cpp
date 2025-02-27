#include "Processor.hpp"

#include <limits>
#include <sstream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "util/macros.hpp"
#include "util/util.hpp"

using namespace std;
using namespace util;

namespace program {
    Processor::Processor(const cv::Mat &mat) {
        CHECK(!mat.empty(), "Cannot process empty image");
        clear();

        this->width = mat.cols;
        this->height = mat.rows;

        cv::Mat gray, blurred, edges;
        // 转为灰度图
        cv::cvtColor(mat, gray, cv::COLOR_BGR2GRAY);
        // 高斯模糊
        static_assert(kGaussianBlurSize % 2 == 1, "高斯核大小应为奇数");
        cv::GaussianBlur(gray, blurred, cv::Size(kGaussianBlurSize, kGaussianBlurSize), 0);
        // 边缘检测
        static_assert(2.0 <= kCannyUpperThreshold / kCannyLowerThreshold &&
                      kCannyUpperThreshold / kCannyLowerThreshold <= 3.0);
        cv::Canny(blurred, edges, kCannyLowerThreshold, kCannyUpperThreshold);
        // 查找轮廓
        vector<cv::Vec4i> hierarchy;
        cv::findContours(edges, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
        CHECK(!contours.empty(), "Processor::Processor() cannot find contour");
    }

    cv::Point Processor::toNearestContourPoint(cv::Point const &pointFrom) {
        CHECK(!contours.empty(), "toNearestContourPoint() called without contour");
        cv::Point const *nearestPoint = nullptr;
        int minDistSquare = numeric_limits<int>::max();

        for (Contour const &contour: contours) {
            for (cv::Point const &pointTo: contour) {
                int curDistSquare = distanceSquare(pointFrom, pointTo);
                if (curDistSquare < minDistSquare) {
                    nearestPoint = &pointTo;
                    minDistSquare = curDistSquare;
                }
            }
        }
        return *nearestPoint;
    }

    void Processor::clear() {
        this->contours.clear();
        this->width = this->height = 0;
    }
}