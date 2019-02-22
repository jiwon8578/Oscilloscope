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

private slots:
    void about();

private:
    Ui::MainWindow *ui;

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

    void createMenus();
    void createActions();
};

#endif // MAINWINDOW_H
