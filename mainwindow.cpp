#include "mainwindow.h"
#include "Paleta.h"
#include "Pelota.h"
#include "Ladrillo.h"
#include <QGraphicsView>
#include <QPixmap>
#include <QMessageBox>
#include <QApplication>
#include <QTimer>
#include <QSoundEffect>
#include <QStatusBar>
#include <QLabel>
#include <QKeyEvent>
#include <QShowEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), puntaje(0), vidas(3) {
    // Inicializa la escena
    escena = new QGraphicsScene();
    escena->setSceneRect(0, 0, 1200, 650);

    // Carga el fondo de la escena
    QPixmap fondo(":/ArkanoidFondo.png");
    escena->setBackgroundBrush(fondo.scaled(escena->sceneRect().size().toSize(), Qt::IgnoreAspectRatio));

    // Crea la vista
    QGraphicsView *vista = new QGraphicsView(this);
    vista->setScene(escena);
    setCentralWidget(vista);

    // Crear una barra de estado personalizada
    QStatusBar *miBarraEstado = new QStatusBar(this);
    setStatusBar(miBarraEstado);

    // Agrega las etiquetas para mostrar el puntaje y las vidas
    etiquetaPuntaje = new QLabel("Puntaje: 0", this);
    etiquetaVidas = new QLabel("Vidas: 3", this);
    miBarraEstado->addWidget(etiquetaPuntaje);
    miBarraEstado->addWidget(etiquetaVidas);

    // Crea la paleta y establece su posición inicial
    paleta = new Paleta(escena);
    paleta->setInitialPosition(escena->width() / 2 - paleta->pixmap().width() / 2, escena->height() - paleta->pixmap().height());
    escena->addItem(paleta);

    // Crea la pelota y establece su posición inicial con la imagen
    QPixmap pelotaPixmap(":/Pelota.png");
    pelota = new Pelota(escena->width() / 2, escena->height() / 2, pelotaPixmap);
    escena->addItem(pelota);

    // Configura la velocidad inicial de la pelota hacia los ladrillos
    pelota->setVelocidad(3, -3);

    // Crea los ladrillos y los agrega a la escena
    for (int i = 0; i < 5; ++i) { // Crear 5 filas de ladrillos
        for (int j = 0; j < 10; ++j) { // 10 columnas
            qreal x = j * 100+100; // Espaciado horizontal de 100px
            qreal y = i * 30+200;  // Espaciado vertical de 30px
            Ladrillo *ladrillo = new Ladrillo(100, 20, x, y, QPixmap(":/Ladrillo.png"));
            escena->addItem(ladrillo);
        }
    }

    // Carga los efectos de sonido
    rebotePelota = new QSoundEffect(this);
    rebotePelota->setSource(QUrl("qrc:/RebotePelota.wav"));
    rebotePelota->setVolume(0.5);

    reboteLadrillo = new QSoundEffect(this);
    reboteLadrillo->setSource(QUrl("qrc:/ReboteLadrillo.wav"));
    reboteLadrillo->setVolume(0.5);

    reboteParedes = new QSoundEffect(this);
    reboteParedes->setSource(QUrl("qrc:/ReboteParedes.wav"));
    reboteParedes->setVolume(0.5);

    // Configura un temporizador para mover la pelota
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::moverPelota);
    timer->start(16); // Aproximadamente 60 fotogramas por segundo
}

MainWindow::~MainWindow() {
    delete escena;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    paleta->keyPressEvent(event);
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
}

void MainWindow::moverPelota() {
    pelota->mover();

    // Lista para almacenar ladrillos a eliminar
    QList<QGraphicsItem*> itemsAEliminar;

    // Detectar colisión con la paleta
    if (pelota->collidesWithItem(paleta)) {
        rebotePelota->play();
        pelota->setVelocidad(pelota->velocidadX(), -pelota->velocidadY()); // Cambia la dirección de la velocidad en Y
    }
    // Detectar colisión con las paredes
    else if (pelota->x() <= 0 || pelota->x() + pelota->pixmap().width() >= escena->width()) {
        reboteParedes->play();
        pelota->setVelocidad(-pelota->velocidadX(), pelota->velocidadY()); // Cambia la dirección de la velocidad en X
    }
    // Detectar colisión con el techo
    else if (pelota->y() <= 0) {
        reboteParedes->play();
        pelota->setVelocidad(pelota->velocidadX(), -pelota->velocidadY()); // Cambia la dirección de la velocidad en Y
    }

    // Crear una lista de ítems antes de iterar
    QList<QGraphicsItem*> items = escena->items();
    for (auto it = items.begin(); it != items.end(); ++it) {
        Ladrillo *ladrillo = dynamic_cast<Ladrillo*>(*it);
        if (ladrillo && pelota->collidesWithItem(ladrillo)) {
            reboteLadrillo->play();
            puntaje += 10;
            etiquetaPuntaje->setText(QString("Puntaje: %1").arg(puntaje));
            itemsAEliminar.append(ladrillo);
            pelota->setVelocidad(pelota->velocidadX(), -pelota->velocidadY()); // Cambia la dirección de la velocidad en Y
        }
    }

    // Eliminar los ladrillos después de verificar las colisiones
    for (auto it = itemsAEliminar.begin(); it != itemsAEliminar.end(); ++it) {
        escena->removeItem(*it);
        delete *it;
    }

    verificarFinJuego();
}

void MainWindow::actualizarPuntaje(int puntos) {
    puntaje += puntos;
    etiquetaPuntaje->setText(QString("Puntaje: %1").arg(puntaje));
}

void MainWindow::actualizarVidas(int vidas) {
    this->vidas += vidas;
    etiquetaVidas->setText(QString("Vidas: %1").arg(this->vidas));
}

void MainWindow::verificarFinJuego() {
    if (escena->items().size() == 2) { // Solo la pelota y la paleta
        QMessageBox::information(this, "¡Felicidades!", "¡Has ganado el juego!");
        QApplication::quit(); // Cierra la aplicación
    }

    if (pelota->y() > escena->height()) {
        vidas--;
        etiquetaVidas->setText(QString("Vidas: %1").arg(vidas));
        if (vidas == 0) {
            QMessageBox::information(this, "Fin del juego", "¡Has perdido!");
            QApplication::quit(); // Cierra la aplicación
        } else {
            // Reposicionar la pelota y la paleta
            pelota->setPos(escena->width() / 2, escena->height() / 2);
            pelota->setVelocidad(2, -2); // Resetear la velocidad de la pelota
        }
    }
}
