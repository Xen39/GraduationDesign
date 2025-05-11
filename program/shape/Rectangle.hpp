#pragma once

#include <opencv2/opencv.hpp>

#include "Parallelogram.hpp"
#include "util/util.hpp"

namespace program::shape {
    class Rectangle : public Parallelogram {
    public:
        Rectangle(const cv::Point &p1, const cv::Point &p2, const cv::Point &p3, const cv::Point &p4);

        [[nodiscard]] virtual constexpr const char *shapeName() const { return "矩形"; }

        virtual std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
                    {"长",    std::to_string(util::getRatio() * length)},
                    {"宽",    std::to_string(util::getRatio() * width)},
            };
        }
    };
}


