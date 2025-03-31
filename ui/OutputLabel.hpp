#pragma once

#include <memory>
#include <opencv2/opencv.hpp>
#include <vector>

#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>

#include "program/Processor.hpp"
#include "program/shape/Shape.hpp"
#include "program/shape/ShapeContainer.hpp"
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

        size_t numShapes() { return shapes.numShapes(); }

        auto getParamPairs(size_t id) {
            return shapes[id]->getParamPairs();
        }

        void highlightPreviousShape() {shapes.highlightPreviousShape(); }

        void highlightNextShape() {shapes.highlightNextShape();}

    protected:
        void mousePressEvent(QMouseEvent *event) override;

    private:
        std::vector<cv::Point> points;
        program::shape::ShapeContainer shapes;
        std::unique_ptr<::program::Processor> processor;
        cv::Mat oriMat;
        bool toNearestContourPoint;
        bool showContours;
        bool showPoints;
    };
}

