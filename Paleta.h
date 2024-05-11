#ifndef PALETA_H
#define PALETA_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
class Paleta : public QGraphicsPixmapItem
{
public:
    Paleta(QGraphicsScene *scene, QGraphicsItem *parent = nullptr);

    void setInitialPosition(qreal x, qreal y);

    void keyPressEvent(QKeyEvent *event) override;

private:
    qreal velocidad;
    QGraphicsScene *escena;
};

#endif // PALETA_H
