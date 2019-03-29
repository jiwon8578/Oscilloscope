#ifndef FREQPLOT_H
#define FREQPLOT_H

#include <QWidget>
#include "oscisetup.h"
#include <QObject>
#include <qcustomplot.h>

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
    void on_pushButton_clicked();
    void plotMousePress(QMouseEvent *event);

private:
    Ui::freqPlot *ui;
    OsciSetup *sender;
    QCPItemText *textItem;
    void closeEvent(QCloseEvent *event) override;
};

#endif // FREQPLOT_H
