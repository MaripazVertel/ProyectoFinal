#ifndef LADRILLO_H
#define LADRILLO_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Ladrillo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Ladrillo(qreal width, qreal height, qreal x, qreal y, const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    virtual ~Ladrillo(); // Asegúrate de que el destructor sea virtual
};

#endif // LADRILLO_H
