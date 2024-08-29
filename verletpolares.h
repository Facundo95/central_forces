#ifndef VERLETPOLARES_H
#define VERLETPOLARES_H

#include "verletalgorithm.h"

class VerletPolares : public VerletAlgorithm
{
public:
    VerletPolares(QString salida, double l, double E, double r, QList<double> potencial, double tf, double dt, double mr);
    void calcularPotencial(QList<double> potencial);
};

#endif // VERLETPOLARES_H
