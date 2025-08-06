#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class ForgotPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    ~ForgotPassword();

private slots:
    void on_buttonReset_clicked();
    void on_buttonCancel_clicked();
    void on_checkBoxShowPassword_toggled(bool checked);

private:
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditNewPassword;
    QLineEdit *lineEditConfirmPassword;
    QPushButton *buttonReset;
    QPushButton *buttonCancel;
    QCheckBox *checkBoxShowPassword;

    void showMessage(const QString &msg);
};

#endif // FORGOTPASSWORD_H
