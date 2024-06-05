#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QSoundEffect>
#include "iniciojuegowidget.h"

class Paleta;
class Pelota;
class Ladrillo;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void mostrarPantallaPrincipal();

private:
    void moverPelota();
    void verificarFinJuego();
    void reiniciarJuego();
    void crearLadrillos();
    void actualizarPuntaje(int puntos);
    void actualizarVidas(int vidas);
    bool juegoIniciado;

    QGraphicsScene *escena;
    Paleta *paleta;
    Pelota *pelota;
    QLabel *etiquetaPuntaje;
    QLabel *etiquetaVidas;
    QSoundEffect *rebotePelota;
    QSoundEffect *reboteLadrillo;
    QSoundEffect *reboteParedes;
    int puntaje;
    int vidas;

    InicioJuegoWidget *inicioWidget;

    QTimer *timer;  // Agregar el temporizador como miembro de la clase
};

#endif // MAINWINDOW_H
