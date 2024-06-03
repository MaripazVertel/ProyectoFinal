#include "Pelota.h"
#include <QTimer>

Pelota::Pelota(qreal x, qreal y, const QPixmap &pixmap, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(pixmap.scaled(20,20), parent), m_velocidadX(3), m_velocidadY(-3) {
    setPos(x, y); // Posición inicial de la pelota

    // Creación de un temporizador para mover la pelota
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Pelota::mover); // Conexión del temporizador al método de mover
    timer->start(16); // Inicia el temporizador (aproximadamente 60 FPS)
}


void Pelota::mover() {
    setPos(x() + m_velocidadX, y() + m_velocidadY); // Movimiento de la pelota según la velocidad en los ejes X e Y
}



void Pelota::setVelocidad(qreal velocidadX, qreal velocidadY) {
    m_velocidadX = velocidadX;
    m_velocidadY = velocidadY;
}

qreal Pelota::velocidadX() const {
    return m_velocidadX;
}

qreal Pelota::velocidadY() const {
    return m_velocidadY;
}

