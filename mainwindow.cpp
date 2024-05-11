#include "mainwindow.h"
#include "Paleta.h"
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 1200, 800); // Tamaño de la escena

    //fondo
    QPixmap fondo(":/ArkanoidFondo.png");
        escena->setBackgroundBrush(fondo.scaled(escena->sceneRect().size().toSize(), Qt::IgnoreAspectRatio));

    QGraphicsView *vista = new QGraphicsView(escena, this);
    setCentralWidget(vista);

    paleta = new Paleta(escena);
    paleta->setInitialPosition(escena->width() / 2 - paleta->pixmap().width() / 2, escena->height() - paleta->pixmap().height());
    escena->addItem(paleta);

}

MainWindow::~MainWindow()
{
    delete escena;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    paleta->keyPressEvent(event);
}
