#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_buttonCreateAccount_clicked();
    void on_checkBoxShowPassword_toggled(bool checked);

private:
    Ui::signup *ui;
    void showMessage(const QString &msg);
};

#endif // SIGNUP_H
