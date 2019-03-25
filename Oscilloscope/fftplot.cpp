#include "fftplot.h"
#include "ui_fftplot.h"
#include "mainwindow.h"
#include <QMdiSubWindow>

#include "fftsetup.h"

fftPlot::fftPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fftPlot)
{
    ui->setupUi(this);
    createfftPlot();
    fftset = new fftsetup;
}

fftPlot::~fftPlot()
{
    delete ui;
}

void fftPlot::createfftPlot()
{
    QFile file(MainWindow::filename);
        QVector<double> x;
        QVector<double> y;

        //open file
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        //get data from file and stored as text stream
        QTextStream in(&file);

        while (!in.atEnd()) {
             QString line = in.readLine();// read first line and so on
             //qDebug() << line;
              QStringList fields = line.split(',');// split the string

              x.append(fields.at(0).toDouble()*(10^(-6))/fftset->delaytimetext().toDouble());
              y.append(fields.at(1).toDouble()/OsciSetup::volt);

        }
        // create graph and assign data to it:
        ui->fftCustomPlot->addGraph();
        ui->fftCustomPlot->graph(0)->setData(x, y);
        // make X-axis unit
        QSharedPointer<QCPAxisTickerFixed> fixedxTicker(new QCPAxisTickerFixed);
        ui->fftCustomPlot->xAxis->setTicker(fixedxTicker);
        fixedxTicker->setTickStep(OsciSetup::time);
        fixedxTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);
        // make Y-axis unit
        QSharedPointer<QCPAxisTickerFixed> fixedyTicker(new QCPAxisTickerFixed);
        ui->fftCustomPlot->yAxis->setTicker(fixedyTicker);
        fixedyTicker->setTickStep(OsciSetup::volt);
        fixedyTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);

        // give the axes some labels:
        ui->fftCustomPlot->xAxis->setLabel("time");
        ui->fftCustomPlot->yAxis->setLabel("volt");

        // set axes ranges, so we see all data:
        double min = *std::min_element(y.begin(), y.end()); //y값 최소
        double max = *std::max_element(y.begin(), y.end()); //y값 최대
        ui->fftCustomPlot->xAxis->setRange(x.front(), x.back());
        ui->fftCustomPlot->yAxis->setRange(min, max);

        // replot graph
        ui->fftCustomPlot->replot();


}

QMdiSubWindow *MainWindow::fftWaveformWin;

void fftPlot::closeEvent(QCloseEvent *event)
{
    MainWindow::fftWaveformWin->hide();
    event->ignore();
}


