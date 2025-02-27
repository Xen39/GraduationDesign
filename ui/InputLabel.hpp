#pragma once

#include <memory>
#include <opencv2/opencv.hpp>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QLabel>
#include <QTimer>

namespace ui {
    class InputLabel : public QLabel {
    public:
        InputLabel(QWidget *widget = nullptr);

        bool startCamera();

        void stopCamera();

        void changeCameraStatus();

    protected:
        void dragEnterEvent(QDragEnterEvent *event) override;

        void dropEvent(QDropEvent *event) override;

    private:
        void updateFrame();

        cv::VideoCapture cap;
        QTimer cameraTimer;
    };
}


