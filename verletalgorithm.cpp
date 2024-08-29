#include "verletalgorithm.h"
#include "QDebug"

VerletAlgorithm::VerletAlgorithm()
{
}

/**ALGORITMO DE VERLET**/
void VerletAlgorithm::resolver(double tf, double dt)
{
    listaX.clear();
    listaY.clear();

    //CALCULAR LAS ACELERACIONES EN T=0 PARA PODER PROMEDIAR LAS VELOCIDADES
    modr=sqrt(x*x+y*y);                                     //Modulo del vector r
    double verx=x/modr;                                     //Versor en la direccion x
    double very=y/modr;                                     //Versor en la direccion y
    double Fx=0;											//Valores iniciales para las fuerzas en x e y
    double Fy=0;
    for (int i=0;i<N;i++)
    {
        Fx=Fx-(Potencial[1][i])*(Potencial[0][i])*powl(modr,(Potencial[1][i]-1))*verx;
        Fy=Fy-(Potencial[1][i])*(Potencial[0][i])*powl(modr,(Potencial[1][i]-1))*very;
    }
    long double axprev=Fx/mr;                                   //Aceleraciones previas
    long double ayprev=Fy/mr;


    //Armo la lista de datos que van a salir en .txt
    QString archTrayectoria("trayectoria-"+salida);
    ofstream posout(archTrayectoria.toStdString(),ios::out);	
    posout<<"t \t x \t y "<<endl;
    posout<<"s \t m \t m"<<endl;
    posout<<"segundos \t metros \t metros"<<endl;

    //Control de paso.
    double dT=dt/sqrt((vx*vx+vy*vy)+(axprev*axprev+ayprev*ayprev));     

    //Calculo la Energia inicial y el momento angular inicial para controlar su conservacion.
    linicial=mr*(x*vy-y*vx);                                
    double Epot=0;
    for(int i=0;i<N;i++)
        Epot=Epot+(Potencial[0][i])*(powl(modr,(Potencial[1][i])));
    double Ekin=0.5*mr*(vx*vx+vy*vy);
    double E0=Ekin+Epot;
    
    
    //Algoritmo de verlet.
    bool BanderitaE=true,BanderitaL=true;
    double ax, ay;                                              //Aceleraciones actualizadas.
    double T=0;
    while ((T<tf)&&(modr>0.01)&&(BanderitaE)&&(BanderitaL))                  
        {
            //calculo el momento angular y la energia total para verificar si se conservan.
            double Epot=0;
            for(int i=0;i<N;i++)
                Epot=Epot+(Potencial[0][i])*(powl(modr,(Potencial[1][i])));
            double Ekin=0.5*mr*(vx*vx+vy*vy);
            E=Ekin+Epot;
            l=mr*(x*vy-y*vx);
            if(sqrt((E-E0)*(E-E0)/E0*E0)>0.05)
                BanderitaE=false;
            if(sqrt((l-linicial)*(l-linicial)/E0*E0)>0.05)
                BanderitaL=false;

            //Calculo las posiciones.
            posout<<T<<"\t";
            x=x+vx*dT+0.5*(axprev)*dT*dT;
            y=y+vy*dT+0.5*(ayprev)*dT*dT;

            listaX.append(x);
            listaY.append(y);

            posout<<x<<"\t"<<y<<endl;
            //1 Defino los versores x e y
            modr=sqrt(x*x+y*y);
            verx=x/modr;
            very=y/modr;
            //2 Calculo la fuerza:
            Fx=0;
            Fy=0;
            for (int i=0;i<N;i++)
            {
                Fx=Fx-(Potencial[1][i])*(Potencial[0][i])*powl(modr,(Potencial[1][i]-1))*verx;
                Fy=Fy-(Potencial[1][i])*(Potencial[0][i])*powl(modr,(Potencial[1][i]-1))*very;
            }
            //3 Caluculo la aceleracion:
            ax=Fx/mr;
            ay=Fy/mr;
            //4 Calculo las velocidades:
            vx=vx+0.5*(axprev+ax)*dT;
            vy=vy+0.5*(ayprev+ay)*dT;
            axprev=ax;
            ayprev=ay;
            dT=dt/sqrt((vx*vx+vy*vy)+(axprev*axprev+ayprev*ayprev));
            T=T+dT;
        }

    posout.close();
}

/**Getters**/
QList<double> VerletAlgorithm::getListaX()
{
    return listaX;
}

QList<double> VerletAlgorithm::getListaY()
{
    return listaY;
}

QList<double> VerletAlgorithm::getListaUf()
{
    return listaUf;
}

QList<double> VerletAlgorithm::getListaR()
{
    return listaR;
}

QList<double> VerletAlgorithm::getListaE()
{
    return listaE;
}

double VerletAlgorithm::getEnergiaTotal()
{
    return E;
}

double VerletAlgorithm::getMomentoAngular()
{
    return l;
}
