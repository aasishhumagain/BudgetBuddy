#include "monthlygoals.h"
#include "ui_monthlygoals.h"

monthlygoals::monthlygoals(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::monthlygoals)
{
    ui->setupUi(this);
}

monthlygoals::~monthlygoals()
{
    delete ui;
}
