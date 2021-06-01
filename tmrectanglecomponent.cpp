#include "tmrectanglecomponent.h"

TMRectangleComponent::TMRectangleComponent()
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

void TMRectangleComponent::draw(QPainter *painter)
{
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
    painter->drawRect(QRectF((this->x1<this->x2)?this->x1:this->x2,(this->y1<this->y2)?this->y1:this->y2,abs(this->x1-this->x2),abs(this->y1-this->y2)));
}

void TMRectangleComponent::select(QPainter *painter)
{
    QPen pen;
    double penWidth=1.0;
    pen.setWidthF(penWidth);
    painter->setPen(pen);
    QColor color("#2196f3");
    int rectangleSize=10;
    int halfRectangleSize=rectangleSize/2;
    painter->fillRect(this->x1-halfRectangleSize,this->y1-halfRectangleSize,rectangleSize,rectangleSize,color);
    painter->fillRect(this->x2-halfRectangleSize,this->y1-halfRectangleSize,rectangleSize,rectangleSize,color);
    painter->fillRect(this->x2-halfRectangleSize,this->y2-halfRectangleSize,rectangleSize,rectangleSize,color);
    painter->fillRect(this->x1-halfRectangleSize,this->y2-halfRectangleSize,rectangleSize,rectangleSize,color);
}

bool TMRectangleComponent::contains(double x, double y)
{
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
   if(x>=x1 && x<=x2 && y>=y1 && y<=y2) return true;
   return false;

}

QString TMRectangleComponent::toString()
{
    return "Rectangle";
}

double TMRectangleComponent::getSmallestX()
{
    return (this->x1<this->x2) ? this->x1 : this->x2;
}

double TMRectangleComponent::getSmallestY()
{
    return (this->y1<this->y2) ? this->y1 : this->y2;
}

double TMRectangleComponent::getLargestX()
{
    return (this->x1>this->x2) ? this->x1 : this->x2;
}

double TMRectangleComponent::getLargestY()
{
    return (this->y1>this->y2) ? this->y1 : this->y2;
}

void TMRectangleComponent::move(double changeInX, double changeInY)
{
    this->x1=this->x1+changeInX;
    this->y1=this->y1+changeInY;
    this->x2=this->x2+changeInX;
    this->y2=this->y2+changeInY;
}

void TMRectangleComponent::write(QJsonObject &jsonObject)
{
    jsonObject["isGrouped"]=this->isGrouped;
    jsonObject["groupId"]=this->groupId;
    jsonObject["name"]="Rectangle";
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

void TMRectangleComponent::read(const QJsonObject &jsonObject)
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

void TMRectangleComponent::setX1(double value)
{
    this->x1=value;
}

double TMRectangleComponent::getX1()
{
    return this->x1;
}

void TMRectangleComponent::setY1(double value)
{
    this->y1=value;
}

double TMRectangleComponent::getY1()
{
    return this->y1;
}

void TMRectangleComponent::setX2(double value)
{
    this->x2=value;
}

double TMRectangleComponent::getX2()
{
    return this->x2;
}

void TMRectangleComponent::setY2(double value)
{
    this->y2=value;
}

double TMRectangleComponent::getY2()
{
    return this->y2;
}

double TMRectangleComponent::getPenWidth() const
{
    return penWidth;
}

void TMRectangleComponent::setPenWidth(double value)
{
    penWidth = value;
}

QString TMRectangleComponent::getPenColor() const
{
    return penColor;
}

void TMRectangleComponent::setPenColor(const QString &value)
{
    penColor = value;
}

Qt::PenStyle TMRectangleComponent::getPenStyle() const
{
    return penStyle;
}

void TMRectangleComponent::setPenStyle(const Qt::PenStyle &value)
{
    penStyle = value;
}

Qt::PenCapStyle TMRectangleComponent::getPenCapStyle() const
{
    return penCapStyle;
}

void TMRectangleComponent::setPenCapStyle(const Qt::PenCapStyle &value)
{
    penCapStyle = value;
}

Qt::PenJoinStyle TMRectangleComponent::getPenJoinStyle() const
{
    return penJoinStyle;
}

void TMRectangleComponent::setPenJoinStyle(const Qt::PenJoinStyle &value)
{
    penJoinStyle = value;
}

QString TMRectangleComponent::getBrushColor() const
{
    return brushColor;
}

void TMRectangleComponent::setBrushColor(const QString &value)
{
    brushColor = value;
}

Qt::BrushStyle TMRectangleComponent::getBrushStyle() const
{
    return brushStyle;
}

void TMRectangleComponent::setBrushStyle(const Qt::BrushStyle &value)
{
    brushStyle = value;
}

void TMRectangleComponent::setIsGrouped(bool value)
{
    groupId = value;
}

bool TMRectangleComponent::getIsGrouped()
{
    return groupId;
}

int TMRectangleComponent::getGroupId()
{
    return groupId;
}

void TMRectangleComponent::setGroupId(int value)
{
    groupId = value;
}
