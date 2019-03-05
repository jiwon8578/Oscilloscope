#ifndef FREQPLOT_H
#define FREQPLOT_H

#include <QWidget>
#include "oscisetup.h"

class OsciSetup;

namespace Ui {
class freqPlot;
}

class freqPlot : public QWidget
{
    Q_OBJECT

public:
    explicit freqPlot(QWidget *parent = nullptr);
    ~freqPlot();


private slots:
    //void freqPlot::graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
    void on_pushButton_clicked();

private:
    Ui::freqPlot *ui;
    OsciSetup *sender;
    void plotMousePress(QMouseEvent *event);
    void closeEvent(QCloseEvent *event) override;
};

#endif // FREQPLOT_H
