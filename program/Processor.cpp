#include "Processor.hpp"

#include <limits>
#include <sstream>
#include <vector>
#include <opencv2/opencv.hpp>

#include <QInputDialog>

#include "program/shape/ShapeFactory.hpp"
#include "util/macros.hpp"
#include "util/util.hpp"

using namespace std;
using namespace util;
using namespace program::shape;

namespace program {
    void Processor::preprocess(const cv::Mat &mat) {
        if (mat.empty())
            return;
        clear();
        this->oriMat = mat.clone();

        // 灰度化
        cv::Mat gray;
        cv::cvtColor(mat, gray, cv::COLOR_BGR2GRAY);
        // 噪声去除 - 高斯模糊
        cv::Mat blurred;
        cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);
        // 噪声去除 - 中值滤波
        cv::Mat denoised;
        cv::medianBlur(blurred, denoised, 5);
        // 图像增强 - 直方图均衡化
        cv::Mat enhanced;
        cv::equalizeHist(denoised, enhanced);
        // 二值化 - 自适应阈值法
        cv::Mat processed;
        cv::adaptiveThreshold(enhanced, processed, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
        // 边缘检测
        cv::Mat edges;
        cv::Canny(blurred, edges, 50, 150);
        // 查找轮廓
        vector<cv::Vec4i> hierarchy;
        cv::findContours(edges, *contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
        CHECK(!contours->empty(), "Processor::Processor() cannot find contour");
    }

    bool Processor::drawShape(ShapeType type) {
        auto shape = ShapeFactory::build(type, points, contours);
        if (shape == nullptr) {
            QWarn("Too few points to draw the target shape");
            return false;
        }
        if (shape->failed()) {
            QWarn("Latest several points cannot form a " + QString(shape->shapeName()));
            return false;
        }
        shapes.addShape(shape);
        return true;
    }

    void Processor::removeAllPoints() {
        points.clear();
    }

    void Processor::removeLastPoint() {
        if (!points.empty())
            points.pop_back();
    }

    void Processor::removeCurrentShape() {
        shapes.removeCurShape();
    }

    cv::Point Processor::toNearestContourPoint(cv::Point const &pointFrom) {
        CHECK(!contours->empty(), "toNearestContourPoint() called without contour");
        cv::Point const *nearestPoint = nullptr;
        int minDistSquare = numeric_limits<int>::max();

        for (Contour const &contour: *contours) {
            for (cv::Point const &pointTo: contour) {
                int curDistSquare = distanceSquare(pointFrom, pointTo);
                if (curDistSquare < minDistSquare) {
                    nearestPoint = &pointTo;
                    minDistSquare = curDistSquare;
                }
            }
        }
        return *nearestPoint;
    }

    void Processor::addPoint(cv::Point p) {
        if (recognizeAsNearestContourPoint)
            points.push_back(toNearestContourPoint(p));
        else
            points.push_back(p);
    }

    bool Processor::circleResize() {
        auto circle = dynamic_pointer_cast<Circle>(shapes.curShape());
        if (circle == nullptr) {
            QWarn("请选择圆或圆弧以进行校正");
            return false;
        }
        int pictureLen = circle->getRadius();
        bool ok;
        double realLen = QInputDialog::getDouble(nullptr, "", "请输入圆的实际半径", pictureLen, 0.01, 2147483647, 2,
                                                 &ok);
        if (!ok)
            return false;
        util::setRatio(realLen / pictureLen);
        return true;
    }

    cv::Mat Processor::curFrame() {
        cv::Mat newFrame = oriMat.clone();
        if (newFrame.empty())
            return newFrame;
        shapes.draw(newFrame);
        if (showContours)
            cv::drawContours(newFrame, *contours, -1, BLUE, 1);
        if (showPoints) {
            for (const cv::Point &point: points)
                cv::circle(newFrame, point, 1, RED, 2);
        }
        return newFrame;
    }

    void Processor::clear() {
        if (contours == nullptr) {
            contours = make_shared<vector<Contour>>();
        } else {
            contours->clear();
        }
        points.clear();
        shapes.clear();
    }
}
