#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "program/shape/ShapeType.hpp"
#include "program/shape/ShapeContainer.hpp"

namespace program {
    class Processor {
        using Contour = std::vector<cv::Point>;
    public:
        Processor() = default;

        void preprocess(cv::Mat const &mat);

        bool drawShape(shape::ShapeType type);

        void removeAllPoints();

        void removeLastPoint();

        void removeCurrentShape();

        void setToNearestContourPoint(bool b) { this->recognizeAsNearestContourPoint = b; }

        void setShowContours(bool b) { this->showContours = b; }

        void setShowPoints(bool b) { this->showPoints = b; }

        auto &getShapes() { return shapes; }

        void addPoint(cv::Point p);

        bool circleResize(); // 单圆校正

        cv::Mat curFrame();

    private:
        void clear();

        cv::Point toNearestContourPoint(const cv::Point &point);

        std::vector<Contour> contours;
        std::vector<cv::Point> points;
        program::shape::ShapeContainer shapes;
        cv::Mat oriMat;

        bool recognizeAsNearestContourPoint;
        bool showContours;
        bool showPoints;
    };
}

