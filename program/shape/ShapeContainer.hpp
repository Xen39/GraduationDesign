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

        [[nodiscard]] auto currentIdx() const { return curIdx; }

        void addShape(const std::shared_ptr<Shape> &shape);

        void removeCurShape();

        [[nodiscard]] size_t numShapes() const;

        void selectShape(size_t idx);

        void draw(cv::Mat &mat);

        std::shared_ptr<Shape> operator[](size_t idx);

        void clear();

        [[nodiscard]] std::vector<std::shared_ptr<Shape>>::const_iterator begin() const { return shapes.begin(); }

        [[nodiscard]] std::vector<std::shared_ptr<Shape>>::const_iterator end() const { return shapes.end(); }

    private:
        void highlight(const std::shared_ptr<Shape> &shape);

        void dehighlight(const std::shared_ptr<Shape> &shape);

        void dehighlightAll();

        std::vector<std::shared_ptr<Shape>> shapes;
        int curIdx;

        const static cv::Scalar DEFAULT_COLOR;
        const static int DEFAULT_THICKNESS;
        const static cv::Scalar HIGHLIGHTED_COLOR;
        const static int HIGHLIGHTED_THICKNESS;
    };
}
