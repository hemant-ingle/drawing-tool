#include "tmlinecomponent.h"

TMLineComponent::TMLineComponent()
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
}

void TMLineComponent::draw(QPainter *painter)
{
    QPen pen;
    pen.setWidthF(this->penWidth);
    pen.setColor(QColor(this->penColor));
    pen.setStyle(this->penStyle);
    pen.setCapStyle(this->penCapStyle);
    pen.setJoinStyle(this->penJoinStyle);
    painter->setPen(pen);painter->drawLine(QPointF(this->x1,this->y1),QPointF(this->x2,this->y2));
}

void TMLineComponent::select(QPainter *painter)
{
    QPen pen;
    double penWidth=1.0;
    double twoTimesPenWidth=penWidth*2;
    pen.setWidthF(penWidth);
    painter->setPen(pen);
    int rectangleSize=10;
    int halfRectangleSize=rectangleSize/2;
    QColor color("#2196f3");
    painter->fillRect(this->x1-halfRectangleSize,this->y1-halfRectangleSize,rectangleSize,rectangleSize,color);
    painter->fillRect(this->x2-halfRectangleSize,this->y2-halfRectangleSize,rectangleSize,rectangleSize,color);
}

bool TMLineComponent::contains(double x, double y)
{

    double distanceBetweenLineAndPoint=(((fabs(((this->y2-this->y1)*x)-((this->x2-this->x1)*y)+(this->x2*this->y1)-(this->y2*this->x1)))/(sqrt((pow((this->y2-this->y1),2))+(pow((this->x2-this->x1),2))))));
    double x1,y1,x2,y2,g;
    x1=this->x1;
    y1=this->y1;
    x2=this->x2;
    y2=this->y2;
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
    return false;
}

QString TMLineComponent::toString()
{
    return "Line";
}

double TMLineComponent::getSmallestX()
{
    return (this->x1<this->x2) ? this->x1 : this->x2;
}

double TMLineComponent::getSmallestY()
{
    return (this->y1<this->y2) ? this->y1 : this->y2;
}

double TMLineComponent::getLargestX()
{
    return (this->x1>this->x2) ? this->x1 : this->x2;
}

double TMLineComponent::getLargestY()
{
    return (this->y1>this->y2) ? this->y1 : this->y2;
}

void TMLineComponent::move(double changeInX, double changeInY)
{
    this->x1=this->x1+changeInX;
    this->y1=this->y1+changeInY;
    this->x2=this->x2+changeInX;
    this->y2=this->y2+changeInY;
}

void TMLineComponent::write(QJsonObject &jsonObject)
{
    jsonObject["isGrouped"]=this->isGrouped;
    jsonObject["groupId"]=this->groupId;
    jsonObject["name"]="Line";
    jsonObject["x1"]=this->x1;
    jsonObject["y1"]=this->y1;
    jsonObject["x2"]=this->x2;
    jsonObject["y2"]=this->y2;
    jsonObject["penWidth"]=this->penWidth;
    jsonObject["penColor"]=this->penColor;
    jsonObject["penStyle"]=this->penStyle;
    jsonObject["penCapStyle"]=this->penCapStyle;
    jsonObject["penJoinStyle"]=this->penJoinStyle;
}

void TMLineComponent::read(const QJsonObject &jsonObject)
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
}

double TMLineComponent::getX1()
{
    return x1;
}

void TMLineComponent::setX1(double value)
{
    x1 = value;
}

double TMLineComponent::getX2()
{
    return x2;
}

void TMLineComponent::setX2(double value)
{
    x2 = value;
}

double TMLineComponent::getY1()
{
    return y1;
}

void TMLineComponent::setY1(double value)
{
    y1 = value;
}

double TMLineComponent::getY2()
{
    return y2;
}

void TMLineComponent::setY2(double value)
{
    y2 = value;
}

double TMLineComponent::getPenWidth() const
{
    return penWidth;
}

void TMLineComponent::setPenWidth(double value)
{
    penWidth = value;
}

QString TMLineComponent::getPenColor() const
{
    return penColor;
}

void TMLineComponent::setPenColor(const QString &value)
{
    penColor = value;
}

Qt::PenStyle TMLineComponent::getPenStyle() const
{
    return penStyle;
}

void TMLineComponent::setPenStyle(const Qt::PenStyle &value)
{
    penStyle = value;
}

Qt::PenCapStyle TMLineComponent::getPenCapStyle() const
{
    return penCapStyle;
}

void TMLineComponent::setPenCapStyle(const Qt::PenCapStyle &value)
{
    penCapStyle = value;
}

Qt::PenJoinStyle TMLineComponent::getPenJoinStyle() const
{
    return penJoinStyle;
}

void TMLineComponent::setPenJoinStyle(const Qt::PenJoinStyle &value)
{
    penJoinStyle = value;
}

int TMLineComponent::getGroupId()
{
    return groupId;
}

void TMLineComponent::setGroupId(int value)
{
    groupId = value;
}

void TMLineComponent::setIsGrouped(bool value)
{
    groupId = value;
}

bool TMLineComponent::getIsGrouped()
{
    return groupId;
}
