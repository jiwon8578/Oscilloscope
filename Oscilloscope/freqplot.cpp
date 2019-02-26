#include "freqplot.h"
#include "ui_freqplot.h"
#include "qmath.h"
#include "oscisetup.h"

freqPlot::freqPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::freqPlot)
{
    ui->setupUi(this);
    m_form = new OsciSetup; //test
    //m_form -> show();       //test
    createfreqPlot();
}

freqPlot::~freqPlot()
{
    delete ui;
}

void freqPlot::createfreqPlot()
{
    double f = m_form->currentText().toDouble(); //test
    double w = 2*(M_PI)*f; //각 진동수 생성
    double Vmax = 10 ;
    QVector<double> time(101), v(101);
    for (int i=0; i<101; ++i)
    {
      time[i] = i;
      v[i] = Vmax*sin(w*i); // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->freqCustomPlot->addGraph();
    ui->freqCustomPlot->graph(0)->setData(time, v);
    // give the axes some labels:
    ui->freqCustomPlot->xAxis->setLabel("Time");
    ui->freqCustomPlot->yAxis->setLabel("Value");
    // set axes ranges, so we see all data:
    ui->freqCustomPlot->xAxis->setRange(0, 100);
    ui->freqCustomPlot->yAxis->setRange(-10, 10);
    ui->freqCustomPlot->replot();
}
