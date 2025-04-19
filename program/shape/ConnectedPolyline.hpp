#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "program/shape/Polyline.hpp"
#include "util/util.hpp"

namespace program::shape {
    class ConnectedPolyline : public Polyline {
    public:
        ConnectedPolyline(std::vector<cv::Point> points);

        virtual ~ConnectedPolyline() = default;

        const char *shapeName() const override { return "多段折线(首尾相联)"; }

        std::vector<std::pair<std::string, std::string>> getParamPairs() const override {
            return {
                    {"图形",   shapeName()},
                    {"总长度", std::to_string(util::getRatio() * length())},
            };
        }

        void draw(cv::Mat &mat) const override;

    private:
        double length() const override;
    };

}
