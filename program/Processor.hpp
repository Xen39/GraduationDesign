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

        void removeLastPoint();

        void removeCurrentShape();

        void setToNearestContourPoint(bool b) { this->recognizeAsNearestContourPoint = b; }

        void setShowContours(bool b) { this->showContours = b; }

        void setShowPoints(bool b) { this->showPoints = b; }

        std::vector<std::pair<std::string, std::string>> getParamPairs() {
            auto shape = shapes.curShape();
            if (shape == nullptr) {
                return {};
            } else {
                return shape->getParamPairs();
            }
        }

        void previousShape() { shapes.previousShape(); }

        void nextShape() { shapes.nextShape(); }

        void addPoint(cv::Point p);

        cv::Mat curFrame();

    private:
        void clear();

        cv::Point toNearestContourPoint(const cv::Point &point);

        std::shared_ptr<std::vector<Contour>> contours;
        std::vector<cv::Point> points;
        program::shape::ShapeContainer shapes;
        cv::Mat oriMat;

        bool recognizeAsNearestContourPoint;
        bool showContours;
        bool showPoints;

        constexpr static int kGaussianBlurSize = 5;
        constexpr static double kCannyLowerThreshold = 50;
        constexpr static double kCannyUpperThreshold = 150;
    };
}

