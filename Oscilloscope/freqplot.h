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

public slots:
    void horizontalState();
    void verticalState();
    void crossState();

private slots:
    void on_pushButton_clicked();
    void plotMousePress(QMouseEvent *event);
    double getX(QMouseEvent *event);
    double getY(QMouseEvent *event);
    void drawLines();

private:
    Ui::freqPlot *ui;
    OsciSetup *sender;
    QCPItemText *textItem;
    void closeEvent(QCloseEvent *event) override;
    double x;
    double y;
    QString currentState;

    QCPItemLine *item;
    QCPItemLine *item2;

};

#endif // FREQPLOT_H
