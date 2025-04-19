#include <cassert>

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QString>

#include "util/util.hpp"
#include "program/Processor.hpp"

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace util;
using namespace program;
using namespace program::shape;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), processor(make_shared<Processor>()) {
    ui->setupUi(this);
    ui->outputLabel->bindProcessor(processor);
    processor->setToNearestContourPoint(ui->toNearestContourPointCheckBox->isChecked());
    processor->setShowContours(ui->showContourCheckBox->isChecked());
    processor->setShowPoints(ui->showPointCheckBox->isChecked());
    displayParis.emplace_back(ui->name0Label, ui->value0Label);
    displayParis.emplace_back(ui->name1Label, ui->value1Label);
    displayParis.emplace_back(ui->name2Label, ui->value2Label);
    displayParis.emplace_back(ui->name3Label, ui->value3Label);
    displayParis.emplace_back(ui->name4Label, ui->value4Label);
    displayParis.emplace_back(ui->name5Label, ui->value5Label);
    displayParis.emplace_back(ui->name6Label, ui->value6Label);
    displayParis.emplace_back(ui->name7Label, ui->value7Label);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_cameraButton_clicked() {
    ui->inputLabel->changeCameraStatus();
}

void MainWindow::on_runButton_clicked() {
    QPixmap originPixmap = ui->inputLabel->pixmap();
    if (originPixmap.isNull())
        return;
    processor->preprocess(QPixmapToCvMat(originPixmap));
    ui->outputLabel->updateFrame();
}

void MainWindow::on_drawButton_clicked() {
    auto shapeIdx = ui->shapeComboBox->currentIndex();
    if (processor->drawShape(ShapeType::fromInt(shapeIdx))) {
        ui->outputLabel->updateFrame();
        displayParamPairs( processor->getParamPairs());
    }
}

void MainWindow::on_removeAllPointsButton_clicked() {
    processor->removeAllPoints();
    ui->outputLabel->updateFrame();
}

void MainWindow::on_removeLastPointButton_clicked() {
    processor->removeLastPoint();
    ui->outputLabel->updateFrame();
}

void MainWindow::on_removeCurrentShapeButton_clicked() {
    processor->removeCurrentShape();
    displayParamPairs(processor->getParamPairs());
    ui->outputLabel->updateFrame();
}

void MainWindow::on_resizeButton_clicked() {
    if (processor->circleResize())
        QInfo("尺寸校正成功!");
    displayParamPairs(processor->getParamPairs());
    ui->outputLabel->updateFrame();
}

void MainWindow::on_toNearestContourPointCheckBox_stateChanged(int val) {
    processor->setToNearestContourPoint(ui->toNearestContourPointCheckBox->isChecked());
}

void MainWindow::on_showContourCheckBox_stateChanged(int val) {
    processor->setShowContours(ui->showContourCheckBox->isChecked());
    ui->outputLabel->updateFrame();
}

void MainWindow::on_showPointCheckBox_stateChanged(int val) {
    processor->setShowPoints(ui->showPointCheckBox->isChecked());
    ui->outputLabel->updateFrame();
}

void MainWindow::on_actionaa_triggered() {
    QPixmap outputPixmap = ui->outputLabel->pixmap();
    if (outputPixmap.isNull()) {
        QWarn("图片为空,无法保存");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, "保存图片", "", "图片文件 (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        if (outputPixmap.save(filePath)) {
            QInfo(filePath + " 图片保存成功");
        } else {
            QWarn(filePath + " 图片保存失败");
        }

    }
}

void MainWindow::displayParamPairs(std::vector<std::pair<std::string, std::string>> paramPairs) {
    if (paramPairs.size() > displayParis.size()) {
        QWarn("Too many shape param pairs!");
    }
    size_t i;
    for (i = 0; i < paramPairs.size() && i < displayParis.size(); ++i) {
        auto &displayPair = displayParis[i];
        auto &paramPair = paramPairs[i];
        displayPair.first->setText(QString::fromStdString(paramPair.first));
        displayPair.second->setText(QString::fromStdString(paramPair.second));
    }
    for (; i < displayParis.size(); ++i) {
        auto &displayPair = displayParis[i];
        displayPair.first->setText("");
        displayPair.second->setText("");
    }
}

void MainWindow::on_previousShapeButton_clicked() {
    processor->previousShape();
    displayParamPairs(processor->getParamPairs());
    ui->outputLabel->updateFrame();
}

void MainWindow::on_nextShapeButton_clicked() {
    processor->nextShape();
    displayParamPairs(processor->getParamPairs());
    ui->outputLabel->updateFrame();
}
