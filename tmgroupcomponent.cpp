#include "tmgroupcomponent.h"

TMGroupComponent::TMGroupComponent()
{
    this->isGrouped=false;
    this->groupId=0;
    this->x1=-1;
    this->y1=-1;
    this->x2=-1;
    this->y2=-1;
}

void TMGroupComponent::draw(QPainter *painter)
{
    for(int i=0;i<childComponents.size();i++) childComponents[i]->second->draw(painter);
}

void TMGroupComponent::select(QPainter *painter)
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
    pen.setColor(color);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawRect(QRectF((this->x1<this->x2)?this->x1:this->x2,(this->y1<this->y2)?this->y1:this->y2,abs(this->x1-this->x2),abs(this->y1-this->y2)));
}

bool TMGroupComponent::contains(double x, double y)
{
   int i,size;
   size=childComponents.size();
   for(i=0;i<size && !childComponents[i]->second->contains(x,y);i++);
   if(i<size) return true;
   return false;
}

QString TMGroupComponent::toString()
{
    return "Group";
}

double TMGroupComponent::getSmallestX()
{
    return (this->x1<this->x2) ? this->x1 : this->x2;
}

double TMGroupComponent::getSmallestY()
{
    return (this->y1<this->y2) ? this->y1 : this->y2;
}

double TMGroupComponent::getLargestX()
{
    return (this->x1>this->x2) ? this->x1 : this->x2;
}

double TMGroupComponent::getLargestY()
{
    return (this->y1>this->y2) ? this->y1 : this->y2;
}

void TMGroupComponent::move(double changeInX, double changeInY)
{
    int size=this->childComponents.size();
    for(int i=0;i<size;i++) childComponents[i]->second->move(changeInX,changeInY);
    this->x1=this->x1+changeInX;
    this->y1=this->y1+changeInY;
    this->x2=this->x2+changeInX;
    this->y2=this->y2+changeInY;
}

void TMGroupComponent::setX1(double value)
{
    this->x1=value;
}

double TMGroupComponent::getX1()
{
    return this->x1;
}

void TMGroupComponent::setY1(double value)
{
    this->y1=value;
}

double TMGroupComponent::getY1()
{
    return this->y1;
}

void TMGroupComponent::setX2(double value)
{
    this->x2=value;
}

double TMGroupComponent::getX2()
{
    return this->x2;
}

void TMGroupComponent::setY2(double value)
{
    this->y2=value;
}

double TMGroupComponent::getY2()
{
    return this->y2;
}

void TMGroupComponent::write(QJsonObject &jsonObject)
{
    jsonObject["isGrouped"]=this->isGrouped;
    jsonObject["groupId"]=this->groupId;
    jsonObject["name"]="Group";
    jsonObject["x1"]=this->x1;
    jsonObject["y1"]=this->y1;
    jsonObject["x2"]=this->x2;
    jsonObject["y2"]=this->y2;
    QJsonArray childComponentsArray;
    for(QPair<int,DrawableComponent *> *pair : this->childComponents)
    {
        QJsonObject jsonPair;
        jsonPair["first"]=pair->first;
        QJsonObject jsonComponent;
        pair->second->write(jsonComponent);
        jsonPair["second"]=jsonComponent;
        childComponentsArray.append(jsonPair);
    }
    jsonObject["childComponents"]=childComponentsArray;
}

void TMGroupComponent::read(const QJsonObject &jsonObject)
{
    if(jsonObject.contains("isGrouped") && jsonObject["isGrouped"].isBool())  this->isGrouped=jsonObject["isGrouped"].toBool();
    if(jsonObject.contains("groupId"))  this->groupId=jsonObject["groupId"].toInt();
    if(jsonObject.contains("x1") && jsonObject["x1"].isDouble()) this->x1=jsonObject["x1"].toDouble();
    if(jsonObject.contains("y1") && jsonObject["y1"].isDouble()) this->y1=jsonObject["y1"].toDouble();
    if(jsonObject.contains("x2") && jsonObject["x2"].isDouble()) this->x2=jsonObject["x2"].toDouble();
    if(jsonObject.contains("y2") && jsonObject["y2"].isDouble()) this->y2=jsonObject["y2"].toDouble();
    if(jsonObject.contains("childComponents") && jsonObject["childComponents"].isArray())
    {
        QJsonArray childComponentsArray=jsonObject["childComponents"].toArray();
        this->childComponents.clear();
        for(int i=0;i<childComponentsArray.size();i++)
        {
            QJsonObject jsonPair=childComponentsArray[i].toObject();
            QPair<int,DrawableComponent *> *pair=new QPair<int,DrawableComponent *>;
            int index;
            if(jsonPair.contains("first"))
            {
                index=jsonPair["first"].toInt();
                pair->first=index;
            }
            QJsonObject jsonComponent;
            if(jsonPair.contains("second") && jsonPair["second"].isObject()) jsonComponent=jsonPair["second"].toObject();
            DrawableComponent *component;
            QString name;
            if(jsonComponent.contains("name") && jsonComponent["name"].isString()) name=jsonComponent["name"].toString();
            if(name=="Line") component=new TMLineComponent();
            if(name=="Circle") component=new TMCircleComponent();
            if(name=="Free Hand Tool") component=new TMFreeHandToolComponent();
            if(name=="Rectangle") component=new TMRectangleComponent();
            if(name=="Group") component=new TMGroupComponent();
            component->read(jsonComponent);
            pair->second=component;
            this->childComponents.append(pair);
        }
    }
}

void TMGroupComponent::setIsGrouped(bool value)
{
    isGrouped = value;
}

bool TMGroupComponent::getIsGrouped()
{
    return isGrouped;
}

int TMGroupComponent::getGroupId()
{
    return groupId;
}

void TMGroupComponent::setGroupId(int value)
{
    groupId = value;
}

QList<QPair<int, DrawableComponent *> *> TMGroupComponent::getChildComponents() const
{
    return childComponents;
}

void TMGroupComponent::setChildComponents(const QList<QPair<int, DrawableComponent *> *> &value)
{
    childComponents = value;
    if(this->childComponents.size()>0) this->setPoints();
}

int TMGroupComponent::getChildCount()
{
    return this->childComponents.count();
}

void TMGroupComponent::setPoints()
{
    int padding=20;
    DrawableComponent *currentComponent;
    /*
     * c => current
     * s/S => smallest
     * l/L => largest
     * X => x coordinate
     * Y => y coordinate
     */
    int sX,sY,lX,lY,cSX,cSY,cLX,cLY;
    currentComponent=this->childComponents[0]->second;
    sX=currentComponent->getSmallestX();
    sY=currentComponent->getSmallestY();
    lX=currentComponent->getLargestX();
    lY=currentComponent->getLargestY();
    for(int i=1;i<this->childComponents.size();i++)
    {
        currentComponent=childComponents[i]->second;
        cSX=currentComponent->getSmallestX();
        cSY=currentComponent->getSmallestY();
        cLX=currentComponent->getLargestX();
        cLY=currentComponent->getLargestY();
        if(sX>cSX) sX=cSX;
        if(sY>cSY) sY=cSY;
        if(lX<cLX) lX=cLX;
        if(lY<cLY) lY=cLY;

    }
    this->x1=sX-padding;
    this->y1=sY-padding;
    this->x2=lX+padding;
    this->y2=lY+padding;
}

void TMGroupComponent::clearChildComponents()
{
    this->childComponents.clear();
}
