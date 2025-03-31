#pragma once

#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>

#include "program/shape/Shape.hpp"

namespace program::shape {
    class ShapeContainer {
    public:
        ShapeContainer();

        std::shared_ptr<Shape> curShape();

        void addShape(const std::shared_ptr<Shape>& shape);

        void removeCurShape();

        [[nodiscard]] size_t numShapes() const;

        void previousShape();

        void nextShape();

        void draw(cv::Mat &mat);

        std::shared_ptr<Shape> operator[](size_t idx);

        void clear();

    private:
        void highlight(const std::shared_ptr<Shape>& shape);

        void dehighlight(const std::shared_ptr<Shape>& shape);

        std::vector<std::shared_ptr<Shape>> shapes;
        int curIdx;

        const static cv::Scalar DEFAULT_COLOR;
        const static int DEFAULT_THICKNESS;
        const static cv::Scalar HIGHLIGHTED_COLOR;
        const static int HIGHLIGHTED_THICKNESS;
    };
}
