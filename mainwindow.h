#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QSoundEffect>

// Declaraciones de las clases utilizadas
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

private:
    void moverPelota();
    void verificarFinJuego();
    void reiniciarJuego();
    void crearLadrillos();  // Asegúrate de declarar esta función
    void actualizarPuntaje(int puntos);
    void actualizarVidas(int vidas);

    // Otros miembros y funciones...

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
};

#endif // MAINWINDOW_H
