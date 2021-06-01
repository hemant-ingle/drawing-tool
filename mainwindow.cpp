#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentFrame=this->ui->componentsHistoryFrame;
    this->ui->drawingPad->setViewComponent(this->ui->componentsList);
    this->ui->penColorValueLabel->setText("#000000");
    this->ui->penColorValueLabel->setStyleSheet("color:black;background-color:black;border:1px solid white;");
    this->ui->brushColorValueLabel->setText("#ffffff");
    this->ui->brushColorValueLabel->setStyleSheet("color:white;background-color:white;border:1px solid white;");
    this->ui->brushFillCheckBox->setChecked(false);
    this->ui->brushColorLabel->setVisible(false);
    this->ui->brushColorValueLabel->setVisible(false);
    this->ui->brushColorChooseButton->setVisible(false);
    this->ui->brushStyleLabel->setVisible(false);
    this->ui->brushStyleComboBox->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
    {
        this->ui->drawingPad->setIsControlKeyPressed(true);
        Mode mode=this->ui->drawingPad->correctSelectionModeFinder();
        this->ui->drawingPad->setMode(mode);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
    {
        this->ui->drawingPad->setIsControlKeyPressed(false);
        this->ui->drawingPad->setMode(Mode::SELECTION);
    }
}

void MainWindow::on_lineButton_clicked()
{
    this->ui->drawingPad->selectLineTool();
}

void MainWindow::on_rectangleButton_clicked()
{
    this->ui->drawingPad->selectRectangleTool();
}

void MainWindow::on_freeHandToolButton_clicked()
{
    this->ui->drawingPad->selectFreeHandTool();
}

void MainWindow::on_circleButton_clicked()
{
    this->ui->drawingPad->selectCircleTool();
}

void MainWindow::on_pickToolButton_clicked()
{
    this->ui->drawingPad->selectPickTool();
}

void MainWindow::on_clearButton_clicked()
{
    this->ui->drawingPad->selectClearTool();
}

void MainWindow::on_componentHistoryButton_clicked()
{
    this->currentFrame->setVisible(false);
    this->currentFrame->setGeometry(790,20,0,0);
    this->currentFrame=this->ui->componentsHistoryFrame;
    this->currentFrame->setGeometry(790,20,162,561);
    this->currentFrame->setVisible(true);
}

void MainWindow::on_penSettingsButton_clicked()
{
    this->currentFrame->setVisible(false);
    this->currentFrame->setGeometry(790,20,0,0);
    this->currentFrame=this->ui->penSettingsFrame;
    this->currentFrame->setGeometry(790,20,162,561);
    this->currentFrame->setVisible(true);
}

void MainWindow::on_brushSettingsButton_clicked()
{
    this->currentFrame->setVisible(false);
    this->currentFrame->setGeometry(790,20,0,0);
    this->currentFrame=this->ui->brushSettingsFrame;
    this->currentFrame->setGeometry(790,20,162,561);
    this->currentFrame->setVisible(true);
}

void MainWindow::on_componentsList_currentRowChanged(int currentRow)
{
    if(currentRow==-1) return;
    this->ui->drawingPad->selectComponent(currentRow);
}

void MainWindow::on_penWidthComboBox_currentIndexChanged(int penWidthIndex)
{
    double penWidth=this->ui->drawingPad->getPenWidth();
    if(penWidthIndex==0) penWidth=1;
    else if(penWidthIndex==1) penWidth=2;
    else if(penWidthIndex==2) penWidth=3;
    else penWidth=4;
    this->ui->drawingPad->setPenWidth(penWidth);
}

void MainWindow::on_penColorChooseButton_clicked()
{
    QColor defaultColor=QColor(this->ui->penColorValueLabel->text());
    QColor color=QColorDialog::getColor(defaultColor,this,"Choose Color");
    QString colorName=color.name();
    if(color.isValid())
    {
        this->ui->penColorValueLabel->setStyleSheet("color:"+colorName+";background-color:"+colorName+";border:1px solid white;");
        this->ui->penColorValueLabel->setText(colorName);
    }
    this->ui->drawingPad->setPenColor(colorName);
}

