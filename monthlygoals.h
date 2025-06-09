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
    explicit monthlygoals(QWidget *parent = nullptr);
    ~monthlygoals();

private:
    Ui::monthlygoals *ui;
};

#endif // MONTHLYGOALS_H
