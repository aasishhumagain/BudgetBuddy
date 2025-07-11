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

analyzereport::analyzereport(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyzereport),
    currentUserId(userId)
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

    // 1️⃣ Total Income
    double totalIncome = 0.0;
    QSqlQuery incomeQuery;
    incomeQuery.prepare(R"(
        SELECT SUM(amount)
        FROM transactions
        WHERE type = 'Income'
          AND user_id = :userId
          AND strftime('%m', date) = :month
          AND strftime('%Y', date) = :year
    )");
    incomeQuery.bindValue(":userId", currentUserId);
    incomeQuery.bindValue(":month", formattedMonth);
    incomeQuery.bindValue(":year", QString::number(year));
    if (incomeQuery.exec() && incomeQuery.next()) {
        totalIncome = incomeQuery.value(0).toDouble();
    }

    // 2️⃣ Total Expenses
    double totalExpense = 0.0;
    QSqlQuery expenseQuery;
    expenseQuery.prepare(R"(
        SELECT SUM(amount)
        FROM transactions
        WHERE type = 'Expense'
          AND user_id = :userId
          AND strftime('%m', date) = :month
          AND strftime('%Y', date) = :year
    )");
    expenseQuery.bindValue(":userId", currentUserId);
    expenseQuery.bindValue(":month", formattedMonth);
    expenseQuery.bindValue(":year", QString::number(year));
    if (expenseQuery.exec() && expenseQuery.next()) {
        totalExpense = expenseQuery.value(0).toDouble();
    }

    // 3️⃣ Total Monthly Goal
    double goalAmount = 0.0;
    QSqlQuery goalQuery;
    goalQuery.prepare(R"(
        SELECT SUM(amount)
        FROM monthly_goals
        WHERE user_id = :userId
          AND month = :month
          AND year = :year
    )");
    goalQuery.bindValue(":userId", currentUserId);
    goalQuery.bindValue(":month", formattedMonth);
    goalQuery.bindValue(":year", year);
    if (goalQuery.exec() && goalQuery.next()) {
        goalAmount = goalQuery.value(0).toDouble();
    }

    // 4️⃣ Update labels
    ui->labelTotalIncome->setText("Total Income: ₹" + QString::number(totalIncome));
    ui->labelTotalExpenses->setText("Total Expenses: ₹" + QString::number(totalExpense));
    ui->labelTotalMonthlyGoal->setText("Total Monthly Goal: ₹" + QString::number(goalAmount));
    double remaining = goalAmount - totalExpense;
    ui->labelRemainingBudget->setText("Remaining Budget: ₹" + QString::number(remaining));

    // 5️⃣ Pie chart: Expense split by category
    QPieSeries *series = new QPieSeries();
    QSqlQuery catQuery;
    catQuery.prepare(R"(
        SELECT category, SUM(amount)
        FROM transactions
        WHERE type = 'Expense'
          AND user_id = :userId
          AND strftime('%m', date) = :month
          AND strftime('%Y', date) = :year
        GROUP BY category
    )");
    catQuery.bindValue(":userId", currentUserId);
    catQuery.bindValue(":month", formattedMonth);
    catQuery.bindValue(":year", QString::number(year));
    if (!catQuery.exec()) {
        qDebug() << "Chart query failed:" << catQuery.lastError().text();
        return;
    }
    while (catQuery.next()) {
        QString category = catQuery.value(0).toString();
        double amount = catQuery.value(1).toDouble();
        series->append(category, amount);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Expenses in " + month + " " + QString::number(year));
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Clear old chart
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

    // 6️⃣ Check goal exceeded
    if (goalAmount > 0 && totalExpense > goalAmount) {
        ui->labelWarnings->setText("⚠️ Spending exceeded monthly goal!");
        ui->labelWarnings->setStyleSheet("QLabel { color : red; font-weight: bold; }");
    } else {
        ui->labelWarnings->clear();
    }
}
