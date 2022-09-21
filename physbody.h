#ifndef PHYSBODY_H
#define PHYSBODY_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class physBody : public QGraphicsItem
{
public:
    physBody();
    ~physBody();
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    double radius;
};

#endif // PHYSBODY_H
