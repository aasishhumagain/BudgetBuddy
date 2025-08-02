#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(int userId, QWidget *parent = nullptr);
    ~ChangePassword();

private slots:
    void on_buttonChange_clicked();
    void on_buttonCancel_clicked();
    void on_checkBoxShowPassword_toggled(bool checked);

private:
    int currentUserId;

    QLineEdit *lineEditOldPassword;
    QLineEdit *lineEditNewPassword;
    QLineEdit *lineEditConfirmPassword;

    QPushButton *buttonChange;
    QPushButton *buttonCancel;

    QCheckBox *checkBoxShowPassword;

    void showMessage(const QString &msg);
};
#endif // CHANGEPASSWORD_H
