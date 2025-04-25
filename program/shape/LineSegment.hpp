#pragma once

#include <opencv2/opencv.hpp>

#include "InfiniteLine.hpp"
#include "util/util.hpp"

namespace program::shape {
    class LineSegment : public InfiniteLine {
    public:
        LineSegment(const cv::Point &v1, const cv::Point &v2);

        [[nodiscard]] virtual constexpr const char *shapeName() const { return "线段"; }

        virtual std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
                    {"端点1", util::to_string(v1)},
                    {"端点2", util::to_string(v2)},
                    {"长度", std::to_string(util::getRatio() * length())}
            };
        }

        virtual void draw(cv::Mat &mat) const override;

        [[nodiscard]] int length() const {
            return util::roundToInt(util::distance(v1, v2));
        }

    private:
        cv::Point v1;
        cv::Point v2;
    };
}
