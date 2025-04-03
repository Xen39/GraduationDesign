#pragma once

#include <opencv2/opencv.hpp>

#include "Circle.hpp"

namespace program::shape {
    class Arc : public Circle {
    public:
        Arc(const cv::Point &endPoint1, const cv::Point &midPoint, const cv::Point &endPoint2);

        [[nodiscard]] virtual constexpr const char *shapeName() const { return "圆弧"; }

        virtual std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
                    {"图形",           shapeName()},
                    {"圆心",           util::to_string(center)},
                    {"半径",           std::to_string(radius)},
                    {"起始角度(360°)", std::to_string(startAngle)},
                    {"结束角度(360°)", std::to_string(endAngle)}
            };
        }

        virtual void draw(cv::Mat &mat) const override;

    protected:
        double startAngle;
        double endAngle;
    };
}
