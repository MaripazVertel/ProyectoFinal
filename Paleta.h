#ifndef PALETA_H
#define PALETA_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>

class Paleta : public QGraphicsPixmapItem {
public:
    Paleta(QGraphicsScene *scene, QGraphicsItem *parent = nullptr); // Constructor

    void setInitialPosition(qreal x, qreal y); // Método para establecer la posición inicial de la paleta

    void keyPressEvent(QKeyEvent *event) override; // Método para manejar los eventos de teclado

private:
    qreal velocidad; // Velocidad de movimiento de la paleta
    QGraphicsScene *escena; // Puntero a la escena donde se encuentra la paleta
};

#endif // PALETA_H
