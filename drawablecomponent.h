#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include<QMessageBox>

#include<QPainter>
#include<QJsonObject>
#include<math.h>

#include<iostream>
using namespace std;
class DrawableComponent
{
public:
    virtual void setX1(double value)=0;
    virtual double getX1()=0;
    virtual void setY1(double value)=0;
    virtual double getY1()=0;
    virtual void setX2(double value)=0;
    virtual double getX2()=0;
    virtual void setY2(double value)=0;
    virtual double getY2()=0;
    virtual void draw(QPainter *painter)=0;
    virtual void select(QPainter *painter)=0;
    virtual bool contains(double x,double y)=0;
    virtual QString toString()=0;
    virtual void setIsGrouped(bool value)=0;
    virtual bool getIsGrouped()=0;
    virtual int getGroupId()=0;
    virtual void setGroupId(int value)=0;
    virtual double getSmallestX()=0;
    virtual double getSmallestY()=0;
    virtual double getLargestX()=0;
    virtual double getLargestY()=0;
    virtual void move(double changeInX,double changeInY)=0;
    virtual void write(QJsonObject &jsonObject)=0;
    virtual void read(const QJsonObject &jsonObject)=0;
};

#endif // DRAWABLECOMPONENT_H
