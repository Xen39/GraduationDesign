#pragma once

#include <memory>
#include <opencv2/opencv.hpp>
#include <vector>

#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>

#include "program/Processor.hpp"
#include "program/shape/Shape.hpp"
#include "program/shape/ShapeType.hpp"

namespace ui {
    class OutputLabel : public QLabel {
    public:
        OutputLabel(QWidget *widget = nullptr);

        void setOriPixmap(const QPixmap &pixmap);

        bool drawShape(::program::shape::ShapeType type);

        void removeLastPoint();

        void removeCurrentShape();

        void setToNearestContourPoint(bool val) { this->toNearestContourPoint = val; }

        void setShowContours(bool b) { this->showContours = b; }

        void setShowPoints(bool b) { this->showPoints = b; }

        void updateFrame();

        void clearShapes();

        size_t numShapes() { return shapes.size(); }

        auto getParamPairs(size_t id) {
            assert(id < numShapes());
            return shapes[id]->getParamPairs();
        }

        void highlightPreviousShape();

        void highlightNextShape();

        void fixCurrentShapeIdx() {
            if (numShapes() == 0 || currentShapeIdx < 0)
                currentShapeIdx = 0;
            if (currentShapeIdx >= numShapes())
                currentShapeIdx = numShapes() - 1;
        }
    protected:
        void mousePressEvent(QMouseEvent *event) override;

    private:
        void highlightCurrentShape();
        std::vector<cv::Point> points;
        std::vector<std::unique_ptr<::program::shape::Shape>> shapes;
        std::unique_ptr<::program::Processor> processor;
        cv::Mat oriMat;
        size_t currentShapeIdx;
        bool toNearestContourPoint;
        bool showContours;
        bool showPoints;
    };
}

