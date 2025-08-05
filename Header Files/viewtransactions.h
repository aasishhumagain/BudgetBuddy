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
    explicit viewtransactions(QWidget *parent = nullptr, int userId = -1);
    ~viewtransactions();

private slots:
    void onBackButtonClicked();
    void loadTransactionData();
    void on_buttonExport_clicked();
    void showContextMenu(const QPoint &pos);
    void editSelectedTransaction();
    void deleteSelectedTransaction();
    void clearFilters();

private:
    Ui::viewtransactions *ui;
    int currentUserId;

    QString currentUserName;
};

#endif // VIEWTRANSACTIONS_H
