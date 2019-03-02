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
    //주파수를 얻으면 주기를 알 수 있다?
    double t=4.5; // 4.5DIV
    double Vmax = OsciSetup::volt ;
    double T=t*OsciSetup::time; // 4.5DIV*()/DIV = 주기
    double w = 2*(M_PI)*(1/T); //각 진동수 생성
    QVector<double> time(500), y(500);
    for (int i=0; i<500; ++i)
    {
      time[i] = i*OsciSetup::time;
      y[i] = Vmax*sin(w*time[i]); // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->freqCustomPlot->addGraph();
    ui->freqCustomPlot->graph(0)->setData(time, y);
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
    ui->freqCustomPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->freqCustomPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->freqCustomPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->freqCustomPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->freqCustomPlot->xAxis->grid()->setSubGridVisible(true);
    ui->freqCustomPlot->yAxis->grid()->setSubGridVisible(true);
    ui->freqCustomPlot->replot();
}
