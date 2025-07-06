#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>

namespace Ui {
class homepage;
}

class homepage : public QDialog
{
    Q_OBJECT

public:
    explicit homepage(int userId, QWidget *parent = nullptr);
    ~homepage();

private slots:
    void on_buttonAddTransaction_clicked();
    void on_buttonViewTransaction_clicked();
    void on_buttonSetGoal_clicked();
    void on_buttonAnalyzeReport_clicked();
    void on_buttonProfile_clicked();
    void handleLogout();
private:
    Ui::homepage *ui;
    int currentUserId;
};

#endif // HOMEPAGE_H
