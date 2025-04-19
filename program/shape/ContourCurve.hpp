#pragma once

#include <memory>
#include <vector>

#include "program/shape/Shape.hpp"

namespace program::shape {
    class ContourCurve : public Shape {
    public:
        ContourCurve(std::shared_ptr<std::vector<std::vector<cv::Point>>> contours, const cv::Point &target);

        virtual ~ContourCurve() = default;

        [[nodiscard]] const char *shapeName() const override { return "轮廓线"; }

        virtual std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
                    {"图形", shapeName()},
            };
        }

        void draw(cv::Mat &mat) const override;

    private:
        std::shared_ptr<const std::vector<std::vector<cv::Point>>> contours;
        int contourIdx;
    };
}
