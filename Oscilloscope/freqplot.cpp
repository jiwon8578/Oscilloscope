#include "freqplot.h"
#include "ui_freqplot.h"
#include "qmath.h"
#include "oscisetup.h"
#include "mainwindow.h"

#include <QMdiSubWindow>
#include <QFile>
#include <algorithm>
#include <vector>
#include <QMessageBox>

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
    ui->setupUi(this);
    setWindowTitle("Oscilloscope");
    textItem = new QCPItemText(ui->freqCustomPlot);

    connect(ui->freqCustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(getX(QMouseEvent *)));
    connect(ui->freqCustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(getY(QMouseEvent *)));
    connect(ui->freqCustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(drawLines()));
    connect(ui->freqCustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(plotMousePress(QMouseEvent*)));
    ui->freqCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                     QCP::iSelectLegend | QCP::iSelectPlottables);


    item = new QCPItemLine(ui->freqCustomPlot);
    item->setVisible(false);
    item->setPen(QPen(Qt::gray, 1.0, Qt::DashLine));

    item2 = new QCPItemLine(ui->freqCustomPlot);
    item2->setVisible(false);
    item2->setPen(QPen(Qt::gray, 1.0, Qt::DashLine));

    //Background-Color
    ui->freqCustomPlot->setBackground(QBrush(QColor("#2d2d2d")));

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
        ui->freqCustomPlot->graph()->setPen(QPen(Qt::green));

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

void freqPlot::plotMousePress(QMouseEvent *event)
{

     double xCoord = ui->freqCustomPlot->xAxis->pixelToCoord(event->localPos().x());
     double yCoord = ui->freqCustomPlot->yAxis->pixelToCoord(event->localPos().y());

     textItem->setText(QString("(%1, %2)").arg(xCoord).arg(yCoord));
     textItem->position->setCoords(QPointF(xCoord, yCoord));
     textItem->setFont(QFont(font().family(), 8));
     textItem->setPen(QPen(Qt::white));
     textItem->setBrush(QBrush(Qt::white));
            //textItem->setBrush(Qt::red);
     ui->freqCustomPlot->replot();
}

void freqPlot::horizontalState() {
    currentState = "cursorHorizontal";
}

void freqPlot::verticalState() {
    currentState = "cursorVertical";
}

void freqPlot::crossState() {
    currentState = "cursorCross";
}

double freqPlot::getX(QMouseEvent *event) {
    x = ui->freqCustomPlot->xAxis->pixelToCoord(event->localPos().x());
    return x;
}

double freqPlot::getY(QMouseEvent *event) {
    y = ui->freqCustomPlot->yAxis->pixelToCoord(event->localPos().y());
    return y;
}

void freqPlot::drawLines() {
    item->setVisible(false);
    item2->setVisible(false);

    if(currentState == "cursorHorizontal") {
        item->start->setCoords(-100, y);
        item->end->setCoords(100, y);
        item->setVisible(true);

    } else if(currentState == "cursorVertical") {
        item->start->setCoords(x, -100);
        item->end->setCoords(x, 100);
        item->setVisible(true);

    } else if(currentState == "cursorCross") {
        item->start->setCoords(-100, y);
        item->end->setCoords(100, y);
        item->setVisible(true);

        item2->start->setCoords(x, -100);
        item2->end->setCoords(x, 100);
        item2->setVisible(true);
    }

    ui->freqCustomPlot->replot();
}
