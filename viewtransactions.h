#ifndef VIEWTRANSACTIONS_H
#define VIEWTRANSACTIONS_H

#include <QDialog>

namespace Ui {
class viewtransactions;
}

class viewtransactions : public QDialog
{
    Q_OBJECT   // ✅ Must be here!

public:
    explicit viewtransactions(QWidget *parent = nullptr, int userId = -1);
    ~viewtransactions();

private slots:
    void onBackButtonClicked();
    void loadTransactionData();
    void on_buttonExport_clicked();

private:
    Ui::viewtransactions *ui;
    int currentUserId;

    QString currentUserName;   // ✅ This is fine now!
};

#endif // VIEWTRANSACTIONS_H
