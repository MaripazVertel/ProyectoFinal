#ifndef INICIOJUEGOWIDGET_H
#define INICIOJUEGOWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class InicioJuegoWidget : public QWidget {
    Q_OBJECT
public:
    explicit InicioJuegoWidget(QWidget *parent = nullptr);

signals:
    void iniciarJuego();

private:
    QPushButton *botonIniciar;
    QLabel *etiquetaTitulo;
};

#endif // INICIOJUEGOWIDGET_H

