#include "freqplot.h"
#include "ui_freqplot.h"
#include "qmath.h"
#include "oscisetup.h"
#include "mainwindow.h"
#include <QMdiSubWindow>
#include <QFile>
#include <algorithm>
#include <vector>

double OsciSetup::time;
double OsciSetup::volt;
QString OsciSetup::timelabel;
QString OsciSetup::voltlabel;
QString OsciSetup::timeunitlabel;
QString OsciSetup::voltunitlabel;

freqPlot::freqPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::freqPlot)
{
    sender = new OsciSetup;
    //connect(sender,SIGNAL(timeEntered(double)),this,SLOT(on_pushButton_clicked()));
    ui->setupUi(this);
//    connect(ui->freqCustomPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));
//    ui->freqCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
//                                     QCP::iSelectLegend | QCP::iSelectPlottables);

}

freqPlot::~freqPlot()
{
    delete ui;
}

//void freqPlot::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
//{
//  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
//  QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
//  ui->statusBar->showMessage(message, 2500);
//}

QString MainWindow::filename;

void freqPlot::on_pushButton_clicked()
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

              x.append(fields.at(0).toDouble()*(10^(-6))/OsciSetup::time);
              y.append(fields.at(1).toDouble()/OsciSetup::volt);

        }
        // 축 원점 고정?
//        int pxx = ui->freqCustomPlot->yAxis->coordToPixel(0);
//        int pxy = ui->freqCustomPlot->xAxis->coordToPixel(0);
//        ui->freqCustomPlot->xAxis->setOffset(ui->freqCustomPlot->axisRect()->height()-ui->freqCustomPlot->axisRect()->top()+pxx);
//        ui->freqCustomPlot->yAxis->setOffset(ui->freqCustomPlot->axisRect()->left()-pxy);
        // create graph and assign data to it:
        ui->freqCustomPlot->addGraph();
        ui->freqCustomPlot->graph(0)->setData(x, y);
        // make X-axis unit
        QSharedPointer<QCPAxisTickerFixed> fixedxTicker(new QCPAxisTickerFixed);
        ui->freqCustomPlot->xAxis->setTicker(fixedxTicker);
        fixedxTicker->setTickStep(OsciSetup::time);
        fixedxTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);
        // make Y-axis unit
        QSharedPointer<QCPAxisTickerFixed> fixedyTicker(new QCPAxisTickerFixed);
        ui->freqCustomPlot->yAxis->setTicker(fixedyTicker);
        fixedyTicker->setTickStep(OsciSetup::volt);
        fixedyTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);

        // give the axes some labels:
        ui->freqCustomPlot->xAxis->setLabel("time");
        ui->freqCustomPlot->yAxis->setLabel("volt");

        // set axes ranges, so we see all data:
        double min = *std::min_element(y.begin(), y.end()); //y값 최소
        double max = *std::max_element(y.begin(), y.end()); //y값 최대
        ui->freqCustomPlot->xAxis->setRange(x.front(), x.back());
        ui->freqCustomPlot->yAxis->setRange(min, max);

        // replot graph
        ui->freqCustomPlot->replot();


    //time, volt information
    ui->time->setText(OsciSetup::timelabel+OsciSetup::timeunitlabel);
    ui->volt->setText(OsciSetup::voltlabel+OsciSetup::voltunitlabel);
}

QMdiSubWindow *MainWindow::osWaveformWin;

void freqPlot::closeEvent(QCloseEvent *event)
{
    MainWindow::osWaveformWin->hide();
    event->ignore();
}

//void freqPlot::plotMousePress(QMouseEvent *event)
//{
//    QCPAbstractPlottable *plottable = plottableAt(event->pos());

//        // 2. If it is a scatter graph, then I want to determine the data
//        // point under the cursor position.
//        QCPGraph *graph(dynamic_cast<QCPGraph*>(plottable));
//        if (graph != nullptr) {
//            int x = ui->freqCustomPlot->xAxis->pixelToCoord(event->pos().x());
//            auto beginRange = graph->data()->findBegin(x);
//            QToolTip::showText(event->globalPos(),
//                  tr("<table>"
//                       "<tr>"
//                       "<td>%L1:</td>" "<td>%L2</td>"
//                       "</tr>"
//                     "</table>").arg("Index").arg(beginRange->key),
//                   this, rect());
//        } else {
//            QToolTip::hideText();
//        }
//}
