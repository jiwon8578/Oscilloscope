#include "freqplot.h"
#include "ui_freqplot.h"
#include "qmath.h"
#include "oscisetup.h"

freqPlot::freqPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::freqPlot)
{
    //sender = new OsciSetup;
    //connect(sender,SIGNAL(timeEntered(double)),this,SLOT(on_pushButton_clicked()));
    ui->setupUi(this);

}

freqPlot::~freqPlot()
{
    delete ui;
}

//void freqPlot::inputvalue(double time)
//{
//    QMessageBox::about(this,"test2","test2");
//    time = sender->pushtime().toDouble();
//    double w = 2*(M_PI)*(1/time); //각 진동수 생성
//    double Vmax = 10 ;
//    QVector<double> t(101), v(101);
//    for (int i=0; i<101; ++i)
//    {
//      t[i] = i;
//      v[i] = Vmax*sin(w*i); // let's plot a quadratic function
//    }
//    // create graph and assign data to it:
//    ui->freqCustomPlot->addGraph();
//    ui->freqCustomPlot->graph(0)->setData(t, v);
//    // give the axes some labels:
//    ui->freqCustomPlot->xAxis->setLabel("Time");
//    ui->freqCustomPlot->yAxis->setLabel("Value");
//    // set axes ranges, so we see all data:
//    ui->freqCustomPlot->xAxis->setRange(0, 100);
//    ui->freqCustomPlot->yAxis->setRange(-10, 10);
//    ui->freqCustomPlot->replot();
//}




void freqPlot::on_pushButton_clicked()
{
    QMessageBox::about(this,"test2","test2");
    double w = 2*(M_PI)*(1/t); //각 진동수 생성
    double Vmax = v ;
    QVector<double> time(101), volt(101);
    for (int i=0; i<101; ++i)
    {
      time[i] = i;
      volt[i] = w+Vmax; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->freqCustomPlot->addGraph();
    ui->freqCustomPlot->graph(0)->setData(time, volt);
    // give the axes some labels:
    ui->freqCustomPlot->xAxis->setLabel("Time");
    ui->freqCustomPlot->yAxis->setLabel("Value");
    // set axes ranges, so we see all data:
    ui->freqCustomPlot->xAxis->setRange(0, 100);
    ui->freqCustomPlot->yAxis->setRange(-30, 30);
    ui->freqCustomPlot->replot();
}
