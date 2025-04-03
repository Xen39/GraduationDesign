#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "program/shape/Shape.hpp"

namespace program::shape {
    class Polyline : public Shape {
    public:
        Polyline(std::vector<cv::Point> points);

        virtual ~Polyline() = default;

        const char *shapeName() const override { return "多段折线"; }

        std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
                    {"图形",   shapeName()},
                    {"总长度", std::to_string(length())},
            };
        }

        void draw(cv::Mat &mat) const override;

    private:
        double length() const;

        std::vector<cv::Point> points;
    };

}
