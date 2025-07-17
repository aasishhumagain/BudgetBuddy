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
    explicit analyzereport(int userId, QWidget *parent = nullptr);  // Constructor with user ID
    ~analyzereport();

private slots:
    void onBackButtonClicked();
    void onFilterClicked();

private:
    void generatePieChart(const QString &month, int year);  // Core chart + UI updater

    Ui::analyzereport *ui;
    int currentUserId;  // Stores current user ID for filtering
};

#endif // ANALYZEREPORT_H
