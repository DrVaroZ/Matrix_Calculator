#include "dialogsolversle.h"
#include "ui_dialogsolversle.h"

DialogSolverSLE::DialogSolverSLE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSolverSLE)
{
    ui->setupUi(this);

    ui->comboBoxRows->addItem("1");
    ui->comboBoxRows->addItem("2");
    ui->comboBoxRows->addItem("3");
    ui->comboBoxRows->addItem("4");
    ui->comboBoxRows->addItem("5");
    ui->comboBoxRows->addItem("6");
    ui->comboBoxRows->addItem("7");
    ui->comboBoxRows->addItem("8");
    ui->comboBoxRows->addItem("9");
    ui->comboBoxRows->addItem("10");

    connect(ui->getDataButton, SIGNAL(clicked()), this, SLOT(getDataFromTable()));
    connect(ui->solveButton, SIGNAL(clicked()), this, SLOT(solveSLE_clicked()));

    connect(ui->comboBoxRows, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable()));
}

DialogSolverSLE::~DialogSolverSLE()
{
    delete ui;
}

void DialogSolverSLE::solveSLE_clicked()
{
    ui->solutionTableWidget->setRowCount(ui->tableWidget->rowCount());
    ui->solutionTableWidget->setColumnCount(2);
    ui->solutionTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->solutionTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Performing Matrix transformation
    int flag = m.performOperation();

    if (flag == 1)
        flag = m.checkConsistency(flag);

    std::vector<std::vector<double>> a(m.getMatrix());
    int n = m.getRows();

    if (flag == 2)
    {
        QMessageBox::information(this, "Info", "Infinite solutions exist");
        ui->solutionTableWidget->clear();
        return;
    }
    else if (flag == 3)
    {
        QMessageBox::information(this, "Info", "There are no solutions");
        ui->solutionTableWidget->clear();
        return;
    }
    // Printing the solution by dividing constants by
    // their respective diagonal elements
    else
    {
        for (int i = 0; i < n; i++)
        {
            double solution = a[i][n] / a[i][i];
            int var_pos = i;

            QString qstr_solution = QString::number(solution);
            QString var = "x" + QString::number(++var_pos);

            ui->solutionTableWidget->setItem(i, 0, new QTableWidgetItem(var));
            ui->solutionTableWidget->setItem(i, 1, new QTableWidgetItem(qstr_solution));
        }
    }
}

void DialogSolverSLE::getDataFromTable()
{
    Matrix temp(ui->tableWidget->rowCount(), ui->tableWidget->rowCount() + 1);

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        int element_pos = 0;
        for (int j = 0; j < ui->tableWidget->columnCount(); j+=3)
        {
            bool flag = ui->tableWidget->item(i, j)->text().isEmpty();

            if (!flag) // the cell is not empty
            {
                QString cell_data = ui->tableWidget->item(i, j)->text();

                if (cell_data.toDouble() == 0 && (cell_data != "0" && cell_data != "+" && cell_data != "=" && cell_data != "x1"
                                                  && cell_data != "x2" && cell_data != "x3" && cell_data != "x4" && cell_data != "x5"
                                                  && cell_data != "x6" && cell_data != "x7" && cell_data != "x8" && cell_data != "x9"
                                                  && cell_data != "x10"))
                {
                    QMessageBox::warning(this, "Error", "Incorrect data input");
                    return;
                }

                double data_d = cell_data.toDouble();

                temp.insertElement(i, element_pos, data_d);
                element_pos++;
            }
            else // the cell is empty
            {
                QMessageBox::warning(this, "Error", "Empty input");
                return;
            }
        }
    }

    m = temp;
}


void DialogSolverSLE::updateTable()
{
    int row_choice = ui->comboBoxRows->currentIndex();

    ui->tableWidget->setRowCount(row_choice + 1);
    ui->tableWidget->setColumnCount(row_choice + 4 + 2 * row_choice);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        int var_pos = 0;
        for (int j = 1; j < ui->tableWidget->columnCount(); j += 3)
        {
            QString var = "x" + QString::number(++var_pos);

            ui->tableWidget->setItem(i, j, new QTableWidgetItem(var));
        }
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for (int j = 2; j < ui->tableWidget->columnCount(); j += 3)
        {
            QString plus = "+";

            ui->tableWidget->setItem(i, j, new QTableWidgetItem(plus));
        }
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            if (j == ui->tableWidget->columnCount() - 2)
            {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem("="));
            }
        }
    }
}
