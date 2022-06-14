#include "dialogmatrix1.h"
#include "ui_dialogmatrix1.h"

DialogMatrix1::DialogMatrix1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMatrix1)
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

    ui->comboBoxColumns->addItem("1");
    ui->comboBoxColumns->addItem("2");
    ui->comboBoxColumns->addItem("3");
    ui->comboBoxColumns->addItem("4");
    ui->comboBoxColumns->addItem("5");
    ui->comboBoxColumns->addItem("6");
    ui->comboBoxColumns->addItem("7");
    ui->comboBoxColumns->addItem("8");
    ui->comboBoxColumns->addItem("9");
    ui->comboBoxColumns->addItem("10");

    connect(ui->getDataButton, SIGNAL(clicked()), this, SLOT(getDataFromTable()));
    connect(ui->checkSymmetryButton, SIGNAL(clicked()), this, SLOT(checkIfSymmetric_clicked()));
    connect(ui->detButton, SIGNAL(clicked()), this, SLOT(findDeterminant_clicked()));
    connect(ui->rankButton, SIGNAL(clicked()), this, SLOT(findRank_clicked()));
    connect(ui->transposeButton, SIGNAL(clicked()), this, SLOT(transpose_clicked()));
    connect(ui->fillButton, SIGNAL(clicked()), this, SLOT(fillWithEqual_clicked()));
    connect(ui->scalarMultButton, SIGNAL(clicked()), this, SLOT(scalarMultiplication_clicked()));

    connect(ui->comboBoxRows, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable()));
    connect(ui->comboBoxColumns, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable()));
}

DialogMatrix1::~DialogMatrix1()
{
    delete ui;
}

void DialogMatrix1::findDeterminant_clicked()
{
    if (m.getRows() != m.getColumns())
    {
        QMessageBox::warning(this, "Error", "Matrix must be square");
        return;
    }

    double det = m.findDeterminant();

    QString qstr_det = QString::number(det);

    QMessageBox::information(this, "Info", "Determinant of the matrix is " + qstr_det);
}

void DialogMatrix1::findRank_clicked()
{
    if (m.getRows() != m.getColumns())
    {
        QMessageBox::warning(this, "Error", "Matrix must be square");
        return;
    }

    int rank = m.findRank();

    QString qstr_rank = QString::number(rank);

    QMessageBox::information(this, "Info", "Rank of the matrix is " + qstr_rank);
}

void DialogMatrix1::transpose_clicked()
{
    Matrix transposed = m.transpose();

    ui->transposeTableWidget->setRowCount(transposed.getRows());
    ui->transposeTableWidget->setColumnCount(transposed.getColumns());
    ui->transposeTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->transposeTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < ui->transposeTableWidget->rowCount(); i++)
    {
        for (int j = 0; j < ui->transposeTableWidget->columnCount(); j++)
        {
            double element = transposed.getElement(i, j);

            QString value = QString::number(element);

            ui->transposeTableWidget->setItem(i, j, new QTableWidgetItem(value));
        }
    }
}

void DialogMatrix1::checkIfSymmetric_clicked()
{
    if (m.getRows() != m.getColumns())
    {
        QMessageBox::warning(this, "Error", "Matrix must be square");
        return;
    }

    if (m.checkIfSymmetrical())
    {
        QMessageBox::information(this, "Info", "Matrix is symmetrical");
        return;
    }
    else
    {
        QMessageBox::information(this, "Info", "Matrix is not symmetrical");
        return;
    }
}

void DialogMatrix1::fillWithEqual_clicked()
{
    QString value = ui->valueEdit->text();

    if (value == "")
    {
        QMessageBox::warning(this, "Error", "Empty input");
        return;
    }
    else if (value.toDouble() == 0 && value != "0")
    {
        QMessageBox::warning(this, "Error", "Incorrect value input");
        ui->valueEdit->clear();
        return;
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(value));
        }
    }

    double value_d = value.toDouble();

    m.fill(value_d);
}

void DialogMatrix1::scalarMultiplication_clicked()
{
    QString scalar = ui->scalarEdit->text();

    if (scalar == "")
    {
        QMessageBox::warning(this, "Error", "Empty input");
        return;
    }
    else if (scalar.toDouble() == 0 && scalar != "0")
    {
        QMessageBox::warning(this, "Error", "Incorrect scalar input");
        ui->scalarEdit->clear();
        return;
    }

    double scalar_d = scalar.toDouble();

    m *= scalar_d;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            double element = m.getElement(i, j);

            QString value = QString::number(element);

            ui->tableWidget->setItem(i, j, new QTableWidgetItem(value));
        }
    }
}

void DialogMatrix1::updateTable()
{
    int row_choice = ui->comboBoxRows->currentIndex();
    int column_choice = ui->comboBoxColumns->currentIndex();

    ui->tableWidget->setRowCount(row_choice + 1);
    ui->tableWidget->setColumnCount(column_choice + 1);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void DialogMatrix1::getDataFromTable()
{
    Matrix temp(ui->tableWidget->rowCount(), ui->tableWidget->columnCount());

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            bool flag = ui->tableWidget->item(i, j)->text().isEmpty();

            if (!flag) // the cell is not empty
            {
                QString cell_data = ui->tableWidget->item(i, j)->text();

                if (cell_data == "")
                {
                    QMessageBox::warning(this, "Error", "Empty input");
                    return;
                }
                else if (cell_data.toDouble() == 0 && cell_data != "0")
                {
                    QMessageBox::warning(this, "Error", "Incorrect data input");
                    return;
                }

                double data_d = cell_data.toDouble();

                temp.insertElement(i, j, data_d);
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
