#ifndef MONTHLYGOALS_H
#define MONTHLYGOALS_H

#include <QDialog>

namespace Ui {
class monthlygoals;
}

class monthlygoals : public QDialog
{
    Q_OBJECT

public:
    explicit monthlygoals(int userId, QWidget *parent = nullptr);
    ~monthlygoals();

private slots:
    void onSubmitClicked();
    void on_buttonBack_clicked();

private:
    Ui::monthlygoals *ui;
    int currentUserId;
    void showMessage(const QString &msg);
};

#endif // MONTHLYGOALS_H
