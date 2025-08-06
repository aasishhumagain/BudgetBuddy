#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QDialog>

namespace Ui {
class profilepage;
}

class profilepage : public QDialog
{
    Q_OBJECT

public:
    explicit profilepage(int userId, QWidget *parent = nullptr);
    ~profilepage();

private slots:
    void on_buttonChangePassword_clicked();
    void on_buttonChangePhoto_clicked();
    void on_buttonBack_clicked();

private:
    Ui::profilepage *ui;
    int currentUserId;

signals:
    void logoutRequested();
};

#endif // PROFILEPAGE_H
