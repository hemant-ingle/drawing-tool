#include "tmcirclecomponent.h"

TMCircleComponent::TMCircleComponent()
{
    this->isGrouped=false;
    this->groupId=0;
    this->x1=-1;
    this->y1=-1;
    this->x2=-1;
    this->y2=-1;
    this->penWidth=4.00;
    this->penColor=Qt::black;
    this->penStyle=Qt::SolidLine;
    this->penCapStyle=Qt::SquareCap;
    this->penJoinStyle=Qt::BevelJoin;
    this->brushColor=Qt::white;
    this->brushStyle=Qt::NoBrush;
}

void TMCircleComponent::draw(QPainter *painter)
{
    QPoint center;
    center.setX(this->x1);
    center.setY(this->y1);
    int radius=sqrt(pow((this->x1-this->x2),2)+pow((this->y1-this->y2),2));
    QPen pen;
    pen.setWidthF(this->penWidth);
    pen.setColor(QColor(this->penColor));
    pen.setStyle(this->penStyle);
    pen.setCapStyle(this->penCapStyle);
    pen.setJoinStyle(this->penJoinStyle);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(QColor(this->brushColor));
    brush.setStyle(this->brushStyle);
    painter->setBrush(brush);
    painter->drawEllipse(center,radius,radius);
}

void TMCircleComponent::select(QPainter *painter)
{
    QPen pen;
    double penWidth=1.0;
    pen.setWidthF(penWidth);
    painter->setPen(pen);
    QColor color("#2196f3");
    int rectangleSize=10;
    int halfRectangleSize=rectangleSize/2;
    double radius=TMUtility::distanceBetweenTwoPoints(x1,y1,x2,y2);
    painter->fillRect(this->x1-halfRectangleSize,this->y1-halfRectangleSize-radius,rectangleSize,rectangleSize,color);
    painter->fillRect(this->x1-halfRectangleSize+radius,this->y1-halfRectangleSize,rectangleSize,rectangleSize,color);
    painter->fillRect(this->x1-halfRectangleSize,this->y1-halfRectangleSize+radius,rectangleSize,rectangleSize,color);
    painter->fillRect(this->x1-halfRectangleSize-radius,this->y1-halfRectangleSize,rectangleSize,rectangleSize,color);

}

bool TMCircleComponent::contains(double x, double y)
{
    double radius=TMUtility::distanceBetweenTwoPoints(x1,y1,x2,y2);
    double distanceBetweenCenterAndGivenPoint=TMUtility::distanceBetweenTwoPoints(x1,y1,x,y);
    if(distanceBetweenCenterAndGivenPoint<(radius+this->penWidth/2)) return true;
    return false;
}

QString TMCircleComponent::toString()
{
    return "Circle";
}

void TMCircleComponent::setIsGrouped(bool value)
{
    groupId = value;
}

bool TMCircleComponent::getIsGrouped()
{
    return groupId;
}

int TMCircleComponent::getGroupId()
{
    return groupId;
}

double TMCircleComponent::getSmallestX()
{
   int radius=sqrt(pow((this->x1-this->x2),2)+pow((this->y1-this->y2),2));
   return this->x1-radius;
}

double TMCircleComponent::getSmallestY()
{
    int radius=sqrt(pow((this->x1-this->x2),2)+pow((this->y1-this->y2),2));
    return this->y1-radius;
}

double TMCircleComponent::getLargestX()
{
    int radius=sqrt(pow((this->x1-this->x2),2)+pow((this->y1-this->y2),2));
    return this->x1+radius;
}

double TMCircleComponent::getLargestY()
{
    int radius=sqrt(pow((this->x1-this->x2),2)+pow((this->y1-this->y2),2));
    return this->y1+radius;
}

void TMCircleComponent::move(double changeInX, double changeInY)
{
    this->x1=this->x1+changeInX;
    this->y1=this->y1+changeInY;
    this->x2=this->x2+changeInX;
    this->y2=this->y2+changeInY;
}

void TMCircleComponent::setGroupId(int value)
{
    groupId = value;
}

double TMCircleComponent::getX1()
{
    return x1;
}

void TMCircleComponent::setX1(double value)
{
    x1 = value;
}

double TMCircleComponent::getX2()
{
    return x2;
}

void TMCircleComponent::setX2(double value)
{
    x2 = value;
}

