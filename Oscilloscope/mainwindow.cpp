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

    //createMenus();
    //createActions();

    osSetupWin = ui->mdiArea->addSubWindow(fftSetupObj);
    osSetupWin->resize(400, 400);
    osSetupWin->show();

    loadSubWindow_plot(new freqPlot(this));
    //loadSubWindow_plot(new fftPlot(this));

    loadSubWindow_setup(new OsciSetup(this));
    loadSubWindow_setup(new fftsetup(this));

    setWindowTitle("Oscilloscope");
    resize(1920, 1080);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::osciSetupFunc()
{
    if(isOsciSetupOpen == false) {
        loadSubWindow_setup(new OsciSetup(this));
    }
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
    if(osSetupWinCount % 2) {
            osSetupWin->show();
        } else {
            osSetupWin->hide();
        }
        osSetupWinCount++;
}
