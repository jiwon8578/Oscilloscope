#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "fftsetup.h"
#include "fftplot.h"
#include "freqplot.h"
#include "oscisetup.h"
#include <QCursor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //static bool isOsciSetupOpen;

    static QMdiSubWindow *osWaveformWin;
    static QMdiSubWindow *osSetupWin;
    static QMdiSubWindow *fftWaveformWin;
    static QMdiSubWindow *fftSetupWin;

private slots:
    void on_actionOscilloscope_triggered();
    void on_actionOscilloscope_Setup_triggered();
    void on_actionOscilloscope_Setup_Window_triggered();
    void on_actionFFT_Waveform_Window_triggered();
    void on_actionFFT_Setup_Window_triggered();

    void on_actionArrange_All_Window_triggered();

    void on_actionFull_Screen_triggered();

    void on_actionNone_triggered();

    void on_actionCross_triggered();

    void on_actionVertical_triggered();

    void on_actionHorizontal_triggered();

    void on_actionTransducer_Setup_triggered();

    void on_actionTest_Target_Setup_triggered();

    void on_actionScreen_Capture_triggered();

    void on_actionDelete_Setup_triggered();

private:
    Ui::MainWindow *ui;

    void loadSubWindow_plot(QWidget *widget);
    void loadSubWindow_setup(QWidget *widget);
    void loadSubWindow_fftsetup(QWidget *widget);

    freqPlot *freqPlotObj = new freqPlot;
    OsciSetup *osciSetupObj = new OsciSetup;
    fftPlot *fftPlotObj = new fftPlot;
    fftsetup *fftSetupObj = new fftsetup;
    QCursor *qcursor;

    unsigned int imageCount = 1;
};

#endif // MAINWINDOW_H
