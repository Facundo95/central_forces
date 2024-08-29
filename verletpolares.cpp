#include "verletpolares.h"

VerletPolares::VerletPolares(QString salida, double l, double E, double r, QList<double> potencial, double tf, double dt, double mr)
{
    this->salida = salida;
    this->l = l;
    this->E = E;
    this->modr = r;
    this->mr = mr;
}

void VerletPolares::calcularPotencial(QList<double> potencial)
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
    };

    //SE PIDEN LAS POSICIONES POR PANTALLA Y SE OBTIENE UNA GRAFICA DEL POTENCIAL.

    QString archPotencial("Potencial-"+salida);
    ofstream Uefout(archPotencial.toStdString(),ios::out);

    //Energia total del sistema
    Uefout<<"r \t Ue \t E"<<endl;
     double dr = modr/100;
    for ( double r=0;r<100;r=r+dr)
    {
        Uefout<<r<<"\t";
        Ur=0;
        for (int i=0;i<N;i++)
            Ur=Ur+(Potencial[0][i])*(powl(r,(Potencial[1][i])));

        double Uc=	(l*l)/(2*mr*r*r);
        Uefout<<Ur+Uc<<"\t";
        Uefout<<E<<endl;

        listaR.append(r);
        listaUf.append(Ur+Uc);
        listaE.append(E);

    };
    Uefout.close();

    //CAMBIO LAS VARIABLES DE POLARES A CARTESIANAS.
    double UR=0;
    for (int i=0;i<N;i++)
    {
        UR=UR+(Potencial[0][i])*(powl(modr,(Potencial[1][i])));
    }


    double modv0 = sqrt(2*(E-UR)/mr);
    double alpha = qAsin(l/(mr*modr*modv0));
    vx0=modv0*qCos(alpha);
    vy0=modv0*qSin(alpha);

    vx=vx0;
    vy=vy0;
    mr =mr;
    x =modr;
    y =0;

}
//getters
double VerletAlgorithm::getVelocidadX()
{
    return vx0;
}
double VerletAlgorithm::getVelocidadY()
{
    return vy0;
}
