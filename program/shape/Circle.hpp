#pragma once

#include <opencv2/opencv.hpp>

#include "Shape.hpp"
#include "util/util.hpp"

namespace program::shape {
    class Circle : public Shape {
    public:
        Circle(const cv::Point &v1, const cv::Point &v2, const cv::Point &v3);

        virtual ~Circle() = default;

        [[nodiscard]] virtual constexpr const char *shapeName() const override { return "圆"; }

        virtual std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
                    {"图形", shapeName()},
                    {"圆心", util::to_string(center)},
                    {"半径", std::to_string(radius * util::getRatio())}
            };
        }

        virtual void draw(cv::Mat &mat) const override;

        [[nodiscard]] int getRadius() const { return radius; }

    protected:
        cv::Point center;
        int radius;
    };
}
