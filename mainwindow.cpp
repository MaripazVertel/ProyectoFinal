#include "mainwindow.h"
#include "Paleta.h"
#include "Pelota.h"
#include "Ladrillo.h"
#include "iniciojuegowidget.h"  // Incluir el widget de inicio de juego
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
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), puntaje(0), vidas(3) {

    // Crear y configurar la pantalla de inicio
    inicioWidget = new InicioJuegoWidget(this);
    setCentralWidget(inicioWidget);
    connect(inicioWidget, &InicioJuegoWidget::iniciarJuego, this, &MainWindow::mostrarPantallaPrincipal);

    // Inicializar la escena
    escena = new QGraphicsScene();
    escena->setSceneRect(0, 0, 1200, 650);

    // Cargar el fondo de la escena
    QPixmap fondo(":/ArkanoidFondo.png");
    escena->setBackgroundBrush(fondo.scaled(escena->sceneRect().size().toSize(), Qt::IgnoreAspectRatio));

    // Crear la vista
    QGraphicsView *vista = new QGraphicsView(this);
    vista->setScene(escena);

    // Crear una barra de estado personalizada
    QStatusBar *miBarraEstado = new QStatusBar(this);
    setStatusBar(miBarraEstado);

    // Agregar etiquetas para mostrar el puntaje y las vidas
    etiquetaPuntaje = new QLabel("Puntaje: 0", this);
    etiquetaVidas = new QLabel("Vidas: 3", this);
    miBarraEstado->addWidget(etiquetaPuntaje);
    miBarraEstado->addWidget(etiquetaVidas);

    // Crear la paleta y establecer su posición inicial
    paleta = new Paleta(escena);
    int margen_inferior = -85;
    paleta->setInitialPosition(escena->width() / 2 - paleta->pixmap().width() / 2, escena->height() - paleta->pixmap().height() - margen_inferior);
    escena->addItem(paleta);

    // Crear la pelota y establecer su posición inicial con la imagen
    QPixmap pelotaPixmap(":/Pelota.png");
    pelota = new Pelota(escena->width() / 2, escena->height() / 2, pelotaPixmap);
    escena->addItem(pelota);

    // Configurar la velocidad inicial de la pelota hacia los ladrillos
    pelota->setVelocidad(2, -2);

    // Crear los ladrillos
    crearLadrillos();

    // Cargar los efectos de sonido
    rebotePelota = new QSoundEffect(this);
    rebotePelota->setSource(QUrl("qrc:/RebotePelota.wav"));
    rebotePelota->setVolume(0.5);

    reboteLadrillo = new QSoundEffect(this);
    reboteLadrillo->setSource(QUrl("qrc:/ReboteLadrillo.wav"));
    reboteLadrillo->setVolume(0.5);

    reboteParedes = new QSoundEffect(this);
    reboteParedes->setSource(QUrl("qrc:/ReboteParedes.wav"));
    reboteParedes->setVolume(0.5);

    // Configurar un temporizador para mover la pelota
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

void MainWindow::mostrarPantallaPrincipal() {
    // Configurar la ventana principal del juego
    QGraphicsView *vista = new QGraphicsView(this);
    vista->setScene(escena);
    setCentralWidget(vista);
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
        Ladrillo *ladrillo = dynamic_cast<Ladrillo*>(*it);
        if (ladrillo) {
            int golpesRestantes = ladrillo->getGolpesRestantes();
            if (golpesRestantes > 1) {
                // Reducir el número de golpes restantes
                ladrillo->setGolpesRestantes(golpesRestantes - 1);
            } else {
                // Si solo queda un golpe, eliminar el ladrillo
                escena->removeItem(*it);
                delete *it;
            }
        }
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
        // Crear un QMessageBox personalizado para "¡Has ganado!"
        QMessageBox msgBox;
        msgBox.setWindowTitle("¡Felicidades!");

        // Crear un widget contenedor
        QWidget* widget = new QWidget(&msgBox);
        QVBoxLayout* layout = new QVBoxLayout(widget);

        // Crear y agregar la etiqueta con la imagen de victoria
        QLabel* etiquetaImagen = new QLabel();
        QPixmap imagen(":/Ganado.jpg");
        etiquetaImagen->setPixmap(imagen);
        layout->addWidget(etiquetaImagen);

        // Ajustar el layout del widget y agregarlo al QMessageBox
        widget->setLayout(layout);
        msgBox.layout()->addWidget(widget);

        // Agregar botones
        msgBox.addButton(QMessageBox::Ok);
        QAbstractButton* replayButton = msgBox.addButton("Volver a jugar", QMessageBox::ActionRole);

        // Mostrar el mensaje y esperar a que el usuario lo cierre
        msgBox.exec();

        // Manejar la respuesta del usuario
        if (msgBox.clickedButton() == replayButton) {
            reiniciarJuego();
        } else {
            QApplication::quit(); // Cierra la aplicación
        }
    }

    if (pelota->y() > escena->height()) {
        vidas--;
        etiquetaVidas->setText(QString("Vidas: %1").arg(vidas));
        if (vidas == 0) {
            // Crear un QMessageBox personalizado para "¡Has perdido!"
            QMessageBox msgBox;
            msgBox.setWindowTitle("Fin del juego");

            // Crear un widget contenedor
            QWidget* widget = new QWidget(&msgBox);
            QVBoxLayout* layout = new QVBoxLayout(widget);

            // Crear y agregar la etiqueta con la imagen de derrota
            QLabel* etiquetaImagen = new QLabel();
            QPixmap imagen(":/Perdida.jpg");
            etiquetaImagen->setPixmap(imagen);
            layout->addWidget(etiquetaImagen);

            // Ajustar el layout del widget y agregarlo al QMessageBox
            widget->setLayout(layout);
            msgBox.layout()->addWidget(widget);

            // Agregar botones
            msgBox.addButton(QMessageBox::Ok);
            QAbstractButton* replayButton = msgBox.addButton("Volver a jugar", QMessageBox::ActionRole);

            // Mostrar el mensaje y esperar a que el usuario lo cierre
            msgBox.exec();

            // Manejar la respuesta del usuario
            if (msgBox.clickedButton() == replayButton) {
                reiniciarJuego();
            } else {
                QApplication::quit(); // Cierra la aplicación
            }
        } else {
            // Reposicionar la pelota y la paleta
            pelota->setPos(escena->width() / 2, escena->height() / 2);
            pelota->setVelocidad(2, -2); // Resetear la velocidad de la pelota
        }
    }
}

