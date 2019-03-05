#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "fftsetup.h"
#include "fftplot.h"
#include "freqplot.h"
#include "oscisetup.h"

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
    static QMdiSubWindow *osWaveformWin;
    static int osWaveformWinCount;

private slots:
    void on_actionOscilloscope_triggered();
    void on_actionOscilloscope_Setup_triggered();

    void on_actionOscilloscope_Setup_Window_triggered();

    void on_actionFFT_Waveform_Window_triggered();

    void on_actionFFT_Setup_Window_triggered();

private:
    Ui::MainWindow *ui;

    void loadSubWindow_plot(QWidget *widget);
    void loadSubWindow_setup(QWidget *widget);
    void loadSubWindow_fftsetup(QWidget *widget);


    int osSetupWinCount = 0;
    int fftWaveformWinCount = 0;
    int fftSetupWinCount = 0;


    QMdiSubWindow *osSetupWin;
    QMdiSubWindow *fftWaveformWin;
    QMdiSubWindow *fftSetupWin;

    freqPlot *freqPlotObj = new freqPlot;
    OsciSetup *osciSetupObj = new OsciSetup;
    fftPlot *fftPlotObj = new fftPlot;
    fftsetup *fftSetupObj = new fftsetup;
};

#endif // MAINWINDOW_H
