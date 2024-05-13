#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "Paleta.h"
#include "Pelota.h"

class Paleta;
class Pelota;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *escena;
    Paleta *paleta;
    Pelota *pelota;


public:
    void moverPelota();
};


#endif // MAINWINDOW_H
