#pragma once

#include <cstdint>

namespace program::shape {
    enum class ShapeType : uint32_t {
        First,
        Arc = First,
        Circle,
        InfiniteLine,
        LineSegment,
        Parallelogram,
        Rectangle,
        Last = Rectangle
    };

    ShapeType getShapeType(uint32_t idx);
}