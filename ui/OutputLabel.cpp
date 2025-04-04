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

namespace ui {
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
                    processor->addPoint(point);
                    updateFrame();
                }
            }
        }
    }
}
