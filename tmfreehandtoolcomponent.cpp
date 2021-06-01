#include "tmfreehandtoolcomponent.h"

#include<iostream>
using namespace std;

TMFreeHandToolComponent::TMFreeHandToolComponent()
{
    this->isGrouped=false;
    this->groupId=0;
    this->x1=-1;
    this->y1=-1;
    this->x2=-1;
    this->y2=-1;
    this->points=nullptr;
    this->pointCount=0;
    this->penWidth=4.00;
    this->penColor=Qt::black;
    this->penStyle=Qt::SolidLine;
    this->penCapStyle=Qt::SquareCap;
    this->penJoinStyle=Qt::BevelJoin;
    this->brushColor=Qt::white;
    this->brushStyle=Qt::NoBrush;
}

TMFreeHandToolComponent::~TMFreeHandToolComponent()
{
    delete this->points;
}

void TMFreeHandToolComponent::draw(QPainter *painter)
{
    QPainterPath path;
    path.moveTo(this->x1,this->y1);
    for(int i=0;i<this->pointCount;i++) path.lineTo(this->points[i].x(),this->points[i].y());
    path.lineTo(this->x2,this->y2);
    QPen pen;
    pen.setWidthF(this->penWidth);
    pen.setColor(QColor(this->penColor));
    pen.setStyle(this->penStyle);
    pen.setCapStyle(this->penCapStyle);
    pen.setJoinStyle(this->penJoinStyle);
    painter->setPen(pen);
    painter->drawPath(path);
}

void TMFreeHandToolComponent::select(QPainter *painter)
{
    QPen pen;
    double penWidth=1.0;
    pen.setWidthF(penWidth);
    painter->setPen(pen);
    int rectangleSize=10;
    int halfRectangleSize=rectangleSize/2;
    QColor color("#2196f3");
    painter->fillRect(this->x1-halfRectangleSize,this->y1-halfRectangleSize,rectangleSize,rectangleSize,color);
    painter->fillRect(this->x2-halfRectangleSize,this->y2-halfRectangleSize,rectangleSize,rectangleSize,color);
}

bool TMFreeHandToolComponent::contains(double x, double y)
{
    double distanceBetweenLineAndPoint;
    double x1,y1,x2,y2,g;
    x1=this->x1;
    y1=this->y1;
    for(int i=1;i<this->pointCount;i++)
    {
        x2=this->points[i].x();
        y2=this->points[i].y();
        distanceBetweenLineAndPoint=(((fabs(((y2-y1)*x)-((x2-x1)*y)+(x2*y1)-(y2*x1)))/(sqrt((pow((y2-y1),2))+(pow((x2-x1),2))))));

        if(x2<x1)
        {
            g=x1;
            x1=x2;
            x2=g;
        }
        if(y2<y1)
        {
            g=y1;
            y1=y2;
            y2=g;
        }
        if((distanceBetweenLineAndPoint<=this->penWidth) && (x>=x1 && x<=x2 && y>=y1 && y<=y2)) return true;
        x1=x2;
        y1=y2;
    }
    return false;
}

QString TMFreeHandToolComponent::toString()
{
    return "Free Hand Tool";
}

double TMFreeHandToolComponent::getSmallestX()
{
    int x;
    int sX=this->x1;
    for(int i=0;i<this->pointCount;i++)
    {
        x=this->points[i].x();
        if(sX>x) sX=x;
    }
    if(sX>this->x2) sX=this->x2;
    return sX;
}

double TMFreeHandToolComponent::getSmallestY()
{
    int y;
    int sY=this->y1;
    for(int i=0;i<this->pointCount;i++)
    {
        y=this->points[i].y();
        if(sY>y) sY=y;
    }
    if(sY>this->y2) sY=this->y2;
    return sY;
}

double TMFreeHandToolComponent::getLargestX()
{
    int x;
    int lX=this->x1;
    for(int i=0;i<this->pointCount;i++)
    {
        x=this->points[i].x();
        if(lX<x) lX=x;
    }
    if(lX<this->x2) lX=this->x2;
    return lX;
}

double TMFreeHandToolComponent::getLargestY()
{
    int y;
    int lY=this->y1;
    for(int i=0;i<this->pointCount;i++)
    {
        y=this->points[i].y();
        if(lY<y) lY=y;
    }
    if(lY<this->y2) lY=this->y2;
    return lY;
}

