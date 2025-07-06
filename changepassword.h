#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(int userId, QWidget *parent = nullptr);
    ~ChangePassword();

private slots:
    void on_buttonChange_clicked();
    void on_buttonCancel_clicked();
    void toggleOldPasswordVisibility();
    void toggleNewPasswordVisibility();
    void toggleConfirmPasswordVisibility();

private:
    QLineEdit *lineEditOldPassword;
    QLineEdit *lineEditNewPassword;
    QLineEdit *lineEditConfirmPassword;

    QPushButton *buttonChange;
    QPushButton *buttonCancel;

    QPushButton *toggleOldPasswordBtn;
    QPushButton *toggleNewPasswordBtn;
    QPushButton *toggleConfirmPasswordBtn;

    bool oldPassVisible = false;
    bool newPassVisible = false;
    bool confirmPassVisible = false;

    int currentUserId;

    void showMessage(const QString &msg);
};

#endif // CHANGEPASSWORD_H
