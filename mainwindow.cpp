#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cassert>
#include <fstream>

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QString>

#include "program/Processor.hpp"
#include "util/macros.hpp"
#include "util/util.hpp"

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
    updateWindow();
}

void MainWindow::on_drawButton_clicked() {
    auto shapeIdx = ui->shapeComboBox->currentIndex();
    if (processor->drawShape(ShapeType::fromInt(shapeIdx)))
        updateWindow();
}

void MainWindow::on_removeAllPointsButton_clicked() {
    processor->removeAllPoints();
    updateWindow();
}

void MainWindow::on_removeLastPointButton_clicked() {
    processor->removeLastPoint();
    updateWindow();
}

void MainWindow::on_removeCurrentShapeButton_clicked() {
    processor->removeCurrentShape();
    updateWindow();
}

void MainWindow::on_resizeButton_clicked() {
    if (processor->circleResize()) {
        updateWindow();
        ui->resizeLabel->setText(QString::fromStdString("当前缩放比例:" + std::to_string(util::getRatio())));
        QInfo("尺寸校正成功!");
    }
}

void MainWindow::on_resizeDefaultButton_clicked() {
    util::setRatio(1.0);
    ui->resizeLabel->setText(QString::fromStdString("当前缩放比例:" + std::to_string(util::getRatio())));
    updateWindow();
}

void MainWindow::on_toNearestContourPointCheckBox_stateChanged(int val) {
    processor->setToNearestContourPoint(ui->toNearestContourPointCheckBox->isChecked());
}

void MainWindow::on_showContourCheckBox_stateChanged(int val) {
    processor->setShowContours(ui->showContourCheckBox->isChecked());
    updateWindow();
}

void MainWindow::on_showPointCheckBox_stateChanged(int val) {
    processor->setShowPoints(ui->showPointCheckBox->isChecked());
    updateWindow();
}

void MainWindow::on_saveResultPicture_triggered() {
    QPixmap outputPixmap = ui->outputLabel->pixmap();
    if (outputPixmap.isNull()) {
        QWarn("图片为空,无法保存");
        return;
    }
    const QString &filePath = QFileDialog::getSaveFileName(this, "保存图片", "", "图片文件 (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        if (outputPixmap.save(filePath))
            QInfo(filePath + " 图片保存成功");
        else
            QWarn(filePath + " 图片保存失败");
    }
}

void MainWindow::on_saveShapeParams_triggered() {
    if (processor->getShapes().numShapes() == 0) {
        QWarn("未绘制任何图形,无法保存");
        return;
    }
    const string &filePath = QFileDialog::getSaveFileName(this, "保存图形参数", "", "表格 (*.csv)").toStdString();
    if (!filePath.empty()) {
        std::ofstream out(filePath);
        if (out.is_open()) {
            out << "编号,图形名称,参数1,参数2,参数3,..." << endl;
            for (const auto shape: processor->getShapes()) {
                static int i = 0;
                out << ++i << ',' << shape->shapeName();
                for (const auto &[paramName, paramValue]: shape->getParamPairs()) {
                    out << ",\"" << paramName << '=' << paramValue << "\"";
                }
                out << endl;
            }
            out.close();
            QInfo(filePath + " 文件保存成功!");
        } else {
            QWarn(filePath + " 文件打开失败！");
        }
    }
}

void MainWindow::on_shapeListWidget_itemClicked(QListWidgetItem *item) {
    size_t idx = ui->shapeListWidget->row(item);
    processor->getShapes().selectShape(idx);
    updateWindow();
}

void MainWindow::displayShapeInfo(const shared_ptr<Shape> shape) {
    if (shape == nullptr) {
        for (auto &[nameLabel, valueLabel]: displayParis) {
            nameLabel->setText("");
            valueLabel->setText("");
        }
        return;
    }
    const auto &paramPairs = shape->getParamPairs();
    if (paramPairs.size() + 1 > displayParis.size()) {
        QWarn("Too many shape param pairs!");
    }
    CHECK(!displayParis.empty(), "displayPairs is empty!");
    displayParis[0].first->setText("图形");
    displayParis[0].second->setText(shape->shapeName());
    size_t i;
    for (i = 1; i - 1 < paramPairs.size() && i < displayParis.size(); ++i) {
        auto &displayPair = displayParis[i];
        auto &paramPair = paramPairs[i - 1];
        displayPair.first->setText(QString::fromStdString(paramPair.first));
        displayPair.second->setText(QString::fromStdString(paramPair.second));
    }
    for (; i < displayParis.size(); ++i) {
        auto &displayPair = displayParis[i];
        displayPair.first->setText("");
        displayPair.second->setText("");
    }
}

void MainWindow::displayShapeList() {
    ui->shapeListWidget->clear();
    int idx = 0;
    for (auto iter: processor->getShapes()) {
        ostringstream oss;
        oss << "编号 " << ++idx << "    图形 " << iter->shapeName();
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(oss.str()), ui->shapeListWidget);
    }
    static constexpr QColor unselectedColor(255,255,255);
    static constexpr QColor selectedColor(200,200,200);
    for (int i = 0; i < ui->shapeListWidget->count(); ++i) {
        ui->shapeListWidget->item(i)->setBackground(unselectedColor);
    }
    if (processor->getShapes().numShapes() > 0) {
        auto curIdx = processor->getShapes().currentIdx();
        assert (0 <= curIdx && curIdx < ui->shapeListWidget->count());
        ui->shapeListWidget->item(curIdx)->setBackground(selectedColor);
    }
}

void MainWindow::updateWindow() {
    ui->outputLabel->updateFrame();
    displayShapeInfo(processor->getShapes().curShape());
    displayShapeList();
}
