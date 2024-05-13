#include "mainwindow.h"
#include "Paleta.h"
#include "Pelota.h"
#include <QGraphicsView>
#include <QTimer>
#include <cmath>





void MainWindow::moverPelota()
{
    // Movemos la pelota
    pelota->move();

    // Detectamos colisiones y rebotes con la paleta
    if (pelota->collidesWithItem(paleta)) {
        qreal diff = pelota->pos().x() - paleta->pos().x();
        qreal factor = diff / (paleta->boundingRect().width() + pelota->getRadius());
        qreal angle = 135 * factor + 45;
        pelota->setVelocity(cos(angle * M_PI / 180), -sin(angle * M_PI / 180));
    }

    // Detectamos colisiones con los bordes de la escena
    /*if (pelota->x() - pelota->getRadius() <= 0 || pelota->x() + pelota->getRadius() >= escena->width()) {
        pelota->setVelocity(-pelota->velocityX(), pelota->velocityY());
    }
    if (pelota->y() - pelota->getRadius() <= 0 || pelota->y() + pelota->getRadius() >= escena->height()) {
        pelota->setVelocity(pelota->velocityX(), -pelota->velocityY());
    }*/
}

/*****************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 1200, 800); // Tamaño de la escena

    pelota = new Pelota(escena->width() / 2, escena->height() / 2, 1, 1, 10); //VERIFICAR


    //fondo
    QPixmap fondo(":/ArkanoidFondo.png");
        escena->setBackgroundBrush(fondo.scaled(escena->sceneRect().size().toSize(), Qt::IgnoreAspectRatio));

    QGraphicsView *vista = new QGraphicsView(escena, this);
    setCentralWidget(vista);

    paleta = new Paleta(escena);
    paleta->setInitialPosition(escena->width() / 2 - paleta->pixmap().width() / 2, escena->height() - paleta->pixmap().height());
    escena->addItem(paleta);


    /*******************************************************************+*/
    // Agregamos la pelota y la paleta a la escena
    //escena->addItem(pelota);
    escena->addItem(paleta);



    // Creamos un temporizador para mover la pelota
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::moverPelota);
    timer->start(16); // Aproximadamente 60 fotogramas por segundo

    // Configuramos la vista
    QGraphicsView *view = new QGraphicsView(escena);
    setCentralWidget(view);
    /*****************************/

}







/**************************************************************/
MainWindow::~MainWindow()
{
    delete escena;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    paleta->keyPressEvent(event);
}
