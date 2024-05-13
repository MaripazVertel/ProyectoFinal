#ifndef PELOTA_H
#define PELOTA_H

#include <iostream>
#include <QGraphicsItem>

class MainWindow;

class Pelota : public QGraphicsItem
{
    friend class MainWindow;
public:
    Pelota(qreal startX, qreal startY, qreal startVelocityX, qreal startVelocityY, qreal startRadius, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void move();
    void setVelocity(qreal velocityX, qreal velocityY);
    qreal getRadius() const;

private:
    qreal x;
    qreal y;
    qreal velocityX;
    qreal velocityY;
    qreal radius;
};

#endif // PELOTA_H
