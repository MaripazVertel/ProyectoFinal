#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QSoundEffect>

#include "Paleta.h"
#include "Pelota.h"
#include "Ladrillo.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void moverPelota();

private:
    void actualizarPuntaje(int puntos);
    void actualizarVidas(int vidas);
    void verificarFinJuego();
    void reiniciarJuego();


    QGraphicsScene *escena;
    Paleta *paleta;
    Pelota *pelota;
    Ladrillo *ladrillo;
    QLabel *etiquetaPuntaje;
    QLabel *etiquetaVidas;
    QSoundEffect *rebotePelota;
    QSoundEffect *reboteLadrillo;
    QSoundEffect *reboteParedes;
    int puntaje;
    int vidas;
};

#endif // MAINWINDOW_H
