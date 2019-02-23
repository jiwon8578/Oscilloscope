#ifndef FREQPLOT_H
#define FREQPLOT_H

#include <QWidget>

namespace Ui {
class freqPlot;
}

class freqPlot : public QWidget
{
    Q_OBJECT

public:
    explicit freqPlot(QWidget *parent = nullptr);
    ~freqPlot();

private:
    Ui::freqPlot *ui;
    void createfreqPlot();
};

#endif // FREQPLOT_H
