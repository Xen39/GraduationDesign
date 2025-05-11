#pragma once

#include <memory>
#include <vector>

#include "program/shape/Arc.hpp"
#include "program/shape/Circle.hpp"
#include "program/shape/ConnectedPolyline.hpp"
#include "program/shape/ContourCurve.hpp"
#include "program/shape/InfiniteLine.hpp"
#include "program/shape/LineSegment.hpp"
#include "program/shape/Parallelogram.hpp"
#include "program/shape/Polyline.hpp"
#include "program/shape/Rectangle.hpp"
#include "program/shape/Shape.hpp"
#include "program/shape/ShapeType.hpp"

namespace program::shape {

    class ShapeFactory {
    public:
        static std::shared_ptr<Shape> build(ShapeType type, std::vector<cv::Point> &points,
                                            std::vector<std::vector<cv::Point>> &contours);
    };

}
