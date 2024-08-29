#include "verletcartesianas.h"

VerletCartesianas::VerletCartesianas(QString salida, double mr, double x, double y, double vx, double vy)
{
    this->salida = salida;
    this->mr = mr;
    this->x = x;
    this->y = y;
    this->vx= vx;
    this->vy= vy;
}

void VerletCartesianas::calcularPotencial(QList<double> potencial)
{
    listaUf.clear();
    listaR.clear();
    listaE.clear();

    N = potencial.size()/2;

    //SE CONSTRUYE EL POTENCI2AL A UTILIZAR//
    int i = 0;
    while (!potencial.empty())
    {
        Potencial [0][i] = potencial.takeFirst();
        Potencial [1][i] = potencial.takeFirst();
        i++;
    }

    //SE CALCULA EL VALOR DE LA ENERGIA TOTAL DEL SISTEMA//
    l = mr*(x*vy-y*vx);                                 //Momento angular del sistema
    modr = sqrt(x*x+y*y);                               //valor del vector r
    double Uc =(l*l)/(2*mr*modr*modr);                  //Potencial centrifugo
    double K=0.5*mr*(vx*vx+vy*vy);                      //Energia cinetica
    Ur=0;												//Valor inicial para sumar los terminos del potencial real
    for (int i=0;i<N;i++)
    {
        Ur=Ur+(Potencial[0][i])*(powl(modr,(Potencial[1][i])));
    }
    E=K+Ur;

    QString archPotencial("Potencial-"+salida);
    ofstream Uefout(archPotencial.toStdString(),ios::out);

    Uefout<<"r \t Ue \t E"<<endl;

    //SE CALCULA EL VALOR DEL POTENCIAL PARA DISTINTOS R Y SE LO MANDA A UNA LISTA.
    double dr = modr/100;
    for (double r=0;r<100;r=r+dr)
    {
        Uefout<<r<<"\t";
        Ur=0;
        for (int i=0;i<N;i++)
            Ur=Ur+(Potencial[0][i])*(powl(r,(Potencial[1][i])));

        Uc=	(l*l)/(2*mr*r*r);
        Uefout<<Ur+Uc<<"\t";
        Uefout<<E<<endl;

        listaR.append(r);
        listaUf.append(Ur+Uc);
        listaE.append(E);
    }
    Uefout.close();
}
