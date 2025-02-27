#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

namespace program {
    class Processor {
        using Contour = std::vector<cv::Point>;
    public:
        Processor(cv::Mat const &image);

        cv::Point toNearestContourPoint(const cv::Point &point);

        std::vector<Contour> getContours() { return contours; }

    private:
        void clear();

        constexpr static int kGaussianBlurSize = 5;
        constexpr static double kCannyLowerThreshold = 50;
        constexpr static double kCannyUpperThreshold = 150;
        int width;
        int height;
        std::vector<Contour> contours;
    };
}

