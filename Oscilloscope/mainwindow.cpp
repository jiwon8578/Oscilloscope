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


    osWaveformWinCount = 0;

    osWaveformWin = ui->mdiArea->addSubWindow(freqPlotObj);
    osWaveformWin->resize(400, 400);
    osWaveformWin->show();

    osSetupWin = ui->mdiArea->addSubWindow(osciSetupObj);
    osSetupWin->resize(400, 400);
    osSetupWin->show();
    isOsciSetupOpen = true;

    fftWaveformWin = ui->mdiArea->addSubWindow(fftPlotObj);
    fftWaveformWin->resize(400, 400);
    fftWaveformWin->show();

    fftSetupWin = ui->mdiArea->addSubWindow(fftSetupObj);
    fftSetupWin->resize(400, 400);
    fftSetupWin->show();

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
    isOsciSetupOpen = true;
}

void MainWindow::on_actionOscilloscope_triggered()
{
    if(osWaveformWinCount % 2) {
            osWaveformWin->show();
        } else {
            osWaveformWin->close();
        }
        osWaveformWinCount++;
}


void MainWindow::on_actionOscilloscope_Setup_Window_triggered()
{
    if(osSetupWinCount % 2) {
        osSetupWin->show();
    } else {
        osSetupWin->hide();
    }
    osSetupWinCount++;
}


void MainWindow::on_actionFFT_Waveform_Window_triggered()
{
    if(fftWaveformWinCount % 2) {
        fftWaveformWin->show();
    } else {
        fftWaveformWin->hide();
    }
    fftWaveformWinCount++;
}

void MainWindow::on_actionFFT_Setup_Window_triggered()
{
    if(fftSetupWinCount % 2) {
        fftSetupWin->show();
    } else {
        fftSetupWin->hide();
    }
    fftSetupWinCount++;
}

void MainWindow::on_actionOscilloscope_Setup_triggered()
{
    if(isOsciSetupOpen == false) {
        loadSubWindow_setup(new OsciSetup(this));
    }
}
