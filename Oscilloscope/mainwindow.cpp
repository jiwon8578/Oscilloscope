#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include <QVBoxLayout>
#include <QMdiSubWindow>
#include "fftplot.h"
#include "freqplot.h"
#include "oscisetup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #454548;"); //background 색상 변경
    setCentralWidget(ui->mdiArea);

    createMenus();
    createActions();

    loadSubWindow_plot(new freqPlot(this));
    loadSubWindow_plot(new fftPlot(this));

    loadSubWindow_setup(new OsciSetup(this));

    setWindowTitle("Oscilloscope");
    resize(1920, 1080);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus()
{
    menuBar()->setStyleSheet("background-color: #454548"); //menubar 색상 변경
    menuBar()->setStyleSheet("color: #FFFFFF"); //menubar 글씨 색상 변경
    //menuBar()->setFont("");

    //FILE만들기.
    file = menuBar() -> addMenu("File");
    load_setups = file -> addAction("Load Setups");
    save_setups = file -> addAction("Save Setups");
    file -> addSeparator();
    open_file = file -> addAction("Open File");
    save_file = file -> addAction("Save File");
    file -> addSeparator();
    print = file -> addAction("Print");
    //exit = file -> addAction("Exit"); // line#44로 대체.

    QAction *quit = new QAction("Exit", this);
    file -> addAction(quit);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);

    //VIEW만들기.
    view = menuBar() -> addMenu("View");
    osWaveFoam = view -> addAction("Oscilloscope Waveform Window");
    osSetupWindow = view -> addAction("Oscilloscope Setup Window");
    view -> addSeparator();
    FFTWaveWindow = view -> addAction("FFT Wavefoam Window");
    FFTSetWindow = view -> addAction("FFT Setup Window");
    view -> addSeparator();
    toolBar = view -> addAction("Tool Bar");
    arrangeAllWindow = view -> addAction("Arrange All Window");
    fullScreen = view -> addAction("Full Screen");

    //setup만들기.
    setup = menuBar() -> addMenu("Setup");
    osSetup = setup -> addAction("Oscilloscope Setup");
    fftSetup = setup -> addAction("FFT Analyzer Setup");
    resetDefault = setup -> addAction("All Setup Reset");

    //utility만들기.
    utility = menuBar() -> addMenu("Utility");
    transSetup = utility -> addAction("Transducer Setup");
    testTargetSetup = utility -> addAction("Test Target Setup");
    screenCapture = utility -> addAction("Screen Capture");
    deleteSetup = utility -> addAction("Delete Setup");

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

void MainWindow::osciSetupFunc()
{
    if(isOsciSetupOpen == false) {
        loadSubWindow_setup(new OsciSetup(this));
    }
}

void MainWindow::createActions()
{
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about); // (변수명, 액션, parent, about함수를 실행시켜라)
    connect(osSetup, &QAction::triggered, this, &MainWindow::osciSetupFunc);
}

void MainWindow::loadSubWindow_plot(QWidget *widget) //mdiArea에 sub window를 띄우는 함수 - plot용
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->resize(320,450);
    window->show();
}

void MainWindow::loadSubWindow_setup(QWidget *widget) //mdiArea에 sub window를 띄우는 함수 - setup용
{
    auto window = ui->mdiArea->addSubWindow(widget);
    window->resize(320,450);
    window->show();
    isOsciSetupOpen = true;
}