void MainWindow::reiniciarJuego() {
    // Reiniciar el puntaje y las vidas
    puntaje = 0;
    vidas = 3;
    etiquetaPuntaje->setText("Puntaje: 0");
    etiquetaVidas->setText("Vidas: 3");

    // Eliminar todos los ladrillos de la escena
    QList<QGraphicsItem*> items = escena->items();
    for (auto it = items.begin(); it != items.end(); ++it) {
        Ladrillo* ladrillo = dynamic_cast<Ladrillo*>(*it);
        if (ladrillo) {
            escena->removeItem(ladrillo);
            delete ladrillo;
        }
    }

    // Reiniciar la posición de la paleta y la pelota

    int margen_inferior = -85;
    paleta->setPos(escena->width() / 2 - paleta->pixmap().width() / 2, escena->height() - paleta->pixmap().height() - margen_inferior);
    pelota->setPos(escena->width() / 2, escena->height() / 2);
    pelota->setVelocidad(3, -3);

    // Recrear los ladrillos
    crearLadrillos();
}

void MainWindow::crearLadrillos() {
    // Crea los ladrillos y los agrega a la escena
    for (int i = 0; i < 5; ++i) { // Crear 5 filas de ladrillos
        for (int j = 0; j < 10; ++j) { // 10 columnas
            qreal x = j * 100 + 100; // Espaciado horizontal de 100px
            qreal y = i * 30 + 200;  // Espaciado vertical de 30px

            QPixmap pixmap;
            int golpes = 1; // Por defecto, un golpe para destruir el ladrillo

            // Identifica los ladrillos que requieren dos golpes para destruirse
            if (i % 2 == 0) { // Si estamos en una fila par
                if (j % 2 == 0) { // Si estamos en una columna par
                    golpes = 3; // Tres golpes para destruir el ladrillo
                }
            } else { // Si estamos en una fila impar
                if (j % 2 != 0) { // Si estamos en una columna impar
                    golpes = 2; // Dos golpes para destruir el ladrillo
                }
            }

            switch (i) {
                case 0:
                    pixmap = QPixmap(":/LadrilloRojo.png");
                    break;
                case 1:
                    pixmap = QPixmap(":/LadrilloNaranja.png");
                    break;
                case 2:
                    pixmap = QPixmap(":/LadrilloVerde.png");
                    break;
                case 3:
                    pixmap = QPixmap(":/LadrilloAmarillo.png");
                    break;
                case 4:
                    pixmap = QPixmap(":/LadrilloGris.png");
                    break;
                default:
                    pixmap = QPixmap(":/Ladrillo.png");
                    break;
            }

            // Crear el ladrillo con el pixmap seleccionado
            Ladrillo *ladrillo = new Ladrillo(100, 20, x, y, pixmap, golpes);
            escena->addItem(ladrillo);
        }
    }
}
