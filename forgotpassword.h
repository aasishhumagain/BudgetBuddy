#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class ForgotPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    ~ForgotPassword();

private slots:
    void on_buttonReset_clicked();
    void on_buttonCancel_clicked();
    void toggleNewPasswordVisibility();
    void toggleConfirmPasswordVisibility();

private:
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditNewPassword;
    QLineEdit *lineEditConfirmPassword;
    QPushButton *buttonReset;
    QPushButton *buttonCancel;
    QPushButton *toggleNewPasswordBtn;
    QPushButton *toggleConfirmPasswordBtn;

    bool newPassVisible = false;
    bool confirmPassVisible = false;

    void showMessage(const QString &msg);
};

#endif // FORGOTPASSWORD_H
