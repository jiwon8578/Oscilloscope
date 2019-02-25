#ifndef OSCISETUP_H
#define OSCISETUP_H

#include <QWidget>

namespace Ui {
class OsciSetup;
}

class OsciSetup : public QWidget
{
    Q_OBJECT

public:
    explicit OsciSetup(QWidget *parent = nullptr);
    ~OsciSetup();

    QString currentText() const; //test
private:
    Ui::OsciSetup *ui;
};

#endif // OSCISETUP_H
