#ifndef OSCISETUP_H
#define OSCISETUP_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class OsciSetup;
}

class OsciSetup : public QWidget
{
    Q_OBJECT

public:
    explicit OsciSetup(QWidget *parent = nullptr);
    //double pushvalue(double x);
    ~OsciSetup();

signals:
    void entered(double);

//private slots:
//    void on_setupButton_clicked();

//public slots:
//    double pushvalue(double x);


private:
    Ui::OsciSetup *ui;
    void closeEvent(QCloseEvent *event) override;
};

#endif // OSCISETUP_H
