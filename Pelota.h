#ifndef PELOTA_H
#define PELOTA_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Pelota : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Pelota(qreal x, qreal y, const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    void setVelocidad(qreal velocidadX, qreal velocidadY); // Nueva función
    qreal velocidadX() const;
    qreal velocidadY() const;
public slots:
    void mover();
private:
    qreal m_velocidadX;
    qreal m_velocidadY;
};

#endif // PELOTA_H

