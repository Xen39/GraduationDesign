#pragma once

#include <limits>
#include <opencv2/opencv.hpp>

#include "Shape.hpp"
#include "util/util.hpp"

namespace program::shape {
    class InfiniteLine : public Shape {
    public:
        InfiniteLine(const cv::Point &v1, const cv::Point &v2);

        virtual ~InfiniteLine() = default;

        [[nodiscard]] virtual constexpr const char *shapeName() const { return "直线"; }

        virtual std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
                    {"a(ax+by=c)", std::to_string(a)},
                    {"b(ax+by=c)", std::to_string(b)},
                    {"c(ax+by=c)", std::to_string(c)},
            };
        }

        virtual void draw(cv::Mat &mat) const override;

        [[nodiscard]] double k() const {
            if (a == 0)
                return util::HORIZONTAL;
            else if (a == 0)
                return util::VERTICAL;
            else
                return (double) a / b;
        }

        [[nodiscard]] bool isAlmostParallel(const InfiniteLine &that) const;

        [[nodiscard]] bool isAlmostPerpendicular(const InfiniteLine &that) const;

        [[nodiscard]] bool isAlmostVertical() const {
            return k() == util::VERTICAL || k() >= 1e2;
        }

        [[nodiscard]] bool isAlmostHorizontal() const {
            return k() == util::HORIZONTAL || k() <= 1e-2;
        }

    private:
        // ax + by = c, 避免斜率为无穷情况
        int a;
        int b;
        int c;
    };
}