double TMCircleComponent::getY1()
{
    return y1;
}

void TMCircleComponent::setY1(double value)
{
    y1 = value;
}

double TMCircleComponent::getY2()
{
    return y2;
}

void TMCircleComponent::setY2(double value)
{
    y2 = value;
}

void TMCircleComponent::write(QJsonObject &jsonObject)
{
    jsonObject["name"]="Circle";
    jsonObject["isGrouped"]=this->isGrouped;
    jsonObject["groupId"]=this->groupId;
    jsonObject["x1"]=this->x1;
    jsonObject["y1"]=this->y1;
    jsonObject["x2"]=this->x2;
    jsonObject["y2"]=this->y2;
    jsonObject["penWidth"]=this->penWidth;
    jsonObject["penColor"]=this->penColor;
    jsonObject["penStyle"]=this->penStyle;
    jsonObject["penCapStyle"]=this->penCapStyle;
    jsonObject["penJoinStyle"]=this->penJoinStyle;
    jsonObject["brushColor"]=this->brushColor;
    jsonObject["brushStyle"]=this->brushStyle;
}

void TMCircleComponent::read(const QJsonObject &jsonObject)
{
    if(jsonObject.contains("isGrouped") && jsonObject["isGrouped"].isBool())  this->isGrouped=jsonObject["isGrouped"].toBool();
    if(jsonObject.contains("groupId"))  this->groupId=jsonObject["groupId"].toInt();
    if(jsonObject.contains("x1") && jsonObject["x1"].isDouble()) this->x1=jsonObject["x1"].toDouble();
    if(jsonObject.contains("y1") && jsonObject["y1"].isDouble()) this->y1=jsonObject["y1"].toDouble();
    if(jsonObject.contains("x2") && jsonObject["x2"].isDouble()) this->x2=jsonObject["x2"].toDouble();
    if(jsonObject.contains("y2") && jsonObject["y2"].isDouble()) this->y2=jsonObject["y2"].toDouble();
    if(jsonObject.contains("penWidth") && jsonObject["penWidth"].isDouble()) this->penWidth=jsonObject["penWidth"].toDouble();
    if(jsonObject.contains("penColor") && jsonObject["penColor"].isString()) this->penColor=jsonObject["penColor"].toString();
    if(jsonObject.contains("penStyle")) this->penStyle=(Qt::PenStyle)jsonObject["penStyle"].toInt();
    if(jsonObject.contains("penCapStyle")) this->penCapStyle=(Qt::PenCapStyle)jsonObject["penCapStyle"].toInt();
    if(jsonObject.contains("penJoinStyle")) this->penJoinStyle=(Qt::PenJoinStyle)jsonObject["penJoinStyle"].toInt();
    if(jsonObject.contains("brushColor")) this->brushColor=jsonObject["brushColor"].toString();
    if(jsonObject.contains("brushStyle")) this->brushStyle=(Qt::BrushStyle)jsonObject["brushStyle"].toInt();
}

double TMCircleComponent::getPenWidth() const
{
    return penWidth;
}

void TMCircleComponent::setPenWidth(double value)
{
    penWidth = value;
}

QString TMCircleComponent::getPenColor() const
{
    return penColor;
}

void TMCircleComponent::setPenColor(const QString &value)
{
    penColor = value;
}

Qt::PenStyle TMCircleComponent::getPenStyle() const
{
    return penStyle;
}

void TMCircleComponent::setPenStyle(const Qt::PenStyle &value)
{
    penStyle = value;
}

Qt::PenCapStyle TMCircleComponent::getPenCapStyle() const
{
    return penCapStyle;
}

void TMCircleComponent::setPenCapStyle(const Qt::PenCapStyle &value)
{
    penCapStyle = value;
}

Qt::PenJoinStyle TMCircleComponent::getPenJoinStyle() const
{
    return penJoinStyle;
}

void TMCircleComponent::setPenJoinStyle(const Qt::PenJoinStyle &value)
{
    penJoinStyle = value;
}

QString TMCircleComponent::getBrushColor() const
{
    return brushColor;
}

void TMCircleComponent::setBrushColor(const QString &value)
{
    brushColor = value;
}

Qt::BrushStyle TMCircleComponent::getBrushStyle() const
{
    return brushStyle;
}

void TMCircleComponent::setBrushStyle(const Qt::BrushStyle &value)
{
    brushStyle = value;
}
