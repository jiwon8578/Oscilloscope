#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static bool isOsciSetupOpen;

private slots:
    void about();
    void osciSetupFunc();

private:
    Ui::MainWindow *ui;
    //File을 만들어볼게요.
    QMenu *file;
    QAction *load_setups;
    QAction *save_setups;
    QAction *open_file;
    QAction *save_file;
    QAction *print;
    QAction *exit;

    //VIEW를 만들어볼게요.
    QMenu *view;
    QAction *osWaveFoam;
    QAction *osSetupWindow;
    QAction *FFTWaveWindow;
    QAction *FFTSetWindow;
    QAction *toolBar;
    QAction *arrangeAllWindow;
    QAction *fullScreen;

    //Setup을 만들어볼게요.
    QMenu *setup;
    QAction *osSetup;
    QAction *fftSetup;
    QAction *resetDefault;

    //Utility를 만들어볼게요.
    QMenu *utility;
    QAction *transSetup;
    QAction *testTargetSetup;
    QAction *screenCapture;
    QAction *deleteSetup;

    //Cursor Menu
    QMenu *cursorMenu;
    QAction *noneAct;
    QAction *crossAct;
    QAction *verticalAct;
    QAction *horizontalAct;

    //Acquire Menu
    QMenu *acquireMenu;
    QAction *startAct;
    QAction *stopAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *acquisitionAct;
    QAction *interpolationAct;
    QAction *autoSetupAct;

    //Measure Menu
    QMenu *measureMenu;
    QMenu *osciVerticalMenu; //submenu
    QAction *maximumAct;
    QAction *minimunAct;
    QAction *peakToPeakAct;
    QAction *topAct;
    QAction *baseAct;
    QAction *rmsAct;
    QAction *amplitudeAct;
    QAction *meanAct;
    QAction *cycleMeanAct;
    QAction *preshootAct;
    QMenu *osciHorizontalMenu; //submenu
    QAction *periodAct;
    QAction *frequencyAct;
    QAction *riseTimeAct;
    QAction *fallTimeAct;
    QAction *pDutyCycleAct;
    QAction *nDutyCycleAct;
    QAction *pPulseWidthAct;
    QAction *nPulseWidthAct;
    QMenu *fftMeasurementMenu; //submenu
    QAction *snrAct;
    QAction *thdAct;
    QAction *enobAct;
    QAction *sfdrAct;
    QAction *sinadAct;
    QAction *totalPowerAct;
    QAction *peakFrequencyAct;
    QAction *clearDisplayAct;

    //Help Menu
    QMenu *helpMenu;
    QAction *contentsAct;
    QAction *aboutAct;

    //Make plot
    QWidget *customPlot;

    void menubars();
    void createMenus();
    void createActions();
    void loadSubWindow_plot(QWidget *widget);
    void loadSubWindow_setup(QWidget *widget);
};

#endif // MAINWINDOW_H
