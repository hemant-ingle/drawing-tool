#include "tmdrawingpad.h"

#include<iostream>
using namespace std;

TMDrawingPad::TMDrawingPad(QWidget *parent):QFrame(parent)
{
    this->model=new TMModel();
    this->currentComponent=nullptr;
    this->mode=Mode::NONE;
    this->isControlKeyPressed=false;
    this->nextGroupId=1;
    this->penWidth=4.00;
    this->penColor=Qt::black;
    this->penStyle=Qt::SolidLine;
    this->penCapStyle=Qt::SquareCap;
    this->penJoinStyle=Qt::BevelJoin;
    this->brushColor=Qt::white;
    this->brushStyle=Qt::NoBrush;
}

TMDrawingPad::~TMDrawingPad()
{
    delete model;
}

void TMDrawingPad::paintEvent(QPaintEvent *paintEvent)
{
    QPainter *painter=new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);
    model->draw(painter);
    if(mode==Mode::NONE && currentComponent!=nullptr) currentComponent=nullptr;
    if(mode==Mode::MULTIPLE_SELECTION)
    {
      if(this->selectedComponents.size()!=0)
      {
          QMapIterator<int,DrawableComponent *> iterator(selectedComponents);
          while(iterator.hasNext())
          {
              iterator.next();
              iterator.value()->select(painter);
          }
      }
    }
    if(mode==Mode::SELECTION && currentComponent!=nullptr)
    {
      currentComponent->select(painter);
    }
    if(mode!=Mode::DRAWING)
    {
        delete painter;
        return;
    }
    if(currentComponent==nullptr)
    {
        delete painter;
        return;
    }
    int currentComponentX1,currentComponentY1,currentComponentX2,currentComponentY2;
    currentComponentX1=currentComponent->getX1();
    currentComponentY1=currentComponent->getY1();
    currentComponentX2=currentComponent->getX2();
    currentComponentY2=currentComponent->getY2();
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
    if(currentComponent->toString()=="Line" && currentComponentX1!=-1 && currentComponentY1!=-1)
    {
        painter->drawLine(QPointF(currentComponentX1,currentComponentY1),QPointF(currentComponentX2,currentComponentY2));
    }
    if(currentComponent->toString()=="Rectangle" && currentComponentX1!=-1 && currentComponentY1!=-1)
    {
        painter->drawRect((currentComponentX1<currentComponentX2)?currentComponentX1:currentComponentX2,(currentComponentY1<currentComponentY2)?currentComponentY1:currentComponentY2,abs(currentComponent->getX1()-currentComponent->getX2()),abs(currentComponent->getY1()-currentComponent->getY2()));
    }
    if(currentComponent->toString()=="Free Hand Tool" && currentComponentX1!=-1 && currentComponentY1!=-1)
    {
        TMFreeHandToolComponent *tmFreeHandToolComponent=(TMFreeHandToolComponent *) currentComponent;
        int pointCount=tmFreeHandToolComponent->getPointCount();
        QList<QPointF> points=tmFreeHandToolComponent->getPointsList();
        QPainterPath path;
        path.moveTo(currentComponentX1,currentComponentY1);
        for(int i=0;i<pointCount;i++) path.lineTo(points[i].x(),points[i].y());
        path.lineTo(currentComponentX2,currentComponentY2);
        painter->drawPath(path);
    }
    if(currentComponent->toString()=="Circle" && currentComponentX1!=-1 && currentComponentY1!=-1)
    {
        QPoint center;
        center.setX(currentComponentX1);
        center.setY(currentComponentY1);
        int radius=sqrt(pow((currentComponentX1-currentComponentX2),2)+pow((currentComponentY1-currentComponentY2),2));
        painter->drawEllipse(center,radius,radius);
    }
    delete painter;
}