void MainWindow::on_penStyleComboBox_currentIndexChanged(int penStyleIndex)
{
    Qt::PenStyle penStyle;
    if(penStyleIndex==0) penStyle=Qt::NoPen;
    else if(penStyleIndex==2) penStyle=Qt::DashLine;
    else if(penStyleIndex==3) penStyle=Qt::DotLine;
    else if(penStyleIndex==4) penStyle=Qt::DashDotLine;
    else if(penStyleIndex==5) penStyle=Qt::DashDotDotLine;
    else penStyle=Qt::SolidLine;
    this->ui->drawingPad->setPenStyle(penStyle);
}

void MainWindow::on_penCapStyleComboBox_currentIndexChanged(int penCapStyleIndex)
{
    Qt::PenCapStyle penCapStyle;
    if(penCapStyleIndex==0) penCapStyle=Qt::FlatCap;
    else if(penCapStyleIndex==2) penCapStyle=Qt::RoundCap;
    else penCapStyle=Qt::SquareCap;
    this->ui->drawingPad->setPenCapStyle(penCapStyle);
}

void MainWindow::on_penJoinStyleComboBox_currentIndexChanged(int penJoinStyleIndex)
{
    Qt::PenJoinStyle penJoinStyle;
    if(penJoinStyleIndex==0) penJoinStyle=Qt::MiterJoin;
    else if(penJoinStyleIndex==2) penJoinStyle=Qt::RoundJoin;
    else if(penJoinStyleIndex==3) penJoinStyle=Qt::SvgMiterJoin;
    else penJoinStyle=Qt::BevelJoin;
    this->ui->drawingPad->setPenJoinStyle(penJoinStyle);
}

void MainWindow::on_brushFillCheckBox_stateChanged(int arg1)
{
    if(arg1==0)
    {
        this->ui->brushColorLabel->setVisible(false);
        this->ui->brushColorValueLabel->setVisible(false);
        this->ui->brushColorChooseButton->setVisible(false);
        this->ui->brushStyleLabel->setVisible(false);
        this->ui->brushStyleComboBox->setVisible(false);
        Qt::BrushStyle brushStyle=Qt::NoBrush;
        this->ui->drawingPad->setBrushStyle(brushStyle);
    }
    if(arg1==2)
    {
        this->ui->brushColorLabel->setVisible(true);
        this->ui->brushColorValueLabel->setVisible(true);
        this->ui->brushColorChooseButton->setVisible(true);
        this->ui->brushStyleLabel->setVisible(true);
        this->ui->brushStyleComboBox->setVisible(true);
        QColor color=QColor(this->ui->brushColorValueLabel->text());
        QString colorName=color.name();
        if(color.isValid())
        {
            this->ui->brushColorValueLabel->setStyleSheet("color:"+colorName+";background-color:"+colorName+";border:1px solid white;");
            this->ui->brushColorValueLabel->setText(colorName);
            this->ui->drawingPad->setBrushColor(colorName);
        }
        Qt::BrushStyle brushStyle;
        int brushStyleIndex=this->ui->brushStyleComboBox->currentIndex();
        if(brushStyleIndex==0) brushStyle=Qt::NoBrush;
        else if(brushStyleIndex==2) brushStyle=Qt::Dense1Pattern;
        else if(brushStyleIndex==3) brushStyle=Qt::Dense2Pattern;
        else if(brushStyleIndex==4) brushStyle=Qt::Dense3Pattern;
        else if(brushStyleIndex==5) brushStyle=Qt::Dense4Pattern;
        else if(brushStyleIndex==6) brushStyle=Qt::Dense5Pattern;
        else if(brushStyleIndex==7) brushStyle=Qt::Dense6Pattern;
        else if(brushStyleIndex==8) brushStyle=Qt::Dense7Pattern;
        else if(brushStyleIndex==9) brushStyle=Qt::HorPattern;
        else if(brushStyleIndex==10) brushStyle=Qt::VerPattern;
        else if(brushStyleIndex==11) brushStyle=Qt::CrossPattern;
        else if(brushStyleIndex==12) brushStyle=Qt::BDiagPattern;
        else if(brushStyleIndex==13) brushStyle=Qt::FDiagPattern;
        else if(brushStyleIndex==14) brushStyle=Qt::DiagCrossPattern;
        else if(brushStyleIndex==15) brushStyle=Qt::LinearGradientPattern;
        else if(brushStyleIndex==16) brushStyle=Qt::ConicalGradientPattern;
        else if(brushStyleIndex==17) brushStyle=Qt::RadialGradientPattern;
        else if(brushStyleIndex==18) brushStyle=Qt::TexturePattern;
        else brushStyle=Qt::SolidPattern;
        this->ui->drawingPad->setBrushStyle(brushStyle);
    }
}

