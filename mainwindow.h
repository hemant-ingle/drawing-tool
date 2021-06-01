#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include <QPushButton>
#include <QKeyEvent>
#include "tmutility.h"
#include <QJsonDocument>
#include <QJsonObject>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void on_lineButton_clicked();

    void on_rectangleButton_clicked();

    void on_freeHandToolButton_clicked();

    void on_circleButton_clicked();

    void on_pickToolButton_clicked();

    void on_clearButton_clicked();

    void on_componentHistoryButton_clicked();

    void on_penSettingsButton_clicked();

    void on_brushSettingsButton_clicked();

    void on_componentsList_currentRowChanged(int currentRow);

    void on_penWidthComboBox_currentIndexChanged(int index);

    void on_penColorChooseButton_clicked();

    void on_penStyleComboBox_currentIndexChanged(int penStyleIndex);

    void on_penCapStyleComboBox_currentIndexChanged(int penCapStyleIndex);

    void on_penJoinStyleComboBox_currentIndexChanged(int penJoinStyleIndex);

    void on_brushFillCheckBox_stateChanged(int arg1);

    void on_brushColorChooseButton_clicked();

    void on_brushStyleComboBox_currentIndexChanged(int index);

    void on_componentsList_itemClicked(QListWidgetItem *item);

    void on_saveButton_clicked();

    void on_openButton_clicked();

    void on_groupButton_clicked();

    void on_ungroupButton_clicked();

private:
    Ui::MainWindow *ui;
    QFrame *currentFrame;
    QPushButton *currentTool;
    QPushButton * currentFrameButton;
};
#endif // MAINWINDOW_H
