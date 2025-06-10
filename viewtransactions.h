#ifndef VIEWTRANSACTIONS_H
#define VIEWTRANSACTIONS_H

#include <QDialog>

namespace Ui {
class viewtransactions;
}

class viewtransactions : public QDialog
{
    Q_OBJECT

public:
    explicit viewtransactions(QWidget *parent = nullptr);
    ~viewtransactions();

private:
    Ui::viewtransactions *ui;
    void loadTransactionData(); // function to fill the table
    void onBackButtonClicked();
};

#endif // VIEWTRANSACTIONS_H
