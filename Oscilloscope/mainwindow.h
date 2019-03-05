#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "fftsetup.h"

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
    void on_actionOscilloscope_triggered();
    void on_actionOscilloscope_Setup_triggered();

private:
    Ui::MainWindow *ui;

    void loadSubWindow_plot(QWidget *widget);
    void loadSubWindow_setup(QWidget *widget);
    void loadSubWindow_fftsetup(QWidget *widget);

    int osSetupWinCount = 0;

    QMdiSubWindow *osSetupWin;
    fftsetup *fftSetupObj = new fftsetup;

};

#endif // MAINWINDOW_H
