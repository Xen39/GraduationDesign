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
#include "util/util.hpp"

namespace ui {
    class OutputLabel : public QLabel {
    public:
        OutputLabel(QWidget *widget = nullptr) { setStyleSheet("background-color: lightblue"); }

        void bindProcessor(std::shared_ptr<::program::Processor> processor) { this->processor = processor; }

        void updateFrame() { this->setPixmap(util::cvMatToQPixmap(processor->curFrame())); }

    protected:
        void mousePressEvent(QMouseEvent *event) override;

    private:
        std::shared_ptr<::program::Processor> processor;
    };
}

