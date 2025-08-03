#include "analyzereport.h"
#include "ui_analyzereport.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
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
    this->setWindowFlags(Qt::Window);
    this->setWindowState(Qt::WindowMaximized);

    connect(ui->buttonBack, &QPushButton::clicked, this, &analyzereport::onBackButtonClicked);
    connect(ui->buttonApplyFilter, &QPushButton::clicked, this, &analyzereport::onFilterClicked);
    connect(ui->buttonClearFilter, &QPushButton::clicked, this, [this]() {
        ui->comboBoxMonth->setCurrentIndex(QDate::currentDate().month() - 1);
    });

    ui->comboBoxChartType->addItems({"Category Pie Chart", "Income vs Expense Bar Chart"});

    QStringList monthList = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    ui->comboBoxMonth->addItems(monthList);
    ui->comboBoxMonth->setCurrentIndex(QDate::currentDate().month() - 1);
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
    int selectedMonth = ui->comboBoxMonth->currentIndex() + 1;
    int currentYear = QDate::currentDate().year();

    QDate fromDate(currentYear, selectedMonth, 1);
    QDate toDate(currentYear, selectedMonth, QDate(currentYear, selectedMonth, 1).daysInMonth());

    QString chartType = ui->comboBoxChartType->currentText();

    if (chartType == "Income vs Expense Bar Chart") {
        generateBarChart(fromDate, toDate);
    } else {
        generatePieChart(fromDate, toDate);
    }
}

void analyzereport::generateBarChart(const QDate &fromDate, const QDate &toDate)
{
    double totalIncome = 0.0, totalExpense = 0.0, goalAmount = 0.0;
    QSqlQuery query;

    query.prepare(R"(
        SELECT SUM(amount) FROM transactions
        WHERE type = 'Income' AND user_id = :userId
          AND date BETWEEN :from AND :to
    )");
    query.bindValue(":userId", currentUserId);
    query.bindValue(":from", fromDate.toString("yyyy-MM-dd"));
    query.bindValue(":to", toDate.toString("yyyy-MM-dd"));
    if (query.exec() && query.next())
        totalIncome = query.value(0).toDouble();

    query.prepare(R"(
        SELECT SUM(amount) FROM transactions
        WHERE type = 'Expense' AND user_id = :userId
          AND date BETWEEN :from AND :to
    )");
    query.bindValue(":userId", currentUserId);
    query.bindValue(":from", fromDate.toString("yyyy-MM-dd"));
    query.bindValue(":to", toDate.toString("yyyy-MM-dd"));
    if (query.exec() && query.next())
        totalExpense = query.value(0).toDouble();

    query.prepare(R"(
        SELECT SUM(amount) FROM monthly_goals
        WHERE user_id = :userId
          AND month = :month AND year = :year
    )");
    query.bindValue(":userId", currentUserId);
    query.bindValue(":month", fromDate.toString("MM"));
    query.bindValue(":year", fromDate.year());
    if (query.exec() && query.next())
        goalAmount = query.value(0).toDouble();

    QBarSet *incomeSet = new QBarSet("Income");
    QBarSet *expenseSet = new QBarSet("Expense");
    *incomeSet << totalIncome;
    *expenseSet << totalExpense;
    incomeSet->setColor(Qt::blue);
    expenseSet->setColor(Qt::red);

    QBarSeries *series = new QBarSeries();
    series->append(incomeSet);
    series->append(expenseSet);

    QStringList categories;
    categories << " ";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Income vs Expense - " + fromDate.toString("MMMM"));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);

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

void analyzereport::generatePieChart(const QDate &fromDate, const QDate &toDate)
{
    double totalIncome = 0.0, totalExpense = 0.0, goalAmount = 0.0;
    QSqlQuery query;

    query.prepare(R"(
        SELECT SUM(amount) FROM transactions
        WHERE type = 'Income' AND user_id = :userId
          AND date BETWEEN :from AND :to
    )");
    query.bindValue(":userId", currentUserId);
    query.bindValue(":from", fromDate.toString("yyyy-MM-dd"));
    query.bindValue(":to", toDate.toString("yyyy-MM-dd"));
    if (query.exec() && query.next())
        totalIncome = query.value(0).toDouble();

    query.prepare(R"(
        SELECT SUM(amount) FROM transactions
        WHERE type = 'Expense' AND user_id = :userId
          AND date BETWEEN :from AND :to
    )");
    query.bindValue(":userId", currentUserId);
    query.bindValue(":from", fromDate.toString("yyyy-MM-dd"));
    query.bindValue(":to", toDate.toString("yyyy-MM-dd"));
    if (query.exec() && query.next())
        totalExpense = query.value(0).toDouble();

    query.prepare(R"(
        SELECT SUM(amount) FROM monthly_goals
        WHERE user_id = :userId
          AND month = :month AND year = :year
    )");
    query.bindValue(":userId", currentUserId);
    query.bindValue(":month", fromDate.toString("MM"));
    query.bindValue(":year", fromDate.year());
    if (query.exec() && query.next())
        goalAmount = query.value(0).toDouble();

    ui->labelTotalIncome->setText("Total Income: " + QString::number(totalIncome, 'f', 2));
    ui->labelTotalExpenses->setText("Total Expenses: " + QString::number(totalExpense, 'f', 2));
    ui->labelTotalMonthlyGoal->setText("Total Monthly Goal: " + QString::number(goalAmount, 'f', 2));

    double netBalance = totalIncome - totalExpense;
    double remaining = goalAmount - totalExpense;

    ui->labelRemainingBudget->setText("Remaining Budget: " + QString::number(remaining, 'f', 2));
    ui->labelNetBalance->setText("Income - Expenses: " + QString::number(netBalance, 'f', 2));

    QPieSeries *series = new QPieSeries();
    QVector<QPair<QString, double>> categoryData;
    double totalCategoryExpense = 0.0;

    query.prepare(R"(
        SELECT category, SUM(amount) FROM transactions
        WHERE type = 'Expense' AND user_id = :userId
          AND date BETWEEN :from AND :to
        GROUP BY category
    )");
    query.bindValue(":userId", currentUserId);
    query.bindValue(":from", fromDate.toString("yyyy-MM-dd"));
    query.bindValue(":to", toDate.toString("yyyy-MM-dd"));
    if (!query.exec()) {
        qDebug() << "Chart query failed:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString category = query.value(0).toString();
        double amount = query.value(1).toDouble();
        categoryData.append({category, amount});
        totalCategoryExpense += amount;
    }

    if (categoryData.isEmpty()) {
        ui->labelHoverInfo->setText("No expense data to show.");
        ui->labelWarnings->clear();
        return;
    }

    for (const auto &entry : categoryData) {
        QPieSlice *slice = series->append(entry.first, entry.second);
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

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Expenses by Category - " + fromDate.toString("MMMM"));
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
