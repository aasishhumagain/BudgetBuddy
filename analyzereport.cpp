#include "analyzereport.h"
#include "ui_analyzereport.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QSqlQuery>
#include <QSqlError>
#include <QVBoxLayout>
#include <QDate>
analyzereport::analyzereport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyzereport)
{
    ui->setupUi(this);

    // Populate month combo
    QStringList months = {"January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};
    ui->comboBoxMonth->addItems(months);

    // Set current year
    int currentYear = QDate::currentDate().year();
    ui->spinBoxYear->setRange(2000, 2100);
    ui->spinBoxYear->setValue(currentYear);

    connect(ui->buttonBack, &QPushButton::clicked, this, &analyzereport::onBackButtonClicked);
    connect(ui->buttonFilter, &QPushButton::clicked, this, &analyzereport::onFilterClicked);

    // Draw for current month/year by default
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
    QString selectedMonth = ui->comboBoxMonth->currentText();
    int selectedYear = ui->spinBoxYear->value();
    generatePieChart(selectedMonth, selectedYear);
}

void analyzereport::generatePieChart(const QString &month, int year)
{
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

    // Format month as two-digit (e.g., "06" for June)
    int monthIndex = ui->comboBoxMonth->currentIndex() + 1;
    QString formattedMonth = QString("%1").arg(monthIndex, 2, 10, QChar('0'));

    query.bindValue(":month", formattedMonth);
    query.bindValue(":year", QString::number(year));

    if (!query.exec()) {
        qDebug() << "Chart Query Error:" << query.lastError().text();
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

    // Remove old chart
    QLayoutItem *child;
    while ((child = ui->chartWidget->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->chartWidget);
    layout->addWidget(chartView);
}
