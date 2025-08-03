#ifndef ANALYZEREPORT_H
#define ANALYZEREPORT_H

#include <QDialog>
#include <QDate>

namespace Ui {
class analyzereport;
}

class analyzereport : public QDialog
{
    Q_OBJECT

public:
    explicit analyzereport(int userId, QWidget *parent = nullptr);
    ~analyzereport();

private slots:
    void onBackButtonClicked();
    void onFilterClicked();

private:
    void generatePieChart(const QDate &fromDate, const QDate &toDate);
    void generateBarChart(const QDate &fromDate, const QDate &toDate);

    Ui::analyzereport *ui;
    int currentUserId;
};

#endif // ANALYZEREPORT_H
