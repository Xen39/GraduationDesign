#pragma once

#include <opencv2/opencv.hpp>

#include <QPixmap>

namespace util {
    QPixmap cvMatToQPixmap(const cv::Mat &mat);

    cv::Mat QPixmapToCvMat(const QPixmap &pixmap);

    int distanceSquare(const cv::Point &v1, const cv::Point &v2);

    double distance(const cv::Point &v1, const cv::Point &v2);

    int roundToInt(double d);

    template<typename T>
    const T& max(const T& t) {
        return t;
    }

    template<typename T, typename... Args>
    const T& max(const T& t, Args... args) {
        return std::max(t, max(args...));
    }

    template<typename T>
    const T& min(const T& t) {
        return t;
    }

    template<typename T, typename... Args>
    const T& min(const T& t, Args... args) {
        return std::min(t, min(args...));
    }
    
    std::string to_string(const cv::Point & v);

    /// return a degree within [0, 360)
    double calcAngle(const cv::Point &origin, const cv::Point &target);

    const cv::Scalar RED(0, 0, 255);
    const cv::Scalar GREEN(0, 255, 0);
    const cv::Scalar BLUE(255, 0, 0);
    const cv::Scalar YELLOW(0, 255, 255);

    constexpr double VERTICAL = std::numeric_limits<double>::max();
    constexpr double HORIZONTAL = std::numeric_limits<double>::max();
}
