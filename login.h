#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_buttonLogin_clicked();   // ✅ only declaration here
    void on_buttonSignup_clicked();  // for signup

private:
    Ui::login *ui;
    void showMessage(const QString &message);
};

#endif // LOGIN_H
