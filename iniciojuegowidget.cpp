#include "iniciojuegowidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>



InicioJuegoWidget::InicioJuegoWidget(QWidget *parent)
    : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);


    QLabel *titulo = new QLabel("¡Bienvenido a Arkanoid!", this);
    titulo->setAlignment(Qt::AlignCenter);
    QFont fuente = titulo->font();
    fuente.setPointSize(24);
    titulo->setFont(fuente);
    layout->addWidget(titulo);

    botonIniciar = new QPushButton("Iniciar Juego", this);
    connect(botonIniciar, &QPushButton::clicked, this, &InicioJuegoWidget::iniciarJuego);
    layout->addWidget(botonIniciar);

    setLayout(layout);
}
