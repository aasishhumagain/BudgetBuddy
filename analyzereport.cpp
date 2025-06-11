#include "analyzereport.h"
#include "ui_analyzereport.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>

analyzereport::analyzereport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyzereport)
{
    ui->setupUi(this);

    QStringList months = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    ui->comboBoxMonth->addItems(months);

    ui->spinBoxYear->setRange(2000, 2100);
    ui->spinBoxYear->setValue(QDate::currentDate().year());

    connect(ui->buttonBack, &QPushButton::clicked, this, &analyzereport::onBackButtonClicked);
    connect(ui->buttonFilter, &QPushButton::clicked, this, &analyzereport::onFilterClicked);

    onFilterClicked();
}

analyzereport::~analyzereport()
{
    delete ui;
}

void analyzereport::onBackButtonClicked()
{
    this->close();
}

void analyzereport::onFilterClicked()
{
    QString month = ui->comboBoxMonth->currentText();
    int year = ui->spinBoxYear->value();
    generatePieChart(month, year);
}

void analyzereport::generatePieChart(const QString &month, int year)
{
    int monthIndex = ui->comboBoxMonth->currentIndex() + 1;
    QString formattedMonth = QString("%1").arg(monthIndex, 2, 10, QChar('0'));

    QPieSeries *series = new QPieSeries();
    QSqlQuery query;
    query.prepare(R"(
        SELECT category, SUM(amount)
        FROM transactions
        WHERE type = 'Expense'
          AND strftime('%m', date) = :month
          AND strftime('%Y', date) = :year
        GROUP BY category
    )");

    query.bindValue(":month", formattedMonth);
    query.bindValue(":year", QString::number(year));

    if (!query.exec()) {
        qDebug() << "Chart query failed:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString category = query.value(0).toString();
        double amount = query.value(1).toDouble();
        series->append(category, amount);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Expenses in " + month + " " + QString::number(year));
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Clear layout if already set
    QLayout *oldLayout = ui->chartWidget->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->chartWidget);
    layout->addWidget(chartView);
}
