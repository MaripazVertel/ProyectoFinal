#include "Paleta.h"
#include <QKeyEvent>
#include <QGraphicsScene>


Paleta::Paleta(QGraphicsScene *scene, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), velocidad(10), escena(scene)
{
    QPixmap pixmap(":/Barra.png");
    setPixmap(pixmap.scaled(100, 20));
}

void Paleta::setInitialPosition(qreal x, qreal y)
{
    setPos(x, y);
}

void Paleta::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A) {
        // Mover la paleta hacia la izquierda
        qreal nuevaPosicion = x() - velocidad;
        if (nuevaPosicion >= 0) { // Verificar que no se salga de la escena
            setPos(nuevaPosicion, y());
        }
    } else if (event->key() == Qt::Key_D) {
        // Mover la paleta hacia la derecha
        qreal nuevaPosicion = x() + velocidad + pixmap().width();
        if (nuevaPosicion <= escena->width()) { // Verificar que no se salga de la escena
            setPos(nuevaPosicion - pixmap().width(), y());
        }
    }
}