void TMDrawingPad::mousePressEvent(QMouseEvent *mouseEvent)
{
    QPointF point=mouseEvent->localPos();
    double x=point.x();
    double y=point.y();
    int index;
    if(mode==Mode::MULTIPLE_SELECTION)
    {
        index=model->processClick(x,y);
        if(index!=-1)
        {
            this->currentComponent=this->model->getAt(index);
            if(this->selectedComponents.contains(index))
            {
                this->selectedComponents.remove(index);
                this->listWidget->setCurrentRow(this->listWidget->count()-(index+1),QItemSelectionModel::Deselect);
            }
            else
            {
                this->selectedComponents.insert(index,currentComponent);
                this->listWidget->setCurrentRow(this->listWidget->count()-(index+1),QItemSelectionModel::Select);
            }
            this->listWidget->setFocus();
            //this->localPoint.setX(x);
            //this->localPoint.setY(y);
        }
        else
        {
            this->selectedComponents.clear();
            this->listWidget->clearFocus();
            this->listWidget->setCurrentRow(this->listWidget->currentRow(),QItemSelectionModel::Deselect);
            this->repaint();
        }
        return;
    }
    if(mode==Mode::SELECTION)
    {
        index=model->processClick(x,y);
        if(index!=-1)
        {
            this->selectedComponents.clear();
            this->currentComponent=this->model->getAt(index);
            this->listWidget->setCurrentRow(model->size()-(index+1));
            this->listWidget->setFocus();
            this->localPoint.setX(x);
            this->localPoint.setY(y);
        }
        else
        {
            this->selectedComponents.clear();
            this->currentComponent=nullptr;
            this->listWidget->clearFocus();
            this->listWidget->setCurrentRow(this->listWidget->currentRow(),QItemSelectionModel::Deselect);

        }
        this->repaint();
        return;
    }

    if(currentComponent==nullptr) return;
    this->currentComponent->setX1(x);
    this->currentComponent->setY1(y);
}

void TMDrawingPad::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    QPointF point=mouseEvent->localPos();
    double x=point.x();
    double y=point.y();
    double changeInX;
    double changeInY;
    if(mode==Mode::MULTIPLE_SELECTION)
    {
        this->repaint();
        return;
    }
    if(currentComponent==nullptr) return;
    if(mode==Mode::SELECTION)
    {
        changeInX=x-this->localPoint.x();
        changeInY=y-this->localPoint.y();
        this->currentComponent->move(changeInX,changeInY);
        this->localPoint.setX(x);
        this->localPoint.setY(y);
        this->repaint();
        return;
    }
    if(currentComponent->getX1()==-1 || currentComponent->getY1()==-1) return;
    QString currentComponentName=currentComponent->toString();
    if(currentComponentName=="Free Hand Tool")
    {
        TMFreeHandToolComponent *tmFreeHandToolComponent=(TMFreeHandToolComponent *) currentComponent;
        tmFreeHandToolComponent->addPoint(QPoint(x,y));
    }
    currentComponent->setX2(x);
    currentComponent->setY2(y);
    this->repaint();
}

