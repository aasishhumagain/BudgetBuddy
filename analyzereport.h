#ifndef ANALYZEREPORT_H
#define ANALYZEREPORT_H

#include <QDialog>

namespace Ui {
class analyzereport;
}

class analyzereport : public QDialog
{
    Q_OBJECT

public:
    explicit analyzereport(QWidget *parent = nullptr);
    ~analyzereport();

private slots:
    void onBackButtonClicked();
    void onFilterClicked();

private:
    Ui::analyzereport *ui;
    void generatePieChart(const QString &month, int year);
};

#endif // ANALYZEREPORT_H
