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
    explicit analyzereport(int userId, QWidget *parent = nullptr);  // ✅ update this
    ~analyzereport();

private slots:
    void onBackButtonClicked();
    void onFilterClicked();

private:
    void generatePieChart(const QString &month, int year);

    Ui::analyzereport *ui;
    int currentUserId;  // ✅ to store passed user ID
};

#endif // ANALYZEREPORT_H
