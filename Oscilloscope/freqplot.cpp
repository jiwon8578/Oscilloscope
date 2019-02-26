#include "freqplot.h"
#include "ui_freqplot.h"
#include "qmath.h"
#include "oscisetup.h"

freqPlot::freqPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::freqPlot)
{
    sender = new OsciSetup;
    connect(sender,SIGNAL(entered(double,double)),this,SLOT(inputvalue(double,double)));
    ui->setupUi(this);

}

freqPlot::~freqPlot()
{
    delete ui;
}

void freqPlot::inputvalue(double time,double volt)
{
    double w = 2*(M_PI)*(1/time); //각 진동수 생성
    double Vmax = volt ;
    QVector<double> t(101), v(101);
    for (int i=0; i<101; ++i)
    {
      t[i] = i;
      v[i] = Vmax*sin(w*i); // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->freqCustomPlot->addGraph();
    ui->freqCustomPlot->graph(0)->setData(t, v);
    // give the axes some labels:
    ui->freqCustomPlot->xAxis->setLabel("Time");
    ui->freqCustomPlot->yAxis->setLabel("Value");
    // set axes ranges, so we see all data:
    ui->freqCustomPlot->xAxis->setRange(0, 100);
    ui->freqCustomPlot->yAxis->setRange(-10, 10);
    ui->freqCustomPlot->replot();
}
