#include <iostream>
#include <Pelota.h>

using namespace std;


#include <QPainter>

Pelota::Pelota(qreal startX, qreal startY, qreal startVelocityX, qreal startVelocityY, qreal startRadius, QGraphicsItem *parent)
    : QGraphicsItem(parent), x(startX), y(startY), velocityX(startVelocityX), velocityY(startVelocityY), radius(startRadius)
{}

QRectF Pelota::boundingRect() const
{
    return QRectF(x - radius, y - radius, 2 * radius, 2 * radius);
}

void Pelota::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawEllipse(x - radius, y - radius, 2 * radius, 2 * radius);
}

void Pelota::move()
{
    x += velocityX;
    y += velocityY;
    setPos(x, y);
}

void Pelota::setVelocity(qreal newVelocityX, qreal newVelocityY)
{
    velocityX = newVelocityX;
    velocityY = newVelocityY;
}

qreal Pelota::getRadius() const
{
    return radius;
}
