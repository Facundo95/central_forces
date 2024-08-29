#ifndef VERLETALGORITHM_H
#define VERLETALGORITHM_H

#include <fstream>
#include <QString>
#include <QList>
#include <iostream>
#include <math.h>
#include "qmath.h"

using namespace std;

class VerletAlgorithm
{
public:
    VerletAlgorithm();
    virtual void calcularPotencial(QList<double> potencial)=0;
    void resolver(double tf, double dt);


    /** Getters **/
    QList<double> getListaX();
    QList<double> getListaY();

    QList<double> getListaUf();
    QList<double> getListaR();
    QList<double> getListaE();
    double getEnergiaTotal();
    double getMomentoAngular();
    double getVelocidadX();
    double getVelocidadY();

protected:
    QString salida;                                             //Variable para nombrar el archivo de salida
    double mr;												//Masa reducida del sistema
    double x, y;											//Posiciones
    double vx, vy, vx0, vy0;											//Velocidadess
    double Potencial [2][100];                             //Matriz para los terminos del potencial y cantidad de terminos
    double modr;                                                //valor del vector posicion
    double Ur;                                             //Potencial real
    double E;                                                   //Energia total
    double l,linicial;
    int N;


    QList<double> listaX;
    QList<double> listaY;
    QList<double> listaUf;
    QList<double> listaR;
    QList<double> listaE;
};

#endif // VERLETALGORITHM_H
