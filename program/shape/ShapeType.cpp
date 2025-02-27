#include "ShapeType.hpp"

namespace program::shape{
    ShapeType getShapeType(uint32_t idx) {
        if (idx < static_cast<uint32_t>(ShapeType::First) || idx > static_cast<uint32_t>(ShapeType::Last))
            throw("shape type idx out of range: "+ idx);
        return ShapeType(idx);
    }
}
