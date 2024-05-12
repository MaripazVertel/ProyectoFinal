#ifndef PELOTA_H

#define PELOTA_H


#include <iostream>


class pelota{


private:

    float x , y; // Posiciones eje x , y en donde se mueve la pelota

    float velocidadEjeX, velocidadEjeY ; // Velocidad en los ejes en donde se mueve la pelota

    float radioPelota; // Radio de la pelota


public:

public:

    void setX(float _x){

        x = _x;

    }


    float getX(){

        return x;

    }



    void setY(float _y){

        y = _y;

    }


    float getY(){

        return y;

    }


    void setVelocidadX(float _velocidadX){

        velocidadEjeX = _velocidadX;

    }


    float getVelocidadX(){

        return velocidadEjeX;

    }


    void setVelocidadY(float _velocidadY){

        velocidadEjeY = _velocidadY;

    }


    float getVelocidadY(){

        return velocidadEjeY;

    }


    void setRadio(float _radio){

        radioPelota = _radio;

    }


    float getRadio(){

        return radioPelota;

    }


    pelota(float _x, float _y, float _velocidadX, float _velocidadY, float _radio) {

            x = _x;

            y = _y;

            velocidadEjeX = _velocidadX;

            velocidadEjeY = _velocidadY;

            radioPelota = _radio;

        }

};

#endif // PELOTA_H
