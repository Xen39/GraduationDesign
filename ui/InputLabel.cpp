#include "InputLabel.hpp"

#include <QImage>
#include <QMimeData>
#include <QMessageBox>
#include <QPixmap>
#include <Qstring>

#include "../util/macros.hpp"
#include "../util/util.hpp"

using namespace std;
using namespace util;

namespace ui {
    InputLabel::InputLabel(QWidget *widget) : QLabel(widget), cameraTimer(this) {
        if (!connect(&cameraTimer, &QTimer::timeout, this, &InputLabel::updateFrame))
            QWarn("Cannot connect cameraTimer with InputLabel::updateFrame");
        setAcceptDrops(true);
        setStyleSheet("background-color: lightgreen");
    }

    bool InputLabel::startCamera() {
        if (!cap.isOpened()) {
            cap.open(0);
            if (!cap.isOpened())
                return false;
        }
        cameraTimer.start(30);
        return true;
    }

    void InputLabel::stopCamera() {
        if (cameraTimer.isActive())
            cameraTimer.stop();
        if (cap.isOpened())
            cap.release();
    }

    void InputLabel::changeCameraStatus() {
        if (cameraTimer.isActive()) {
            stopCamera();
        } else {
            bool success = startCamera();
            if (!success)
                QWarn("Camera open failed!");
        }
    }

    void InputLabel::dragEnterEvent(QDragEnterEvent *event) {
        const QMimeData *data = event->mimeData();
        if (data->hasUrls()) {
            QString filePath = data->urls().at(0).toLocalFile();
            QImage image(filePath);
            if (image.isNull()) {
                event->ignore();
            } else {
                event->acceptProposedAction();
            }
        } else {
            event->ignore();
        }
    }

    void InputLabel::dropEvent(QDropEvent *event) {
        const QMimeData *data = event->mimeData();
        if (data->hasUrls()) {
            QString filePath = data->urls().at(0).toLocalFile();
            QImage image(filePath);
            if (!image.isNull()) {
                stopCamera();
                QPixmap pixmap = QPixmap::fromImage(image);
                setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }
    }

    void InputLabel::updateFrame() {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            QWarn("Empty camera frame found, stopped camera");
            stopCamera();
            return;
        }
        QPixmap pixmap = cvMatToQPixmap(frame);
        // 显示图像
        this->setPixmap(pixmap.scaled(this->size(), Qt::KeepAspectRatio));
    }
}
