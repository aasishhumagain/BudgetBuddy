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
    explicit monthlygoals(QWidget *parent = nullptr);
    ~monthlygoals();

private slots:
    void on_buttonSubmit_clicked();

private:
    Ui::monthlygoals *ui;
    void showMessage(const QString &msg);
};

#endif // MONTHLYGOALS_H
