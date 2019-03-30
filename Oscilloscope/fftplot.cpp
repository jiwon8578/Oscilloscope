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
    setWindowTitle("FFT");

    fftset = new fftsetup;

    ui->fftCustomPlot->setBackground(QBrush(QColor("#2d2d2d")));  
}

fftPlot::~fftPlot()
{
    delete ui;
}

QMdiSubWindow *MainWindow::fftWaveformWin;

void fftPlot::closeEvent(QCloseEvent *event)
{
    MainWindow::fftWaveformWin->hide();
    event->ignore();
}



void fftPlot::on_start_clicked()
{
    QString filename_fftPlot = MainWindow::filename;

    QFile file(filename_fftPlot);
        QVector<double> x;
        QVector<double> y;

        //open file
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        //get data from file and stored as text stream
        QTextStream in(&file);

        while (!in.atEnd()) {
             QString line = in.readLine();// read first line and so on
             QStringList fields = line.split(',');// split the string
             double target =  *std::max_element(y.begin(), y.end());

             //조건에 만족하는 행 고르기
//             foreach(const QString& var, fields)
//             {
//                if (var.toDouble()==target)
//                {
//                    y.append(var);
//                }
//             }

              // filter 이용해서 찾고자 하는 행 찾을 수 있음!

              x.append(fields.at(0).toDouble()*(10^(-6)));
              y.append(fields.at(1).toDouble());
        //fftset->delaytimetext().toDouble() : fftsetup에서 지정한 변수 사용하고 싶을 때 요렇게!
        }
        // create graph and assign data to it:
        ui->fftCustomPlot->addGraph();
        ui->fftCustomPlot->graph(0)->setData(x, y);
        ui->fftCustomPlot->graph()->setPen(QPen(Qt::green));

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
        //ui->fftCustomPlot->xAxis->setLabel();
        //ui->fftCustomPlot->yAxis->setLabel();

        // set axes ranges, so we see all data:
        double min = *std::min_element(y.begin(), y.end()); //y값 최소
        double max = *std::max_element(y.begin(), y.end()); //y값 최대
        ui->fftCustomPlot->xAxis->setRange(x.front(), x.back());
        ui->fftCustomPlot->yAxis->setRange(min, max);

        // replot graph
        ui->fftCustomPlot->replot();

}
