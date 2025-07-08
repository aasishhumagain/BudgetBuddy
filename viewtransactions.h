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
    explicit viewtransactions(QWidget *parent = nullptr, int userId = -1); // 👈 add userId
    ~viewtransactions();

private slots:
    void onBackButtonClicked();
    void on_buttonExport_clicked();

private:
    Ui::viewtransactions *ui;
    int currentUserId; // 👈 store user ID
    void loadTransactionData();
};

#endif // VIEWTRANSACTIONS_H