void TMFreeHandToolComponent::move(double changeInX, double changeInY)
{
    for(int i=0;i<this->pointCount;i++)
    {
       this->points[i].setX(this->points[i].x()+changeInX);
       this->points[i].setY(this->points[i].y()+changeInY);
    }
    this->x1=this->x1+changeInX;
    this->y1=this->y1+changeInY;
    this->x2=this->x2+changeInX;
    this->y2=this->y2+changeInY;
}

void TMFreeHandToolComponent::write(QJsonObject &jsonObject)
{
    jsonObject["isGrouped"]=this->isGrouped;
    jsonObject["groupId"]=this->groupId;
    jsonObject["name"]="Free Hand Tool";
    jsonObject["x1"]=this->x1;
    jsonObject["y1"]=this->y1;
    jsonObject["x2"]=this->x2;
    jsonObject["y2"]=this->y2;
    QJsonArray jsonPoints;
    for(int i=0;i<this->pointCount;i++)
    {
        QJsonObject jsonPoint;
        jsonPoint["x"]=(double)this->points[i].x();
        jsonPoint["y"]=(double)this->points[i].y();
        jsonPoints.append(jsonPoint);
    }
    jsonObject["points"]=jsonPoints;
    jsonObject["pointCount"]=this->pointCount;
    jsonObject["penWidth"]=this->penWidth;
    jsonObject["penColor"]=this->penColor;
    jsonObject["penStyle"]=this->penStyle;
    jsonObject["penCapStyle"]=this->penCapStyle;
    jsonObject["penJoinStyle"]=this->penJoinStyle;
    jsonObject["brushColor"]=this->brushColor;
    jsonObject["brushStyle"]=this->brushStyle;
}

void TMFreeHandToolComponent::read(const QJsonObject &jsonObject)
{
    if(jsonObject.contains("isGrouped") && jsonObject["isGrouped"].isBool())  this->isGrouped=jsonObject["isGrouped"].toBool();
    if(jsonObject.contains("groupId"))  this->groupId=jsonObject["groupId"].toInt();
    if(jsonObject.contains("x1") && jsonObject["x1"].isDouble()) this->x1=jsonObject["x1"].toDouble();
    if(jsonObject.contains("y1") && jsonObject["y1"].isDouble()) this->y1=jsonObject["y1"].toDouble();
    if(jsonObject.contains("x2") && jsonObject["x2"].isDouble()) this->x2=jsonObject["x2"].toDouble();
    if(jsonObject.contains("y2") && jsonObject["y2"].isDouble()) this->y2=jsonObject["y2"].toDouble();
    if(jsonObject.contains("pointCount")) this->pointCount=jsonObject["pointCount"].toInt();
    if(jsonObject.contains("points") && jsonObject["points"].isArray())
    {
        QJsonArray jsonPoints=jsonObject["points"].toArray();
        int jsonPointsSize=jsonPoints.size();
        this->points=new QPointF[jsonPointsSize];
        for(int i=0;i<jsonPointsSize;i++)
        {
            QJsonObject jsonPoint=jsonPoints[i].toObject();
            QPointF pointF;
            if(jsonPoint.contains("x") && jsonPoint["x"].isDouble())
            {
                double x=jsonPoint["x"].toDouble();
                pointF.setX(x);
            }
            if(jsonPoint.contains("y") && jsonPoint["y"].isDouble())
            {
                double y=jsonPoint["y"].toDouble();
                pointF.setY(y);
            }
            this->points[i]=pointF;
        }
    }
    if(jsonObject.contains("penWidth") && jsonObject["penWidth"].isDouble()) this->penWidth=jsonObject["penWidth"].toDouble();
    if(jsonObject.contains("penColor") && jsonObject["penColor"].isString()) this->penColor=jsonObject["penColor"].toString();
    if(jsonObject.contains("penStyle")) this->penStyle=(Qt::PenStyle)jsonObject["penStyle"].toInt();
    if(jsonObject.contains("penCapStyle")) this->penCapStyle=(Qt::PenCapStyle)jsonObject["penCapStyle"].toInt();
    if(jsonObject.contains("penJoinStyle")) this->penJoinStyle=(Qt::PenJoinStyle)jsonObject["penJoinStyle"].toInt();
    if(jsonObject.contains("brushColor")) this->brushColor=jsonObject["brushColor"].toString();
    if(jsonObject.contains("brushStyle")) this->brushStyle=(Qt::BrushStyle)jsonObject["brushStyle"].toInt();
}

void TMFreeHandToolComponent::setX1(double value)
{
    this->x1=value;
}

double TMFreeHandToolComponent::getX1()
{
    return this->x1;
}