void MainWindow::on_brushColorChooseButton_clicked()
{
    QColor defaultColor=QColor(this->ui->brushColorValueLabel->text());
    QColor color=QColorDialog::getColor(defaultColor,this,"Choose Color");
    QString colorName=color.name();
    if(color.isValid())
    {
        this->ui->brushColorValueLabel->setStyleSheet("color:"+colorName+";background-color:"+colorName+";border:1px solid white;");
        this->ui->brushColorValueLabel->setText(colorName);
        this->ui->drawingPad->setBrushColor(colorName);
    }
    if(this->ui->brushFillCheckBox->isChecked()) this->ui->drawingPad->setBrushColor(colorName);
}

void MainWindow::on_brushStyleComboBox_currentIndexChanged(int brushStyleIndex)
{
    Qt::BrushStyle brushStyle;
    if(brushStyleIndex==0) brushStyle=Qt::NoBrush;
    else if(brushStyleIndex==2) brushStyle=Qt::Dense1Pattern;
    else if(brushStyleIndex==3) brushStyle=Qt::Dense2Pattern;
    else if(brushStyleIndex==4) brushStyle=Qt::Dense3Pattern;
    else if(brushStyleIndex==5) brushStyle=Qt::Dense4Pattern;
    else if(brushStyleIndex==6) brushStyle=Qt::Dense5Pattern;
    else if(brushStyleIndex==7) brushStyle=Qt::Dense6Pattern;
    else if(brushStyleIndex==8) brushStyle=Qt::Dense7Pattern;
    else if(brushStyleIndex==9) brushStyle=Qt::HorPattern;
    else if(brushStyleIndex==10) brushStyle=Qt::VerPattern;
    else if(brushStyleIndex==11) brushStyle=Qt::CrossPattern;
    else if(brushStyleIndex==12) brushStyle=Qt::BDiagPattern;
    else if(brushStyleIndex==13) brushStyle=Qt::FDiagPattern;
    else if(brushStyleIndex==14) brushStyle=Qt::DiagCrossPattern;
    else if(brushStyleIndex==15) brushStyle=Qt::LinearGradientPattern;
    else if(brushStyleIndex==16) brushStyle=Qt::ConicalGradientPattern;
    else if(brushStyleIndex==17) brushStyle=Qt::RadialGradientPattern;
    else if(brushStyleIndex==18) brushStyle=Qt::TexturePattern;
    else brushStyle=Qt::SolidPattern;
    if(this->ui->brushFillCheckBox->isChecked()==false) brushStyle=Qt::NoBrush;
    this->ui->drawingPad->setBrushStyle(brushStyle);
}

void MainWindow::on_componentsList_itemClicked(QListWidgetItem *item)
{
    this->on_componentsList_currentRowChanged(this->ui->componentsList->currentRow());
}

void MainWindow::on_saveButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QString fileName=dialog.getSaveFileName(this,"Save As","./Untitled.dtd","DrawingTool (*.DTD)");
    QJsonObject modelObject;
    this->ui->drawingPad->getModel()->write(modelObject);
    QJsonObject jsonObject;
    jsonObject["model"]=modelObject;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(QJsonDocument(jsonObject).toJson());
}


void MainWindow::on_openButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QString fileName=dialog.getOpenFileName(this,"Open",".","DrawingTool (*.DTD)");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray byteArray=file.readAll();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(byteArray));
    QJsonObject modelObject=jsonDocument.object();
    QJsonObject jsonObject=modelObject["model"].toObject();
    this->ui->drawingPad->getModel()->read(jsonObject);
    this->ui->drawingPad->repaint();
}

void MainWindow::on_groupButton_clicked()
{
    this->ui->drawingPad->groupComponents();
}

void MainWindow::on_ungroupButton_clicked()
{
    this->ui->drawingPad->ungroupComponents();
}
