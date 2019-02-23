#include "freqplot.h"
#include "ui_freqplot.h"

freqPlot::freqPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::freqPlot)
{
    ui->setupUi(this);
    createfreqPlot();
}

freqPlot::~freqPlot()
{
    delete ui;
}

void freqPlot::createfreqPlot()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->freqCustomPlot->addGraph();
    ui->freqCustomPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->freqCustomPlot->xAxis->setLabel("x");
    ui->freqCustomPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->freqCustomPlot->xAxis->setRange(-1, 1);
    ui->freqCustomPlot->yAxis->setRange(0, 1);
    ui->freqCustomPlot->replot();
}