void TMDrawingPad::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    QPointF point=mouseEvent->localPos();
    double x=point.x();
    double y=point.y();
    double changeInX;
    double changeInY;
    if(mode==Mode::MULTIPLE_SELECTION)
    {
        this->repaint();
        return;
    }
    if(currentComponent==nullptr) return;
    if(mode==Mode::SELECTION)
    {
        changeInX=x-this->localPoint.x();
        changeInY=y-this->localPoint.y();
        this->currentComponent->move(changeInX,changeInY);
        this->localPoint.setX(x);
        this->localPoint.setY(y);
        this->repaint();
        return;
    }
    currentComponent->setX2(x);
    currentComponent->setY2(y);
    QString currentComponentName=currentComponent->toString();
    if(currentComponentName=="Line")
    {
        TMLineComponent *tmLineComponent=(TMLineComponent *)currentComponent;
        tmLineComponent->setPenWidth(this->penWidth);
        tmLineComponent->setPenColor(this->penColor);
        tmLineComponent->setPenStyle(this->penStyle);
        tmLineComponent->setPenCapStyle(this->penCapStyle);
        tmLineComponent->setPenJoinStyle(this->penJoinStyle);
    }
    if(currentComponentName=="Rectangle")
    {
        TMRectangleComponent *tmRectangleComponent=(TMRectangleComponent *)currentComponent;
        tmRectangleComponent->setPenWidth(this->penWidth);
        tmRectangleComponent->setPenColor(this->penColor);
        tmRectangleComponent->setPenStyle(this->penStyle);
        tmRectangleComponent->setPenCapStyle(this->penCapStyle);
        tmRectangleComponent->setPenJoinStyle(this->penJoinStyle);
        tmRectangleComponent->setBrushColor(this->brushColor);
        tmRectangleComponent->setBrushStyle(this->brushStyle);
    }
    if(currentComponentName=="Free Hand Tool")
    {
        TMFreeHandToolComponent *tmFreeHandToolComponent=(TMFreeHandToolComponent *)currentComponent;
        tmFreeHandToolComponent->setPenWidth(this->penWidth);
        tmFreeHandToolComponent->setPenColor(this->penColor);
        tmFreeHandToolComponent->setPenStyle(this->penStyle);
        tmFreeHandToolComponent->setPenCapStyle(this->penCapStyle);
        tmFreeHandToolComponent->setPenJoinStyle(this->penJoinStyle);
        tmFreeHandToolComponent->setBrushColor(this->brushColor);
        tmFreeHandToolComponent->setBrushStyle(this->brushStyle);
    }
    if(currentComponentName=="Circle")
    {
        TMCircleComponent *tmCircleComponent=(TMCircleComponent *)currentComponent;
        tmCircleComponent->setPenWidth(this->penWidth);
        tmCircleComponent->setPenColor(this->penColor);
        tmCircleComponent->setPenStyle(this->penStyle);
        tmCircleComponent->setPenCapStyle(this->penCapStyle);
        tmCircleComponent->setPenJoinStyle(this->penJoinStyle);
        tmCircleComponent->setBrushColor(this->brushColor);
        tmCircleComponent->setBrushStyle(this->brushStyle);
    }
    model->add(currentComponent);
    currentComponent=nullptr;
    if(currentComponentName=="Line") selectLineTool();
    if(currentComponentName=="Rectangle") selectRectangleTool();
    if(currentComponentName=="Free Hand Tool") selectFreeHandTool();
    if(currentComponentName=="Circle") selectCircleTool();
    this->repaint();
}

void TMDrawingPad::selectLineTool()
{
    this->clearSelection();
    mode=Mode::DRAWING;
    currentComponent=new TMLineComponent();
}

void TMDrawingPad::selectRectangleTool()
{
    this->clearSelection();
    mode=Mode::DRAWING;
    currentComponent=new TMRectangleComponent();
}

void TMDrawingPad::selectFreeHandTool()
{
    this->clearSelection();
    mode=Mode::DRAWING;
    currentComponent=new TMFreeHandToolComponent();
}

void TMDrawingPad::selectCircleTool()
{
    this->clearSelection();
    mode=Mode::DRAWING;
    currentComponent=new TMCircleComponent();
}

void TMDrawingPad::selectPickTool()
{
    mode=Mode::SELECTION;
    if(isControlKeyPressed) mode=Mode::MULTIPLE_SELECTION;
    currentComponent=nullptr;
}

void TMDrawingPad::selectClearTool()
{
    this->clearSelection();
    this->model->clear();
    this->selectedComponents.clear();
    this->nextGroupId=1;
    this->repaint();
}

void TMDrawingPad::groupComponents()
{
    if(this->selectedComponents.count()==0) return;
    QMapIterator<int,DrawableComponent *> iterator(this->selectedComponents);
    QList<QPair<int,DrawableComponent *> *> selectedComponentsList;
    QString name;
    int index;
    DrawableComponent *drawableComponent;
    QPair<int,DrawableComponent *> *pair;
    while(iterator.hasNext())
    {
        iterator.next();
        index=iterator.key();
        drawableComponent=iterator.value();
        drawableComponent->setIsGrouped(true);
        drawableComponent->setGroupId(this->nextGroupId);
        pair=new QPair<int,DrawableComponent *>;
        pair->first=index;
        pair->second=drawableComponent;
        selectedComponentsList.append(pair);
        this->model->remove(drawableComponent);
        name=this->listWidget->item(this->listWidget->count()-(index+1))->text();
        name=name+" ("+QString::number(this->nextGroupId)+")";
        this->listWidget->item(this->listWidget->count()-(index+1))->setText(name);
    }
    TMGroupComponent *tmGroupComponent=new TMGroupComponent();
    tmGroupComponent->setChildComponents(selectedComponentsList);
    this->model->add(tmGroupComponent);
    this->nextGroupId++;
    this->selectedComponents.clear();
    this->currentComponent=tmGroupComponent;
    this->mode=Mode::SELECTION;
    this->listWidget->setFocus();
    this->repaint();
}

