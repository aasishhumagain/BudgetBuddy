#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QDialog>

namespace Ui {
class transactions;
}

class transactions : public QDialog
{
    Q_OBJECT

public:
    explicit transactions(QWidget *parent = nullptr, int userId = -1); // userId passed
    ~transactions();

private slots:
    void on_buttonSubmit_clicked();
    void on_buttonBack_clicked();

private:
    Ui::transactions *ui;
    int currentUserId; // store userId
    void showMessage(const QString &msg);
};

#endif // TRANSACTIONS_H
