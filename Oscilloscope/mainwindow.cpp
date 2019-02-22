#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createMenus();
    createActions();

    setWindowTitle("Oscilloscope");
    resize(1920, 1080);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus()
{
    //Cursor Menu
    cursorMenu = menuBar()->addMenu("Cursor");
    noneAct = cursorMenu->addAction("None");
    crossAct = cursorMenu->addAction("Cross");
    verticalAct = cursorMenu->addAction("Vertical");
    horizontalAct = cursorMenu->addAction("Horizontal");

    //Acquire Menu
    acquireMenu = menuBar()->addMenu("Acquire");
    startAct = acquireMenu->addAction("Start");
    stopAct = acquireMenu->addAction("Stop");
    acquireMenu->addSeparator();
    zoomInAct = acquireMenu->addAction("Zoom in");
    zoomOutAct = acquireMenu->addAction("Zoom out");
    acquireMenu->addSeparator();
    acquisitionAct = acquireMenu->addAction("Acquisition");
    interpolationAct = acquireMenu->addAction("Interpolation");
    autoSetupAct = acquireMenu->addAction("Auto setup");

    //Measure Menu
    measureMenu = menuBar()->addMenu("Measure");

    //Measure Menu - Oscilloscope Vertical Submenu
    osciVerticalMenu = measureMenu->addMenu("Oscilloscope Vertical");
    maximumAct = osciVerticalMenu->addAction("Maximum");
    minimunAct = osciVerticalMenu->addAction("Minimum");
    peakToPeakAct = osciVerticalMenu->addAction("Peak to Peak");
    topAct = osciVerticalMenu->addAction("Top");
    baseAct = osciVerticalMenu->addAction("Base");
    rmsAct = osciVerticalMenu->addAction("RMS");
    amplitudeAct = osciVerticalMenu->addAction("Amplitude");
    meanAct = osciVerticalMenu->addAction("Mean");
    cycleMeanAct = osciVerticalMenu->addAction("Cycle Mean");
    preshootAct = osciVerticalMenu->addAction("Preshoot");

    //Measure Menu - Oscilloscope Horizontal Submenu
    osciHorizontalMenu = measureMenu->addMenu("Oscilloscope Horizontal");
    periodAct = osciHorizontalMenu->addAction("Period");
    frequencyAct = osciHorizontalMenu->addAction("Frequency");
    riseTimeAct = osciHorizontalMenu->addAction("Rise Time");
    fallTimeAct = osciHorizontalMenu->addAction("Fall Time");
    pDutyCycleAct = osciHorizontalMenu->addAction("+Duty Cycle");
    nDutyCycleAct = osciHorizontalMenu->addAction("-Duty Cycle");
    pPulseWidthAct = osciHorizontalMenu->addAction("+Pulse Width");
    nPulseWidthAct = osciHorizontalMenu->addAction("-Pulse Width");

    measureMenu->addSeparator();

    //Measure Menu - FFT Measurement Submenu
    fftMeasurementMenu = measureMenu->addMenu("FFT Measurement");
    snrAct = fftMeasurementMenu->addAction("SNR");
    thdAct = fftMeasurementMenu->addAction("THD");
    enobAct = fftMeasurementMenu->addAction("ENOB");
    sfdrAct = fftMeasurementMenu->addAction("SFDR");
    sinadAct = fftMeasurementMenu->addAction("SINAD");
    totalPowerAct = fftMeasurementMenu->addAction("TotalPower");
    peakFrequencyAct = fftMeasurementMenu->addAction("Peak Frequency");

    measureMenu->addSeparator();
    clearDisplayAct = measureMenu->addAction("Clear display");

    //Help Menu
    helpMenu = menuBar()->addMenu("Help");
    contentsAct = helpMenu->addAction("Contents");
    aboutAct = helpMenu->addAction("About..");
}

void MainWindow::about()
{
    AboutDialog aboutDialog;
    aboutDialog.exec();
}

void MainWindow::createActions()
{
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}
