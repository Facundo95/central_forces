#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "qcustomplot/qcustomplot.h"
#include <QList>
#include "verletalgorithm.h"
#include "verletcartesianas.h"
#include "verletpolares.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void drawPlotPotencial(QList<double> listaR, QList<double>listaUf,QList<double>listaE);
    void drawPlotTrayectoria(QList<double> listaX, QList<double> listaY);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtonEjecutar_clicked();

    void on_pushButtonEjecutar_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QCustomPlot* customPlot;
};

#endif // MAINWINDOW_H
