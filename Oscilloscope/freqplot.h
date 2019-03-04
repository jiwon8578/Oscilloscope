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
    QLineEdit *test;
    ~freqPlot();

private slots:

    void on_pushButton_clicked();

private:
    Ui::freqPlot *ui;
    OsciSetup *sender;
};

#endif // FREQPLOT_H
