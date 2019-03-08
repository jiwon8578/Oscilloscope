#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMdiSubWindow>
#include "fftplot.h"
#include "freqplot.h"
#include "oscisetup.h"
#include "transducersetupdialog.h"
#include "testtargetsetupdialog.h"
#include "fftsetup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #454548;"); //background 색상 변경
    setCentralWidget(ui->mdiArea);

    osWaveformWin = ui->mdiArea->addSubWindow(freqPlotObj);
    osWaveformWin->resize(400, 400);
    osWaveformWin->show();

    osSetupWin = ui->mdiArea->addSubWindow(osciSetupObj);
    osSetupWin->resize(400, 400);
    osSetupWin->show();

    fftWaveformWin = ui->mdiArea->addSubWindow(fftPlotObj);
    fftWaveformWin->resize(400, 400);
    fftWaveformWin->show();

    fftSetupWin = ui->mdiArea->addSubWindow(fftSetupObj);
    fftSetupWin->resize(400, 400);
    fftSetupWin->show();

    ui->menuFile->setStyleSheet("QMenu::selected{background-color:white;}");

    setWindowTitle("Oscilloscope");
    resize(1920, 1080);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSubWindow_plot(QWidget *widget) //mdiArea에 sub window를 띄우는 함수 - plot용
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->resize(400,400);
    window->show();
}

void MainWindow::loadSubWindow_setup(QWidget *widget) //mdiArea에 sub window를 띄우는 함수 - setup용
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->resize(400,500);
    window->show();
}

void MainWindow::on_actionOscilloscope_triggered() //view - oscilloscope plot
{
    if(osWaveformWin->isHidden()) {
        osWaveformWin->show();
    } else {
        osWaveformWin->hide();
    }
}


void MainWindow::on_actionOscilloscope_Setup_Window_triggered() //view - oscilloscope setup
{    
    if(osSetupWin->isHidden()) {
        osSetupWin->show();
    } else {
        osSetupWin->hide();
    }
}


void MainWindow::on_actionFFT_Waveform_Window_triggered() //view - fft plot
{
    if(fftWaveformWin->isHidden()) {
        fftWaveformWin->show();
    } else {
      fftWaveformWin->hide();
    }
}

void MainWindow::on_actionFFT_Setup_Window_triggered() //view - fft setup
{
    if(fftSetupWin->isHidden()) {
        fftSetupWin->show();
    } else {
        fftSetupWin->hide();
    }
}

void MainWindow::on_actionOscilloscope_Setup_triggered() //setup - oscilloscope setup
{
    if(osSetupWin->isHidden()) {
        osSetupWin->show();
    }
}

void MainWindow::on_actionArrange_All_Window_triggered() //view - arrange all window
{
    osWaveformWin->move(0, 0);
    if(osWaveformWin->isHidden()) {
        osWaveformWin->show();
    }
    osSetupWin->move(400, 0);
    if(osSetupWin->isHidden()) {
        osSetupWin->show();
    }
    fftWaveformWin->move(800, 0);
    if(fftWaveformWin->isHidden()) {
        fftWaveformWin->show();
    }
    fftSetupWin->move(1200, 0);
    if(fftSetupWin->isHidden()) {
        fftSetupWin->show();
    }
}

void MainWindow::on_actionFull_Screen_triggered() //view - full screen
{
    this->showMaximized();
}

void MainWindow::on_actionNone_triggered()
{
    this->setCursor(QCursor(Qt::BlankCursor));
}

void MainWindow::on_actionCross_triggered()
{
   this->setCursor(QCursor(Qt::CrossCursor));
}


void MainWindow::on_actionVertical_triggered()
{
    this->setCursor(QCursor(Qt::SizeVerCursor));
}

void MainWindow::on_actionHorizontal_triggered()
{
    this->setCursor(QCursor(Qt::SizeHorCursor));
}

void MainWindow::on_actionTransducer_Setup_triggered() //utility - transducer setup
{
    TransducerSetupDialog transducerSetup;
    transducerSetup.exec();
}


void MainWindow::on_actionTest_Target_Setup_triggered() //utility - test target setup
{
    TestTargetSetupDialog testTargetSetup;
    testTargetSetup.exec();
}

void MainWindow::on_actionScreen_Capture_triggered() //utility - screen capture
{
    QPixmap pic = this->grab();
    //pic.save("" + QString::number(imageCount) + ".png"); //""안에 경로 입력
    imageCount++;
}

void MainWindow::on_actionDelete_Setup_triggered()
{

}
