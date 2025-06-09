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
    explicit transactions(QWidget *parent = nullptr);
    ~transactions();

private slots:
    void on_buttonSubmit_clicked();

private:
    Ui::transactions *ui;
    void showMessage(const QString &msg);
};

#endif // TRANSACTIONS_H
