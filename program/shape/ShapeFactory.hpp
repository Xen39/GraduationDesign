#pragma once

#include <memory>
#include <vector>

#include "program/shape/Arc.hpp"
#include "program/shape/Circle.hpp"
#include "program/shape/InfiniteLine.hpp"
#include "program/shape/LineSegment.hpp"
#include "program/shape/Parallelogram.hpp"
#include "program/shape/Rectangle.hpp"
#include "program/shape/Shape.hpp"
#include "program/shape/ShapeType.hpp"

namespace program::shape {

    class ShapeFactory {
    public:
        static std::unique_ptr<Shape> build(ShapeType type, const std::vector<cv::Point>& points) {
            size_t n = points.size();
            std::unique_ptr<Shape> shape = nullptr;
            switch(type) {
                case ShapeType::Arc:
                    if (n >= 3) {
                        shape = std::make_unique<Arc>(points[n -3], points[n - 2], points[n - 1]);
                    }
                    break;
                case ShapeType::Circle:
                    if (n >= 3) {
                        shape = std::make_unique<Circle>(points[n -3], points[n - 2], points[n - 1]);
                    }
                    break;
                case ShapeType::InfiniteLine:
                    if (n >= 2) {
                        shape = std::make_unique<InfiniteLine>( points[n - 2], points[n - 1]);
                    }
                    break;
                case ShapeType::LineSegment:
                    if (n >= 2) {
                        shape = std::make_unique<LineSegment>( points[n - 2], points[n - 1]);
                    }
                    break;
                case ShapeType::Parallelogram:
                    if (n >= 4) {
                        shape = std::make_unique<Parallelogram>( points[n-4], points[n-3],points[n - 2], points[n - 1]);
                    }
                    break;
                case ShapeType::Rectangle:
                    if (n >= 4) {
                        shape = std::make_unique<Rectangle>( points[n-4], points[n-3],points[n - 2], points[n - 1]);
                    }
                    break;
            }
            return std::move(shape);
        }
    };

}
