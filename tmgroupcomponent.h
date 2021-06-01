#ifndef TMGROUPCOMPONENT_H
#define TMGROUPCOMPONENT_H

#include "drawablecomponent.h"
#include <QJsonArray>
#include <QJsonObject>
#include "tmlinecomponent.h"
#include "tmfreehandtoolcomponent.h"
#include "tmcirclecomponent.h"
#include "tmrectanglecomponent.h"
class TMGroupComponent:public DrawableComponent
{
private:
    bool isGrouped;
    int groupId;
    double x1;
    double y1;
    double x2;
    double y2;
    QList<QPair<int, DrawableComponent *> *> childComponents;
public:
    TMGroupComponent();
    virtual void setX1(double value)override;
    virtual double getX1() override;
    virtual void setY1(double value) override;
    virtual double getY1() override;
    virtual void setX2(double value) override;
    virtual double getX2() override;
    virtual void setY2(double value) override;
    virtual double getY2() override;
    virtual void draw(QPainter *painter) override;
    virtual void select(QPainter *painter) override;
    virtual bool contains(double x,double y) override;
    virtual QString toString() override;
    virtual double getSmallestX() override;
    virtual double getSmallestY() override;
    virtual double getLargestX() override;
    virtual double getLargestY() override;
    virtual void move(double changeInX,double changeInY) override;
    virtual void write(QJsonObject &jsonObject) override;
    virtual void read(const QJsonObject &jsonObject) override;
    virtual void setIsGrouped(bool value) override;
    virtual bool getIsGrouped() override;
    virtual int getGroupId() override;
    virtual void setGroupId(int value) override;
    QList<QPair<int, DrawableComponent *> *> getChildComponents() const;
    void setChildComponents(const QList<QPair<int, DrawableComponent *> *> &value);
    int getChildCount();
    void setPoints();
    void clearChildComponents();
};

#endif // TMGROUPCOMPONENT_H
