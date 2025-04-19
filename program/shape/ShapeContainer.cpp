#include "ShapeContainer.hpp"

#include <limits>

#include "util/util.hpp"

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
        if (curIdx != INVALID) {
            dehighlight(shapes[curIdx]);
        }
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
        if (curIdx == numShapes())
            curIdx--;
        highlight(shapes[curIdx]);
    }

    size_t ShapeContainer::numShapes() const {
        return shapes.size();
    }

    void ShapeContainer::previousShape() {
        if (shapes.empty()) {
            assert(curIdx == INVALID);
            return;
        }
        if (curIdx > 0) {
            dehighlight(shapes[curIdx]);
            curIdx--;
            highlight(shapes[curIdx]);
        }
    }

    void ShapeContainer::nextShape() {
        if (shapes.empty()) {
            assert(curIdx == INVALID);
            return;
        }
        if (curIdx < numShapes() - 1) {
            dehighlight(shapes[curIdx]);
            curIdx++;
            highlight(shapes[curIdx]);
        }
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

    const cv::Scalar ShapeContainer::DEFAULT_COLOR = GREEN;
    const int ShapeContainer::DEFAULT_THICKNESS = 1;
    const cv::Scalar ShapeContainer::HIGHLIGHTED_COLOR = YELLOW;
    const int ShapeContainer::HIGHLIGHTED_THICKNESS = DEFAULT_THICKNESS + 1;
}