void TMFreeHandToolComponent::setY1(double value)
{
    this->y1=value;
}

double TMFreeHandToolComponent::getY1()
{
    return this->y1;
}

void TMFreeHandToolComponent::setX2(double value)
{
    this->x2=value;
}

double TMFreeHandToolComponent::getX2()
{
    return this->x2;
}

void TMFreeHandToolComponent::setY2(double value)
{
    this->y2=value;
}

double TMFreeHandToolComponent::getY2()
{
    return this->y2;
}

QList<QPointF> TMFreeHandToolComponent::getPointsList() const
{
    QList<QPointF> pointsList;
    for(int i=0;i<pointCount;i++) pointsList.append(this->points[i]);
    return pointsList;
}

QPointF TMFreeHandToolComponent::getPointAt(int index) const
{
    return this->points[index];
}
QPointF TMFreeHandToolComponent::removePointAt(int index)
{
    int pointCount=this->pointCount-1;
    QPointF *points=new QPointF[pointCount];
    int i,j;
    QPointF removedPoint;
    for(i=0,j=0;i<pointCount;i++,j++)
    {
        if(i==index)
        {
            removedPoint.setX(this->points[i].x());
            removedPoint.setY(this->points[i].y());
            j--;
        }
        points[j].setX(this->points[i].x());
        points[j].setY(this->points[i].y());
    }
    delete [] this->points;
    this->pointCount=pointCount;
    this->points=points;
    return removedPoint;
}
void TMFreeHandToolComponent::setPointAt(int index,QPointF value)
{
    QPointF *points=new QPointF[this->pointCount];
    int i;
    for(i=0;i<this->pointCount;i++)
    {
        if(i==index)
        {
            points[i].setX(value.x());
            points[i].setY(value.y());
            continue;
        }
        points[i].setX(this->points[i].x());
        points[i].setY(this->points[i].y());
    }
    delete [] this->points;
    this->points=points;
}

void TMFreeHandToolComponent::addPoint(QPointF value)
{
    int pointCount=this->pointCount+1;
    QPointF *points=new QPointF[pointCount];
    int i;
    for(i=0;i<pointCount-1;i++)
    {
        points[i].setX(this->points[i].x());
        points[i].setY(this->points[i].y());
    }
    points[i].setX(value.x());
    points[i].setY(value.y());
    delete [] this->points;
    this->pointCount=pointCount;
    this->points=points;
}

int TMFreeHandToolComponent::getPointCount() const
{
    return pointCount;
}

void TMFreeHandToolComponent::setPointCount(int value)
{
    pointCount = value;
}

double TMFreeHandToolComponent::getPenWidth() const
{
    return penWidth;
}

void TMFreeHandToolComponent::setPenWidth(double value)
{
    penWidth = value;
}

QString TMFreeHandToolComponent::getPenColor() const
{
    return penColor;
}

void TMFreeHandToolComponent::setPenColor(const QString &value)
{
    penColor = value;
}

Qt::PenStyle TMFreeHandToolComponent::getPenStyle() const
{
    return penStyle;
}

void TMFreeHandToolComponent::setPenStyle(const Qt::PenStyle &value)
{
    penStyle = value;
}

Qt::PenCapStyle TMFreeHandToolComponent::getPenCapStyle() const
{
    return penCapStyle;
}

void TMFreeHandToolComponent::setPenCapStyle(const Qt::PenCapStyle &value)
{
    penCapStyle = value;
}

Qt::PenJoinStyle TMFreeHandToolComponent::getPenJoinStyle() const
{
    return penJoinStyle;
}

void TMFreeHandToolComponent::setPenJoinStyle(const Qt::PenJoinStyle &value)
{
    penJoinStyle = value;
}

QString TMFreeHandToolComponent::getBrushColor() const
{
    return brushColor;
}

void TMFreeHandToolComponent::setBrushColor(const QString &value)
{
    brushColor = value;
}

Qt::BrushStyle TMFreeHandToolComponent::getBrushStyle() const
{
    return brushStyle;
}

void TMFreeHandToolComponent::setBrushStyle(const Qt::BrushStyle &value)
{
    brushStyle = value;
}

int TMFreeHandToolComponent::getGroupId()
{
    return groupId;
}

void TMFreeHandToolComponent::setGroupId(int value)
{
    groupId = value;
}

void TMFreeHandToolComponent::setIsGrouped(bool value)
{
    groupId = value;
}

bool TMFreeHandToolComponent::getIsGrouped()
{
    return groupId;
}
