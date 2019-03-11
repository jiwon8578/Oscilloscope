#include "freqplot.h"
#include "ui_freqplot.h"
#include "qmath.h"
#include "oscisetup.h"
#include "mainwindow.h"
#include <QMdiSubWindow>
#include <QFile>


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
//    connect(ui->freqfreqCustomPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));
//    ui->freqfreqCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
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
    QFile file("C:/Users/dmlru/OneDrive/project/Oscilloscope/open_fft.csv");
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

              x.append(fields.at(0).toDouble());
              y.append(fields.at(1).toDouble());

        }
        // create graph and assign data to it:
        ui->freqCustomPlot->addGraph();
        ui->freqCustomPlot->graph(0)->setData(x, y);

        // give the axes some labels:
        ui->freqCustomPlot->xAxis->setLabel("time");
        ui->freqCustomPlot->yAxis->setLabel("volt");

        // set axes ranges, so we see all data:
        ui->freqCustomPlot->xAxis->setRange(20, 30);
        ui->freqCustomPlot->yAxis->setRange(-90, 90);

        // replot graph
        ui->freqCustomPlot->replot();


    //클럭을 통해 한 주기 알 수 있음
//    double t=4.5; // 4.5DIV
//    double Vmax = OsciSetup::volt ;
//    double T=t*OsciSetup::time; // 4.5DIV*time/DIV = 주기
//    double w = 2*(M_PI)*(1/T); //각 진동수 생성
//    QVector<double> time(500), y(500);
//    for (int i=0; i<line.size(); ++i)
//    {
//      time[i] = time_test.toDouble;
//      y[i] = Vmax*sin(w*time[i]); // let's plot a quadratic function
//    }
//    // create graph and assign data to it:
//    ui->freqfreqCustomPlot->addGraph();
//    ui->freqfreqCustomPlot->graph(0)->setData(time_test.toDouble, adc_test.toDouble);
//    // give the axes some labels:
//    ui->freqfreqCustomPlot->xAxis->setLabel("Time");
//    ui->freqfreqCustomPlot->yAxis->setLabel("Value");
//    // set axes ranges, so we see all data:
//    ui->freqfreqCustomPlot->xAxis->setRange(0, 10);
//    ui->freqfreqCustomPlot->yAxis->setRange(-10, 10);
//    // make grid
//    QVector<double> x(501), y(501);
//    for (int j=0; j<500; ++j)
//    {
//        x[j]= OsciSetup::time*j;
//        y[j]= OsciSetup::volt*j;
//    }

//    QCPBars *bars1 = new QCPBars(ui->freqfreqCustomPlot->xAxis, ui->freqfreqCustomPlot->yAxis);
//    bars1->setWidth(9/(double)x.size());
//    bars1->setData(x, y);
//    bars1->setPen(Qt::NoPen);
//    bars1->setBrush(QColor(10, 140, 70, 160));
//    ui->freqfreqCustomPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    ui->freqfreqCustomPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
//    ui->freqfreqCustomPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    ui->freqfreqCustomPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
//    ui->freqfreqCustomPlot->xAxis->grid()->setSubGridVisible(true);
//    ui->freqfreqCustomPlot->yAxis->grid()->setSubGridVisible(true);
//    ui->freqfreqCustomPlot->replot();

//    //time information
//    ui->time->setText(OsciSetup::timelabel+OsciSetup::timeunitlabel);
//    ui->volt->setText(OsciSetup::voltlabel+OsciSetup::voltunitlabel);
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
