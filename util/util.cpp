#include "util.hpp"

#include <ostream>

#include <QMessageBox>

using namespace std;

namespace util {
    QPixmap cvMatToQPixmap(const cv::Mat &mat) {
        if (mat.empty())
            return QPixmap();
        // 处理不同的图像格式
        switch (mat.type()) {
            case CV_8UC1: {
                // 单通道灰度图
                QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
                return QPixmap::fromImage(image);
            }
            case CV_8UC3: {
                // 三通道彩色图
                cv::Mat rgbMat;
                // 将BGR格式转换为RGB格式
                cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
                QImage image(rgbMat.data, rgbMat.cols, rgbMat.rows, rgbMat.step, QImage::Format_RGB888);
                return QPixmap::fromImage(image);
            }
            case CV_8UC4: {
                // 四通道带Alpha通道的图像
                QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
                return QPixmap::fromImage(image);
            }
            default:
                // 对于不支持的格式，返回空的QPixmap
                return QPixmap();
        }
    }

    cv::Mat QPixmapToCvMat(QPixmap const &pixmap) {
        if (pixmap.isNull())
            return cv::Mat();
        QImage image = pixmap.toImage();
        switch (image.format()) {
            case QImage::Format_RGB32: {
                image = image.convertToFormat(QImage::Format_RGB888);
            }
            case QImage::Format_RGB888: {
                // 对于RGB888格式，直接创建cv::Mat
                cv::Mat mat(image.height(), image.width(), CV_8UC3, const_cast<uchar *>(image.bits()),
                            image.bytesPerLine());
                // 从RGB转换为BGR
                cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
                return mat.clone();
            }
            case QImage::Format_ARGB32:
            case QImage::Format_ARGB32_Premultiplied: {
                // 对于带Alpha通道的格式，创建CV_8UC4类型的cv::Mat
                cv::Mat mat(image.height(), image.width(), CV_8UC4, const_cast<uchar *>(image.bits()),
                            image.bytesPerLine());
                return mat.clone();
            }
            case QImage::Format_Grayscale8: {
                // 对于灰度图格式，创建CV_8UC1类型的cv::Mat
                cv::Mat mat(image.height(), image.width(), CV_8UC1, const_cast<uchar *>(image.bits()),
                            image.bytesPerLine());
                return mat.clone();
            }
            default:
                // 对于不支持的格式，返回空的cv::Mat
                qDebug() << "Cannot convert to cv::Mat with image format " << static_cast<uint16_t>(image.format())
                         << '\n';
                return cv::Mat();
        }
    }

    int distanceSquare(const cv::Point &v1, const cv::Point &v2) {
        int x = v1.x - v2.x;
        int y = v1.y - v2.y;
        return (x * x) + (y * y);
    }

    double distance(const cv::Point &v1, const cv::Point &v2) {
        return sqrt((double)distanceSquare(v1, v2));
    }

    int roundToInt(double d) {
        return static_cast<int>(round(d));
    }

    string to_string(const cv::Point& v) {
        ostringstream oss;
        oss << '(' << v.x << ',' << v.y << ')';
        return oss.str();
    }

    double calcAngle(const cv::Point &origin, const cv::Point &target) {
        assert(origin != target);
        double angle = atan2(target.y - origin.y, target.x - origin.x) * 180 / CV_PI;
        if (angle < 0)
            angle += 360.0;
        return angle;
    }

}