#include "iniciojuegowidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

InicioJuegoWidget::InicioJuegoWidget(QWidget *parent)
    : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Agregar el título
    QLabel *titulo = new QLabel("¡Bienvenido!", this);
    titulo->setAlignment(Qt::AlignCenter);
    QFont fuente = titulo->font();
    fuente.setPointSize(24);
    titulo->setFont(fuente);
    layout->addWidget(titulo);

    // Agregar la imagen
    QLabel *imagenLabel = new QLabel(this);
    QPixmap imagen(":/Portada.jpg");
    // Escalar la imagen al doble de su tamaño original
    imagen = imagen.scaled(imagen.width() * 2, imagen.height() * 2);
    imagenLabel->setPixmap(imagen);
    imagenLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imagenLabel);

    // Agregar el botón de iniciar juego
    botonIniciar = new QPushButton("Start ", this);
    connect(botonIniciar, &QPushButton::clicked, this, &InicioJuegoWidget::iniciarJuego);
    layout->addWidget(botonIniciar);

    setLayout(layout);
}
