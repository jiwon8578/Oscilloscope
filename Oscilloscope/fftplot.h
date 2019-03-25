#ifndef FFTPLOT_H
#define FFTPLOT_H

#include <QWidget>

class fftsetup;

namespace Ui {
class fftPlot;
}

class fftPlot : public QWidget
{
    Q_OBJECT

public:
    explicit fftPlot(QWidget *parent = nullptr);
    ~fftPlot();

private:
    Ui::fftPlot *ui;
    fftsetup *fftset;
    void createfftPlot();
    void closeEvent(QCloseEvent *event) override;
};

#endif // FFTPLOT_H
