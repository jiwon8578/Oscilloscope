#include "fftplot.h"
#include "ui_fftplot.h"
#include "mainwindow.h"
#include <QMdiSubWindow>

fftPlot::fftPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fftPlot)
{
    ui->setupUi(this);
    createfftPlot();
}

fftPlot::~fftPlot()
{
    delete ui;
}

void fftPlot::createfftPlot()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->fftCustomPlot->addGraph();
    ui->fftCustomPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->fftCustomPlot->xAxis->setLabel("x");
    ui->fftCustomPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->fftCustomPlot->xAxis->setRange(-1, 1);
    ui->fftCustomPlot->yAxis->setRange(0, 1);
    ui->fftCustomPlot->replot();
}

QMdiSubWindow *MainWindow::fftWaveformWin;

void fftPlot::closeEvent(QCloseEvent *event)
{
    MainWindow::fftWaveformWin->hide();
    event->ignore();
}


