#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <InputLabel.hpp>
#include <QListWidgetItem>

#include "program/Processor.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_runButton_clicked();

    void on_cameraButton_clicked();

    void on_drawButton_clicked();

    void on_removeAllPointsButton_clicked();

    void on_removeLastPointButton_clicked();

    void on_removeCurrentShapeButton_clicked();

    void on_resizeButton_clicked();

    void on_toNearestContourPointCheckBox_stateChanged(int val);

    void on_showContourCheckBox_stateChanged(int val);

    void on_showPointCheckBox_stateChanged(int val);

    void on_saveResultPicture_triggered();

    void on_saveShapeParams_triggered();

    void on_resizeDefaultButton_clicked();

    void on_shapeListWidget_itemClicked(QListWidgetItem *item);

private:
    void displayShapeInfo(const std::shared_ptr<program::shape::Shape> shape);

    void displayShapeList();

    void updateWindow();

    std::vector<std::pair<QLabel *, QLabel *>> displayParis;
    Ui::MainWindow *ui;
    std::shared_ptr<program::Processor> processor;
};
