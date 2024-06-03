#include "Paleta.h"
#include <QKeyEvent>
#include <QGraphicsScene>

Paleta::Paleta(QGraphicsScene *scene, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), velocidad(20), escena(scene) { // Constructor de la paleta
    QPixmap pixmap(":/Barra.1.png"); // Carga la imagen de la paleta
    setPixmap(pixmap.scaled(200, 200)); // Establece la imagen de la paleta y la escala

}


void Paleta::setInitialPosition(qreal x, qreal y) {
    setPos(x, y); // Establece la posición inicial de la paleta
}






void Paleta::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) { // Si se presiona la tecla A
        qreal nuevaPosicion = x() - velocidad; // Calcula la nueva posición hacia la izquierda
        if (nuevaPosicion >= 0) { // Verifica que no se salga de la escena
            setPos(nuevaPosicion, y()); // Establece la nueva posición
        }
    } else if (event->key() == Qt::Key_D) { // Si se presiona la tecla D
        qreal nuevaPosicion = x() + velocidad + pixmap().width(); // Calcula la nueva posición hacia la derecha
        if (nuevaPosicion <= escena->width()) { // Verifica que no se salga de la escena
            setPos(nuevaPosicion - pixmap().width(), y()); // Establece la nueva posición
        }
    }
}




