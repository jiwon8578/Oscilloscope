#ifndef FFTPLOT_H
#define FFTPLOT_H

#include <QWidget>

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
    void createfftPlot();
};

#endif // FFTPLOT_H
