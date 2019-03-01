#include "freqplot.h"
#include "ui_freqplot.h"
#include "qmath.h"
#include "oscisetup.h"

double OsciSetup::time;
double OsciSetup::volt;

freqPlot::freqPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::freqPlot)
{
    sender = new OsciSetup;
    //connect(sender,SIGNAL(timeEntered(double)),this,SLOT(on_pushButton_clicked()));
    ui->setupUi(this);

}

freqPlot::~freqPlot()
{
    delete ui;
}

void freqPlot::on_pushButton_clicked()
{
    double w = 2*(M_PI)*(1/OsciSetup::time); //각 진동수 생성
    double Vmax = OsciSetup::volt ;
    QVector<double> time(500), volt(500);
    for (int i=0; i<500; ++i)
    {
      time[i] = OsciSetup::time*i;
      volt[i] = Vmax*sin(w*i); // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->freqCustomPlot->addGraph();
    ui->freqCustomPlot->graph(0)->setData(time, volt);
    // give the axes some labels:
    ui->freqCustomPlot->xAxis->setLabel("Time");
    ui->freqCustomPlot->yAxis->setLabel("Value");
    // set axes ranges, so we see all data:
    ui->freqCustomPlot->xAxis->setRange(0, 300);
    ui->freqCustomPlot->yAxis->setRange(-100, 100);
    // make grid
//    QVector<double> x(501), y(501);
//    for (int j=0; j<500; ++j)
//    {
//        x[j]= OsciSetup::time*j;
//        y[j]= OsciSetup::volt*j;
//    }

//    QCPBars *bars1 = new QCPBars(ui->freqCustomPlot->xAxis, ui->freqCustomPlot->yAxis);
//    bars1->setWidth(9/(double)x.size());
//    bars1->setData(x, y);
//    bars1->setPen(Qt::NoPen);
//    bars1->setBrush(QColor(10, 140, 70, 160));
    ui->freqCustomPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->freqCustomPlot->replot();
}
