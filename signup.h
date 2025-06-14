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
    void on_buttonTogglePassword_clicked();

private:
    Ui::signup *ui;
    void showMessage(const QString &msg);

    bool passwordVisible;
    QString iconClosedPath;
    QString iconOpenPath;
};

#endif // SIGNUP_H