void TMDrawingPad::ungroupComponents()
{
    if(currentComponent==nullptr || currentComponent->toString()!="Group") return;
    this->selectedComponents.clear();
    TMGroupComponent *tmGroupComponent=(TMGroupComponent *)currentComponent;
    QList<QPair<int,DrawableComponent *> *> childComponents=tmGroupComponent->getChildComponents();
    int childComponentsSize=childComponents.size();
    DrawableComponent *childComponent;
    int index,groupId;
    QString name;
    for(int i=0;i<childComponentsSize;i++)
    {
        index=childComponents[i]->first;
        childComponent=childComponents[i]->second;
        groupId=childComponent->getGroupId();
        childComponent->setGroupId(0);
        childComponent->setIsGrouped(false);
        this->selectedComponents[index]=childComponent;
        this->model->insertAt(index,childComponent);
        name=this->listWidget->item(this->listWidget->count()-(index+1))->text();
        name=name.remove("("+QString::number(groupId)+")");
        this->listWidget->item(this->listWidget->count()-(index+1))->setText(name);
    }
    tmGroupComponent->clearChildComponents();
    this->model->remove(tmGroupComponent);

    this->nextGroupId--;
    this->currentComponent=nullptr;
    this->mode=Mode::MULTIPLE_SELECTION;
    this->listWidget->setFocus();
    this->repaint();
}

void TMDrawingPad::selectComponent(int index)
{
    this->mode=Mode::SELECTION;
    if(isControlKeyPressed) mode=Mode::MULTIPLE_SELECTION;
    int size=this->model->size();
    currentComponent=this->model->getAt(size-(index+1));
    this->repaint();
}

void TMDrawingPad::setViewComponent(QListWidget *listWidget)
{
    this->listWidget=listWidget;
    if(this->listWidget!=nullptr) this->model->setViewList(this->listWidget);
}

TMModel *TMDrawingPad::getModel() const
{
    return model;
}

void TMDrawingPad::setModel(TMModel *value)
{
    model = value;
}

void TMDrawingPad::clearSelection()
{
    this->currentComponent=nullptr;
    this->listWidget->setCurrentRow(this->listWidget->currentRow(),QItemSelectionModel::Deselect);
    this->repaint();
}

Mode TMDrawingPad::correctSelectionModeFinder()
{
    if(this->mode==Mode::SELECTION && isControlKeyPressed) return Mode::MULTIPLE_SELECTION;
    return this->mode;
}

double TMDrawingPad::getPenWidth() const
{
    return penWidth;
}

void TMDrawingPad::setPenWidth(double value)
{
    penWidth = value;
}

QString TMDrawingPad::getPenColor() const
{
    return penColor;
}

void TMDrawingPad::setPenColor(const QString &value)
{
    penColor = value;
}

Qt::PenStyle TMDrawingPad::getPenStyle() const
{
    return penStyle;
}

void TMDrawingPad::setPenStyle(const Qt::PenStyle &value)
{
    penStyle = value;
}

Qt::PenCapStyle TMDrawingPad::getPenCapStyle() const
{
    return penCapStyle;
}

void TMDrawingPad::setPenCapStyle(const Qt::PenCapStyle &value)
{
    penCapStyle = value;
}

Qt::PenJoinStyle TMDrawingPad::getPenJoinStyle() const
{
    return penJoinStyle;
}

void TMDrawingPad::setPenJoinStyle(const Qt::PenJoinStyle &value)
{
    penJoinStyle = value;
}

QString TMDrawingPad::getBrushColor() const
{
    return brushColor;
}

void TMDrawingPad::setBrushColor(const QString &value)
{
    brushColor = value;
}

Qt::BrushStyle TMDrawingPad::getBrushStyle() const
{
    return brushStyle;
}

void TMDrawingPad::setBrushStyle(const Qt::BrushStyle &value)
{
    brushStyle = value;
}
Mode TMDrawingPad::getMode() const
{
    return mode;
}

void TMDrawingPad::setMode(const Mode &value)
{
    mode = value;
}

bool TMDrawingPad::getIsControlKeyPressed() const
{
    return isControlKeyPressed;
}

void TMDrawingPad::setIsControlKeyPressed(bool value)
{
    isControlKeyPressed = value;
}
