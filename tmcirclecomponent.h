#ifndef TMCIRCLECOMPONENT_H
#define TMCIRCLECOMPONENT_H

#include "drawablecomponent.h"
#include "tmutility.h"
class TMCircleComponent:public DrawableComponent
{
private:
    bool isGrouped;
    int groupId;
    double x1;
    double x2;
    double y1;
    double y2;
    double penWidth;
    QString penColor;
    Qt::PenStyle penStyle;
    Qt::PenCapStyle penCapStyle;
    Qt::PenJoinStyle penJoinStyle;
    QString brushColor;
    Qt::BrushStyle brushStyle;
public:
    TMCircleComponent();
    TMCircleComponent(TMCircleComponent &other);
    virtual void setX1(double value) override;
    virtual double getX1() override;
    virtual void setY1(double value) override;
    virtual double getY1() override;
    virtual void setX2(double value) override;
    virtual double getX2() override;
    virtual void setY2(double value) override;
    virtual double getY2() override;
    virtual void draw(QPainter *painter) override;
    virtual void select(QPainter *painter) override;
    virtual bool contains(double x, double y) override;
    virtual QString toString() override;
    virtual void setIsGrouped(bool value) override;
    virtual bool getIsGrouped() override;
    virtual int getGroupId() override;
    virtual double getSmallestX() override;
    virtual double getSmallestY() override;
    virtual double getLargestX() override;
    virtual double getLargestY() override;
    virtual void move(double changeInX,double changeInY) override;
    virtual void setGroupId(int value) override;
    virtual void write(QJsonObject &jsonObject) override;
    virtual void read(const QJsonObject &jsonObject) override;
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
};

#endif // TMCIRCLECOMPONENT_H
