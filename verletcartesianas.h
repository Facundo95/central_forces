#ifndef VELERTCARTESIANAS_H
#define VELERTCARTESIANAS_H

#include "verletalgorithm.h"

class VerletCartesianas : public VerletAlgorithm
{
public:
    VerletCartesianas(QString salida, double mr,double x, double y, double vx, double vy);
    void calcularPotencial(QList<double> potencial);
};

#endif // VELERTCARTESIANAS_H
