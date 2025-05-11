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

namespace {
    std::vector<cv::Point> findContourByPoint(std::shared_ptr<std::vector<std::vector<cv::Point>>>contours,
                                              cv::Point targetPoint) {
        for (const auto& contour: *contours) {
            for (const auto& point : contour) {
                if (point == targetPoint)
                    return contour;
            }
        }
        return {};
    }
}

namespace program::shape {

    class ShapeFactory {
    public:
        static std::shared_ptr<Shape> build(ShapeType type, std::vector<cv::Point> &points,
                                            std::shared_ptr<std::vector<std::vector<cv::Point>>> contours) {
            size_t numPoints = points.size();
            std::shared_ptr<Shape> shape = nullptr;
            auto removePoints = [&points](int n) {
                assert(points.size() >= n);
                points.erase(points.end() - n, points.end());
            };
            switch (type.type) {
                case ShapeType::Arc:
                    if (numPoints >= 3) {
                        shape = std::make_shared<Arc>(points[numPoints - 3], points[numPoints - 2],
                                                      points[numPoints - 1]);
                        if (shape != nullptr && !shape->failed())
                            removePoints(3);
                    }
                    break;
                case ShapeType::Circle:
                    if (numPoints >= 3) {
                        shape = std::make_shared<Circle>(points[numPoints - 3], points[numPoints - 2],
                                                         points[numPoints - 1]);
                        if (shape != nullptr && !shape->failed())
                            removePoints(3);
                    }
                    break;
                case ShapeType::ConnectedPolyline:
                    if (numPoints >= 2) {
                        shape = std::make_shared<ConnectedPolyline>(points);
                        if (shape != nullptr && !shape->failed())
                            points.clear();
                    }
                    break;
                case ShapeType::ContourCurve:
                    if (numPoints >= 1) {
                        shape = std::make_shared<ContourCurve>(findContourByPoint(contours, points.back()));
                        if (shape != nullptr && !shape->failed())
                            removePoints(1);
                    }
                    break;
                case ShapeType::InfiniteLine:
                    if (numPoints >= 2) {
                        shape = std::make_shared<InfiniteLine>(points[numPoints - 2], points[numPoints - 1]);
                        if (shape != nullptr && !shape->failed())
                            removePoints(2);
                    }
                    break;
                case ShapeType::LineSegment:
                    if (numPoints >= 2) {
                        shape = std::make_shared<LineSegment>(points[numPoints - 2], points[numPoints - 1]);
                        if (shape != nullptr && !shape->failed())
                            removePoints(2);
                    }
                    break;
                case ShapeType::Parallelogram:
                    if (numPoints >= 4) {
                        shape = std::make_shared<Parallelogram>(points[numPoints - 4], points[numPoints - 3],
                                                                points[numPoints - 2], points[numPoints - 1]);
                        if (shape != nullptr && !shape->failed())
                            removePoints(4);
                    }
                    break;
                case ShapeType::Polyline:
                    if (numPoints >= 2) {
                        shape = std::make_shared<Polyline>(points);
                        if (shape != nullptr && !shape->failed())
                            points.clear();
                    }
                    break;
                case ShapeType::Rectangle:
                    if (numPoints >= 4) {
                        shape = std::make_shared<Rectangle>(points[numPoints - 4], points[numPoints - 3],
                                                            points[numPoints - 2], points[numPoints - 1]);
                        if (shape != nullptr && !shape->failed())
                            removePoints(4);
                    }
                    break;
                default:
                    throw std::runtime_error("Unexpected ShapeType " + std::to_string(static_cast<int>(type.type)));
            }
            return shape;
        }
    };

}
