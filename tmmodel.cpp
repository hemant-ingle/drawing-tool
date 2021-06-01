#include "tmmodel.h"

#include<iostream>
using namespace std;
TMModel::TMModel()
{
  viewList=nullptr;
}
void TMModel::add(DrawableComponent *component)
{
    this->components.append(component);
    if(viewList!=nullptr && component->toString()!="Group") viewList->insertItem(0,component->toString());
}

void TMModel::insertAt(int i, DrawableComponent *component)
{
    this->components.insert(i,component);
}

void TMModel::remove(DrawableComponent *component)
{
    this->components.removeAll(component);

}
void TMModel::draw(QPainter *painter)
{
    int i,size;
    size=this->components.size();
    for(i=0;i<size;i++) this->components[i]->draw(painter);
}

int TMModel::processClick(double x, double y)
{
    QList<DrawableComponent *> validComponents;
    int i,size;
    size=this->components.size();
    DrawableComponent *dc;
    for(i=size-1;i>=0 && !this->components[i]->contains(x,y);i--);
    /*for(i=size-1;i>=0;i--)
    {
        dc=this->components[i];
        if(dc->contains(x,y)) validComponents.push_back(dc);
    }
    if(validComponents.size()==0) return -1;
    */
    if(i<0) return -1;
    return i;
}

DrawableComponent *TMModel::getAt(int index)
{
    return this->components[index];
}

void TMModel::clear()
{
    if(viewList!=nullptr) viewList->clear();
    DrawableComponent *dc;
    while(this->components.size()>0)
    {
        dc=this->components.front();
        this->components.pop_front();
        delete dc;
    }
}

QString TMModel::toString()
{
    int i,size;
    size=this->components.size();
    QString str="";
    for(i=0;i<size;i++)
    {
        str.append(this->components[i]->toString());
        if(i<size-1) str.append(",");
    }
    return str;
}

int TMModel::size()
{
    return this->components.size();
}

QListWidget *TMModel::getViewList() const
{
    return viewList;
}

void TMModel::setViewList(QListWidget *value)
{
    viewList = value;
}

void TMModel::write(QJsonObject &jsonObject)
{
    QJsonArray componentsArray;
    for(DrawableComponent *drawableComponent : this->components)
    {
        QJsonObject jsonComponent;
        drawableComponent->write(jsonComponent);
        componentsArray.append(jsonComponent);
    }
    jsonObject["components"]=componentsArray;
    QJsonArray viewListArray;
    for(int i=0;i<this->viewList->count();i++) viewListArray.append(this->viewList->item(i)->text());
    jsonObject["viewList"]=viewListArray;
}

void TMModel::read(const QJsonObject &jsonObject)
{
    if(jsonObject.contains("components") && jsonObject["components"].isArray())
    {
        QJsonArray componentsArray=jsonObject["components"].toArray();
        this->components.clear();
        this->viewList->clear();
        for(int i=0;i<componentsArray.size();i++)
        {
            QJsonObject jsonComponent=componentsArray[i].toObject();
            DrawableComponent *component;
            QString name;
            if(jsonComponent.contains("name") && jsonComponent["name"].isString()) name=jsonComponent["name"].toString();
            if(name=="Line") component=new TMLineComponent();
            if(name=="Circle") component=new TMCircleComponent();
            if(name=="Free Hand Tool") component=new TMFreeHandToolComponent();
            if(name=="Rectangle") component=new TMRectangleComponent();
            if(name=="Group") component=new TMGroupComponent();
            component->read(jsonComponent);
            this->components.append(component);
            this->viewList->insertItem(0,name);
        }
    }
}
