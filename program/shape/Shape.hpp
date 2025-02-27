#pragma once

#include <opencv2/opencv.hpp>
#include <string>

namespace program::shape {
    class Shape {
    public:
        Shape() : success(true) {}

        virtual ~Shape() = default;

        virtual const char *shapeName() const = 0;

        virtual std::vector<std::pair<std::string, std::string>> getParamPairs() const = 0;

        virtual void draw(cv::Mat &mat) const = 0;

        std::ostream &operator<<(std::ostream &out) const {
            auto const &paramPairs = getParamPairs();
            out << '{';
            size_t i;
            for (i = 0; i < paramPairs.size() - 1; ++i) {
                out << paramPairs[i].first << ": " << paramPairs[i].second << ", ";
            }
            out << paramPairs[i].first << ": " << paramPairs[i].second << '}';
            return out;
        }

        void setColor(const cv::Scalar &c) {
            this->color = c;
        }

        void setThickness(int t) {
            this->thickness = t;
        }

        bool failed() {
            return !success;
        }

    protected:
        void setFailed() {
            success = false;
        }

        auto getLineType() const {
            return cv::LINE_AA;
        }

        cv::Scalar color;
        int thickness;

    private:
        bool success;
    };
}
