#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "instrucciones.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->tabla->setRowCount( ui->tabla->rowCount()+1);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->tabla->rowCount()>0)
        ui->tabla->setRowCount(ui->tabla->rowCount()-1);
}
void MainWindow::on_pushButtonEjecutar_clicked()
{
    //Para el potencial!!!
    QList<double> potencial;
    int N = ui->tabla->rowCount();
    for (int i=0;i<N;i++)
    {
        double k = 0;
        double n = 0;
        if (ui->tabla->item(i,0) != 0)
            k = ui->tabla->item(i,0)->text().replace(',','.').toDouble(0);
        if (ui->tabla->item(i,1) != 0)
            n = ui->tabla->item(i,1)->text().replace(',','.').toDouble(0);
        potencial.append(k);
        potencial.append(n);
    }

    VerletAlgorithm* verlet = new VerletCartesianas(ui->lineSalida->text(),ui->doubleSpinBoxMr->value(),ui->doubleSpinBoxX0->value(),ui->doubleSpinBoxY0->value(),ui->doubleSpinBoxVx0->value(),ui->doubleSpinBoxVy0->value());
    verlet->calcularPotencial(potencial);
    verlet->resolver(ui->doubleSpinBoxTf->value(),ui->doubleSpinBoxDt->value());


    drawPlotPotencial(verlet->getListaR(),verlet->getListaUf(),verlet->getListaE());
    drawPlotTrayectoria(verlet->getListaX(),verlet->getListaY());

    ui->eLCD->display(verlet->getEnergiaTotal());
    ui->lLCD->display(verlet->getMomentoAngular());
    ui->VelocidadX->display(0);
    ui->VelocidadY->display(0);

    delete(verlet);
}

void MainWindow::drawPlotPotencial(QList<double> listaR, QList<double>listaUf,QList<double>listaE)
{
    customPlot = ui->potencial;

    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::red));

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::blue));

    QVector<double> x(listaR.size()), y(listaUf.size()), y1(listaE.size());

    for (int i=0;i<listaR.size();i++)
    {
        x[i] = listaR[i];
        y[i] = listaUf[i];
        y1[i] = listaE[i];
    }

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);

    customPlot->yAxis->setLabel("U(r)");
    customPlot->xAxis->setLabel("r");
    customPlot->graph(1)->setName("Energia");

    customPlot->graph(0)->setData(x, y);
    customPlot->graph(1)->setData(x,y1);

    customPlot->graph(0)->rescaleAxes(true);
    customPlot->graph(1)->rescaleAxes(true);
    customPlot->xAxis->setRange(0,5);
    
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    customPlot->axisRect()->setRangeZoom(Qt::Vertical);


    customPlot->replot();
}

void MainWindow::drawPlotTrayectoria(QList<double> listaX, QList<double>listaY)
{
    customPlot = ui->trayectoria;

    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    customPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc , 3));

    //cutomPlot->addGraph();

    QVector<double> x(listaX.size()), y(listaY.size());

    for (int i=0;i<listaX.size();i++)
    {
        x[i] = listaX[i];
        y[i] = listaY[i];
    }

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);

    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    customPlot->graph(0)->setData(x, y);

    customPlot->graph(0)->rescaleAxes();
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->replot();
}

void MainWindow::on_pushButtonEjecutar_2_clicked()
{
    //Para el potencial!!!
    QList<double> potencial;
    int N = ui->tabla->rowCount();
    for (int i=0;i<N;i++)
    {
        double k = 0;
        double n = 0;
        if (ui->tabla->item(i,0) != 0)
            k = ui->tabla->item(i,0)->text().replace(',','.').toDouble(0);
        if (ui->tabla->item(i,1) != 0)
            n = ui->tabla->item(i,1)->text().replace(',','.').toDouble(0);
        potencial.append(k);
        potencial.append(n);
    }



    VerletAlgorithm* verlet = new VerletPolares(ui->lineSalida->text(),ui->spinBoxMomentoAngular->value(),ui->spinBoxEnergia->value(),ui->spinBoxPosicion->value(),potencial,ui->doubleSpinBoxTf->value(),ui->doubleSpinBoxDt->value(),ui->doubleSpinBoxMr->value());
    verlet->calcularPotencial(potencial);
    verlet->resolver(ui->doubleSpinBoxTf->value(),ui->doubleSpinBoxDt->value());
    drawPlotPotencial(verlet->getListaR(),verlet->getListaUf(),verlet->getListaE());
    drawPlotTrayectoria(verlet->getListaX(),verlet->getListaY());

    ui->VelocidadX->display(verlet->getVelocidadX());
    ui->VelocidadY->display(verlet->getVelocidadY());
    ui->eLCD->display(0);
    ui->lLCD->display(0);

    delete(verlet);
}

void MainWindow::on_pushButton_3_clicked()
{
   Instrucciones instrucciones;
   instrucciones.setModal(true);
   instrucciones.exec();
}
