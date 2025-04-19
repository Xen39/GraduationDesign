#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

namespace program::shape {
    class ShapeType {
    private:
        enum class Type : int {
            First,
            Arc = First,
            Circle,
            ConnectedPolyline,
            ContourCurve,
            InfiniteLine,
            LineSegment,
            Parallelogram,
            Polyline,
            Rectangle,
            Last = Rectangle
        };

    public:
        ShapeType(Type type) : type(type) {}

        static ShapeType fromInt(int idx) {
            if (idx < static_cast<int>(Type::First) || idx > static_cast<int>(Type::Last))
                throw std::runtime_error("shape type idx out of range: " + std::to_string(idx));
            return ShapeType(static_cast<Type>(idx));
        }

        static constexpr Type Arc = Type::Arc;
        static constexpr Type Circle = Type::Circle;
        static constexpr Type ConnectedPolyline = Type::ConnectedPolyline;
        static constexpr Type ContourCurve = Type::ContourCurve;
        static constexpr Type InfiniteLine = Type::InfiniteLine;
        static constexpr Type LineSegment = Type::LineSegment;
        static constexpr Type Parallelogram = Type::Parallelogram;
        static constexpr Type Polyline = Type::Polyline;
        static constexpr Type Rectangle = Type::Rectangle;

    private:
        Type type;

        friend class ShapeFactory;
    };
}