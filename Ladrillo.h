#ifndef LADRILLO_H
#define LADRILLO_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Ladrillo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int golpesRestantes; // Número de golpes restantes para destruir el ladrillo
public:
    Ladrillo(qreal width, qreal height, qreal x, qreal y, const QPixmap &pixmap, int golpes = 1, QGraphicsItem *parent = nullptr);
    int getGolpesRestantes() const;
    void setGolpesRestantes(int golpes);
    virtual ~Ladrillo();
};

#endif // LADRILLO_H




/*
#ifndef LADRILLO_H
#define LADRILLO_H

#include <QGraphicsRectItem>
#include <QPixmap>

class Ladrillo : public QGraphicsRectItem {
public:
    Ladrillo(int width, int height, int x, int y, const QPixmap &pixmap, int golpesRestantes, QGraphicsItem *parent = nullptr);

    int getGolpesRestantes() const;
    void setGolpesRestantes(int golpes);

private:
    int golpesRestantes;
};

#endif // LADRILLO_H

*/




