#ifndef TMMODEL_H
#define TMMODEL_H

#include "drawablecomponent.h"
#include <QList>
#include <QPair>
#include <QPainter>
#include <QListWidget>
#include <tmlinecomponent.h>
#include <tmrectanglecomponent.h>
#include <tmcirclecomponent.h>
#include <tmfreehandtoolcomponent.h>
#include <tmgroupcomponent.h>
#include <QJsonArray>
#include <QJsonObject>
class TMModel
{
private:
QList<DrawableComponent *> components;
QListWidget *viewList;
public:
    TMModel();
    void add(DrawableComponent *component);
    void insertAt(int i,DrawableComponent *component);
    void remove(DrawableComponent *component);
    void draw(QPainter *painter);
    int processClick(double x,double y);
    DrawableComponent *getAt(int index);
    void clear();
    QString toString();
    int size();
    QListWidget *getViewList() const;
    void setViewList(QListWidget *value);
    void write(QJsonObject &jsonObject);
    void read(const QJsonObject &jsonObject);
};

#endif // TMMODEL_H
