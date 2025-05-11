#pragma once

#include <memory>
#include <vector>

#include "program/shape/Shape.hpp"

namespace program::shape {
    class ContourCurve : public Shape {
    public:
        ContourCurve(const std::vector<cv::Point>& contour);

        virtual ~ContourCurve() = default;

        [[nodiscard]] const char *shapeName() const override { return "轮廓线"; }

        virtual std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
            };
        }

        void draw(cv::Mat &mat) const override;

    private:
        std::vector<cv::Point> contour;
    };
}
