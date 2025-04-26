#include "ShapeContainer.hpp"

#include <limits>

#include "util/util.hpp"
#include "util/macros.hpp"

using namespace std;
using namespace util;

namespace {
    constexpr int INVALID = -1;
}

namespace program::shape {
    ShapeContainer::ShapeContainer() {
        clear();
    }

    std::shared_ptr<Shape> ShapeContainer::curShape() {
        if (shapes.empty()) {
            assert(curIdx == INVALID);
            return nullptr;
        }
        return shapes[curIdx];
    }

    void ShapeContainer::addShape(const shared_ptr <Shape> &shape) {
        shapes.push_back(shape);
        dehighlightAll();
        curIdx = static_cast<int>(numShapes()) - 1;
        highlight(shapes[curIdx]);
    }

    void ShapeContainer::removeCurShape() {
        if (shapes.empty()) {
            assert(curIdx == INVALID);
            return;
        }
        assert(0 <= curIdx && curIdx < numShapes());
        shapes.erase(shapes.begin() + curIdx);
        if (shapes.empty()) {
            curIdx = INVALID;
            return;
        }
        if (curIdx >= numShapes())
            curIdx = numShapes() - 1;
        dehighlightAll();
        highlight(shapes[curIdx]);
    }

    size_t ShapeContainer::numShapes() const {
        return shapes.size();
    }

    void ShapeContainer::selectShape(size_t idx) {
        CHECK(0 <= idx && idx < shapes.size(), "shape idx out of range: " + to_string(idx));
        curIdx = idx;
        dehighlightAll();
        highlight(shapes[curIdx]);
    }

    void ShapeContainer::draw(cv::Mat &mat) {
        for (const auto &shape: shapes)
            shape->draw(mat);
    }

    std::shared_ptr<Shape> ShapeContainer::operator[](size_t idx) {
        assert(0 <= idx && idx < numShapes());
        return shapes[idx];
    }

    void ShapeContainer::clear() {
        shapes.clear();
        curIdx = INVALID;
    }

    void ShapeContainer::highlight(const std::shared_ptr<Shape> &shape) {
        shape->setColor(HIGHLIGHTED_COLOR);
        shape->setThickness(HIGHLIGHTED_THICKNESS);
    }

    void ShapeContainer::dehighlight(const std::shared_ptr<Shape> &shape) {
        shape->setColor(DEFAULT_COLOR);
        shape->setThickness(DEFAULT_THICKNESS);
    }

    void ShapeContainer::dehighlightAll() {
        for (auto& shape:shapes)
            dehighlight(shape);
    }

    const cv::Scalar ShapeContainer::DEFAULT_COLOR = GREEN;
    const int ShapeContainer::DEFAULT_THICKNESS = 1;
    const cv::Scalar ShapeContainer::HIGHLIGHTED_COLOR = YELLOW;
    const int ShapeContainer::HIGHLIGHTED_THICKNESS = DEFAULT_THICKNESS + 1;
}
