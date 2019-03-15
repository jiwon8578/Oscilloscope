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

void freqPlot::on_pushButton_clicked()
{
    QFile file("C:/Users/dmlru/OneDrive/project/Oscilloscope/open_adc.csv");
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
        ui->freqCustomPlot->xAxis->setRange(x.front(), x.back()*1.2);
        ui->freqCustomPlot->yAxis->setRange(min, max);

        // replot graph
        ui->freqCustomPlot->replot();


//    // make grid
//    QVector<double> time(501), volt(501);
//    for (int j=0; j<500; ++j)
//    {
//        time[j]= OsciSetup::time*j;
//        volt[j]= OsciSetup::volt*j;
//    }

//    ui->freqCustomPlot->graph(1)->setData(time, volt);
//    ui->freqCustomPlot->graph(1)->rescaleAxes();

//    QCPBars *bars1 = new QCPBars(ui->freqCustomPlot->xAxis, ui->freqCustomPlot->yAxis);
//    bars1->setWidth(9/(double)time.size());
//    bars1->setData(time, volt);
//    bars1->setPen(Qt::NoPen);
//    bars1->setBrush(QColor(10, 140, 70, 160));
//    ui->freqCustomPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    ui->freqCustomPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    ui->freqCustomPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    ui->freqCustomPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    ui->freqCustomPlot->xAxis->grid()->setSubGridVisible(true);
//    ui->freqCustomPlot->yAxis->grid()->setSubGridVisible(true);
//    ui->freqCustomPlot->replot();

    //time information
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
