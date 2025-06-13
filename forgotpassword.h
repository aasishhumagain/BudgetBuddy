#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class ForgotPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    ~ForgotPassword();

private slots:
    void on_buttonReset_clicked();
    void on_buttonCancel_clicked();

private:
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditNewPassword;
    QLineEdit *lineEditConfirmPassword;
    QPushButton *buttonReset;
    QPushButton *buttonCancel;

    void showMessage(const QString &msg);
};

#endif // FORGOTPASSWORD_H
