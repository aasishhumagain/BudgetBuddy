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
    void on_buttonLogout_clicked();

private:
    Ui::profilepage *ui;
    int currentUserId; // ✅ Only need this now!

signals:
    void logoutRequested();
};

#endif // PROFILEPAGE_H
