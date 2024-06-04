#include "Ladrillo.h"

Ladrillo::Ladrillo(qreal width, qreal height, qreal x, qreal y, const QPixmap &pixmap, int golpes, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap.scaled(width, height), parent), golpesRestantes(golpes) {
    setPos(x, y);
}

Ladrillo::~Ladrillo() {
    // Destructor
}

int Ladrillo::getGolpesRestantes() const {
    return golpesRestantes;
}

void Ladrillo::setGolpesRestantes(int golpes) {
    golpesRestantes = golpes;
}





