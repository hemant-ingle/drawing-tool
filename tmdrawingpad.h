#ifndef TMDRAWINGPAD_H
#define TMDRAWINGPAD_H

#include<QFrame>
#include<QPainter>
#include<QMouseEvent>
#include<QList>
#include<QListWidget>
#include "tmmodel.h"
#include "tmutility.h"
#include "drawablecomponent.h"
#include "tmlinecomponent.h"
#include "tmrectanglecomponent.h"
#include "tmfreehandtoolcomponent.h"
#include "tmcirclecomponent.h"
#include "tmgroupcomponent.h"
class TMDrawingPad:public QFrame
{
private:
    TMModel *model;
    DrawableComponent *currentComponent;
    QPointF localPoint;
    int nextGroupId;
    Mode mode;
    bool isControlKeyPressed;
    QMap<int,DrawableComponent *> selectedComponents;
    double penWidth;
    QString penColor;
    Qt::PenStyle penStyle;
    Qt::PenCapStyle penCapStyle;
    Qt::PenJoinStyle penJoinStyle;
    QString brushColor;
    Qt::BrushStyle brushStyle;
    QListWidget *listWidget;
public:
    TMDrawingPad(QWidget *parent=nullptr);
    ~TMDrawingPad();
    virtual void paintEvent(QPaintEvent *paintEvent) override;
    virtual void mousePressEvent(QMouseEvent *mouseEvent) override;
    virtual void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent *mouseEvent) override;
    void selectLineTool();
    void selectRectangleTool();
    void selectFreeHandTool();
    void selectCircleTool();
    void selectPickTool();
    void selectClearTool();
    void groupComponents();
    void ungroupComponents();
    void selectComponent(int index);
    void setViewComponent(QListWidget *listWidget);
    void clearSelection();
    Mode correctSelectionModeFinder();
    TMModel *getModel() const;
    void setModel(TMModel *value);
    double getPenWidth() const;
    void setPenWidth(double value);
    QString getPenColor() const;
    void setPenColor(const QString &value);
    Qt::PenStyle getPenStyle() const;
    void setPenStyle(const Qt::PenStyle &value);
    Qt::PenCapStyle getPenCapStyle() const;
    void setPenCapStyle(const Qt::PenCapStyle &value);
    Qt::PenJoinStyle getPenJoinStyle() const;
    void setPenJoinStyle(const Qt::PenJoinStyle &value);
    QString getBrushColor() const;
    void setBrushColor(const QString &value);
    Qt::BrushStyle getBrushStyle() const;
    void setBrushStyle(const Qt::BrushStyle &value);
    Mode getMode() const;
    void setMode(const Mode &value);
    bool getIsControlKeyPressed() const;
    void setIsControlKeyPressed(bool value);
};

#endif // TMDRAWINGPAD_H
