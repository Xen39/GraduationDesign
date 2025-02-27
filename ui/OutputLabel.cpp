#include "OutputLabel.hpp"

#include <QMessageBox>
#include <QMouseEvent>
#include <QPointF>

#include "util/macros.hpp"
#include "util/util.hpp"
#include "program/shape/ShapeFactory.hpp"

using namespace std;
using namespace program;
using namespace program::shape;
using namespace util;

namespace {
    const cv::Scalar DEFAULT_COLOR = GREEN;
    const int DEFAULT_THICKNESS = 1;
}

namespace ui {
    OutputLabel::OutputLabel(QWidget *widget)
            : toNearestContourPoint(false), showContours(false), currentShapeIdx(0) {
        setStyleSheet("background-color: lightblue");
    }

    void OutputLabel::setOriPixmap(const QPixmap &pixmap) {
        this->setPixmap(pixmap);
        this->oriMat = util::QPixmapToCvMat(pixmap);
        processor = make_unique<Processor>(this->oriMat);
        this->clearShapes();
        updateFrame();
    }

    void OutputLabel::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            QPointF const clickPoint = event->position();

            int clickX = static_cast<int>(clickPoint.x());
            int clickY = static_cast<int>(clickPoint.y());

            QPixmap pixmap = this->pixmap();
            if (!pixmap.isNull()) {
                int labelWidth = this->width();
                int labelHeight = this->height();
                int pixmapWidth = pixmap.width();
                int pixmapHeight = pixmap.height();

                // 计算缩放后的 QPixmap 大小
                QSize scaledSize = pixmap.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio).size();
                int scaledWidth = scaledSize.width();
                int scaledHeight = scaledSize.height();

                // 计算 QPixmap 在 QLabel 中的偏移量（考虑居中对齐）
                int offsetX = (labelWidth - scaledWidth) / 2;
                int offsetY = (labelHeight - scaledHeight) / 2;

                // 检查点击位置是否在 QPixmap 范围内
                if (clickX >= offsetX && clickX < offsetX + scaledWidth &&
                    clickY >= offsetY && clickY < offsetY + scaledHeight) {
                    // 计算相对于缩放后 QPixmap 的坐标
                    int scaledClickX = clickX - offsetX;
                    int scaledClickY = clickY - offsetY;

                    // 计算缩放比例
                    double scaleX = static_cast<double>(pixmapWidth) / scaledWidth;
                    double scaleY = static_cast<double>(pixmapHeight) / scaledHeight;

                    // 将点击位置转换为相对于原始 QPixmap 的坐标
                    int pixmapX = static_cast<int>(scaledClickX * scaleX);
                    int pixmapY = static_cast<int>(scaledClickY * scaleY);

                    // 确保坐标在 QPixmap 范围内
                    pixmapX = std::max(0, std::min(pixmapX, pixmapWidth - 1));
                    pixmapY = std::max(0, std::min(pixmapY, pixmapHeight - 1));

                    cv::Point point(pixmapX, pixmapY);
                    if (toNearestContourPoint)
                        point = processor->toNearestContourPoint(point);
                    if (!points.empty() && point == points.back()) {
                        QWARN("两次所选点不能重合");
                    } else {
                        points.push_back(point);
                    }
                    updateFrame();
                }
            }
        }
    }

    void OutputLabel::updateFrame() {
        cv::Mat newFrame = oriMat.clone();
        if (showPoints) {
            for (const cv::Point &point: points)
                cv::circle(newFrame, point, 1, RED, 2);
        }
        for (const auto &shape: shapes)
            shape->draw(newFrame);
        if (this->showContours)
            cv::drawContours(newFrame, processor->getContours(), -1, BLUE, 1);
        this->setPixmap(util::cvMatToQPixmap(newFrame));
    }

    bool OutputLabel::drawShape(::program::shape::ShapeType type) {
        auto shape = ShapeFactory::build(type, points);
        if (shape == nullptr) {
            QWARN("Too few points to draw a " + QString(shape->shapeName()));
            return false;
        }
        if (shape->failed()) {
            QWARN("Latest several points cannot form a " + QString(shape->shapeName()));
            return false;
        }
        shape->setColor(DEFAULT_COLOR);
        shape->setThickness(DEFAULT_THICKNESS);
        shapes.push_back(std::move(shape));
        highlightNextShape();
        return true;
    }

    void OutputLabel::removeLastPoint() {
        if (!points.empty())
            points.pop_back();
    }

    void OutputLabel::removeCurrentShape() {
        if (!shapes.empty()) {
            shapes.pop_back();
            fixCurrentShapeIdx();
        }
    }

    void OutputLabel::clearShapes() {
        this->points.clear();
        this->shapes.clear();
    }

    void OutputLabel::highlightPreviousShape() {
        fixCurrentShapeIdx();
        if (numShapes() == 0)
            return;
        if (currentShapeIdx > 0) {
            shapes[currentShapeIdx]->setColor(DEFAULT_COLOR);
            shapes[currentShapeIdx]->setThickness(DEFAULT_THICKNESS);
            currentShapeIdx--;
        }
        highlightCurrentShape();
    }

    void OutputLabel::highlightNextShape() {
        fixCurrentShapeIdx();
        if (numShapes() == 0)
            return;
        if (currentShapeIdx < shapes.size() - 1) {
            shapes[currentShapeIdx]->setColor(DEFAULT_COLOR);
            shapes[currentShapeIdx]->setThickness(DEFAULT_THICKNESS);
            currentShapeIdx++;
        }
        highlightCurrentShape();
    }

    void OutputLabel::highlightCurrentShape() {
        fixCurrentShapeIdx();
        if (0 <= currentShapeIdx && currentShapeIdx < numShapes()) {
            shapes[currentShapeIdx]->setColor(YELLOW);
            shapes[currentShapeIdx]->setThickness(DEFAULT_THICKNESS + 1);
        }
    }
}
