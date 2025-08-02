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
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>


analyzereport::analyzereport(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::analyzereport),
    currentUserId(userId)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->setWindowState(Qt::WindowMaximized);

    QStringList months = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    ui->comboBoxMonth->addItems(months);

    ui->spinBoxYear->setRange(2000, 2100);
    ui->spinBoxYear->setValue(QDate::currentDate().year());

    connect(ui->buttonBack, &QPushButton::clicked, this, &analyzereport::onBackButtonClicked);
    connect(ui->buttonFilter, &QPushButton::clicked, this, &analyzereport::onFilterClicked);
    ui->comboBoxChartType->addItems({"Category Pie Chart", "Income vs Expense Bar Chart"});
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

    QString chartType = ui->comboBoxChartType->currentText();
    if (chartType == "Income vs Expense Bar Chart") {
        generateBarChart(month, year);
    } else {
        generatePieChart(month, year);
    }
}

void analyzereport::generateBarChart(const QString &month, int year)
{
    int monthIndex = ui->comboBoxMonth->currentIndex() + 1;
    QString formattedMonth = QString("%1").arg(monthIndex, 2, 10, QChar('0'));

    double totalIncome = 0.0, totalExpense = 0.0;
    QSqlQuery query;

    query.prepare(R"(
        SELECT SUM(amount)
        FROM transactions
        WHERE type = 'Income'
          AND user_id = :userId
          AND strftime('%m', date) = :month
          AND strftime('%Y', date) = :year
    )");
    query.bindValue(":userId", currentUserId);
    query.bindValue(":month", formattedMonth);
    query.bindValue(":year", QString::number(year));
    if (query.exec() && query.next())
        totalIncome = query.value(0).toDouble();

    query.prepare(R"(
        SELECT SUM(amount)
        FROM transactions
        WHERE type = 'Expense'
          AND user_id = :userId
          AND strftime('%m', date) = :month
          AND strftime('%Y', date) = :year
    )");
    query.bindValue(":userId", currentUserId);
    query.bindValue(":month", formattedMonth);
    query.bindValue(":year", QString::number(year));
    if (query.exec() && query.next())
        totalExpense = query.value(0).toDouble();

    QBarSet *set = new QBarSet("Amount");
    *set << totalIncome << totalExpense;

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QStringList categories;
    categories << "Income" << "Expense";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Income vs Expense - " + month + " " + QString::number(year));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    chart->createDefaultAxes();
    chart->legend()->setVisible(false);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

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

void analyzereport::generatePieChart(const QString &month, int year)
{
    int monthIndex = ui->comboBoxMonth->currentIndex() + 1;
    QString formattedMonth = QString("%1").arg(monthIndex, 2, 10, QChar('0'));


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
    if (incomeQuery.exec() && incomeQuery.next())
        totalIncome = incomeQuery.value(0).toDouble();

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
    if (expenseQuery.exec() && expenseQuery.next())
        totalExpense = expenseQuery.value(0).toDouble();

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
    if (goalQuery.exec() && goalQuery.next())
        goalAmount = goalQuery.value(0).toDouble();

    ui->labelTotalIncome->setText("Total Income: " + QString::number(totalIncome, 'f', 2));
    ui->labelTotalExpenses->setText("Total Expenses: " + QString::number(totalExpense, 'f', 2));
    ui->labelTotalMonthlyGoal->setText("Total Monthly Goal: " + QString::number(goalAmount, 'f', 2));
    double remaining = goalAmount - totalExpense;
    double income_remaining = totalIncome - totalExpense;
    ui->labelRemainingBudget->setText("Remaining Budget: " + QString::number(remaining, 'f', 2));
    ui->labelNetBalance->setText("Remaining Net Balance:: " + QString::number(income_remaining, 'f', 2));


    double netBalance = totalIncome - totalExpense;
    ui->labelNetBalance->setText("Income - Expenses: " + QString::number(netBalance, 'f', 2));

    QPieSeries *series = new QPieSeries();
    double totalCategoryExpense = 0.0;
    QVector<QPair<QString, double>> categoryData;

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
        totalCategoryExpense += amount;
        categoryData.append({category, amount});
    }

    if (categoryData.isEmpty()) {
        ui->labelHoverInfo->setText("No expense data to show.");
        ui->labelWarnings->clear();
        return;
    }

    for (const auto &entry : categoryData) {
        QPieSlice *slice = series->append(entry.first, entry.second);

        if (totalCategoryExpense > 0) {
            double percentage = (entry.second / totalCategoryExpense) * 100.0;
            QString tooltip = QString("%1: %2 (%3%)")
                                  .arg(entry.first)
                                  .arg(entry.second, 0, 'f', 2)
                                  .arg(QString::number(percentage, 'f', 1));

            slice->setLabel(tooltip);
            slice->setLabelVisible(true);

            connect(slice, &QPieSlice::hovered, this, [=](bool hovered) {
                if (hovered)
                    ui->labelHoverInfo->setText(tooltip);
                else
                    ui->labelHoverInfo->clear();
            });
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Expenses in " + month + " " + QString::number(year));
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

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

    if (goalAmount > 0 && totalExpense > goalAmount) {
        ui->labelWarnings->setText("⚠️ Spending exceeded monthly goal!");
        ui->labelWarnings->setStyleSheet("QLabel { color : red; font-weight: bold; }");
    } else {
        ui->labelWarnings->clear();
    }
}
