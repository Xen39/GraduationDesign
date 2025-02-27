#pragma once

#include "Shape.hpp"

#include "util/util.hpp"

namespace program::shape {
    class Parallelogram : public Shape {
    public:
        Parallelogram(const cv::Point &p1, const cv::Point &p2, const cv::Point &p3, const cv::Point &p4);

        virtual ~Parallelogram() = default;

        [[nodiscard]] virtual constexpr const char *shapeName() const override { return "平行四边形"; }

        virtual std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
                    {"图形",  shapeName()},
                    {"长",    std::to_string(length)},
                    {"宽",    std::to_string(width)},
                    {"端点1", util::to_string(v1)},
                    {"端点2", util::to_string(v2)},
                    {"端点3", util::to_string(v3)},
                    {"端点4", util::to_string(v4)},
            };
        }

        virtual void draw(cv::Mat &mat) const override;

    protected:
        cv::Point v1, v2, v3, v4; // 平行四边形v1v2v3v4, 12 & 34为长边, 14 & 23为短边
        int length;
        int width;
    };
}
