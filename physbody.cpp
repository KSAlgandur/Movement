#include "physbody.h"

physBody::physBody()
{

}

QRectF physBody::boundingRect() const
{
    return QRectF(0,0,2*radius,2*radius);
}

void physBody::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{

    QPen pen(Qt::black, 1); // цвет контура тела (чёрный)
    QBrush brush(Qt::blue); // цвет тела (синий)
    painter->setPen(pen);
    painter->setBrush(brush);
    // прорисовка тела в виде окружности
    painter->drawEllipse(boundingRect());


}

physBody::~physBody()
{
}
