#ifndef MONTHLYGOALS_H
#define MONTHLYGOALS_H

#include <QDialog>

namespace Ui {
class monthlygoals;
}

class monthlygoals : public QDialog
{
    Q_OBJECT

public:
    explicit monthlygoals(int userId, QWidget *parent = nullptr);  // pass userId from homepage
    ~monthlygoals();

private slots:
    void onSubmitClicked();

private:
    Ui::monthlygoals *ui;
    int currentUserId;  // ✅ only here
    void showMessage(const QString &msg);  // ✅ Add this line
};

#endif // MONTHLYGOALS_H
