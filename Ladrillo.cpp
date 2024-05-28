#include "Ladrillo.h"

Ladrillo::Ladrillo(qreal width, qreal height, qreal x, qreal y, const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap.scaled(width, height), parent) {
    setPos(x, y);
}

Ladrillo::~Ladrillo() {
    // Destructor virtual necesario
}
