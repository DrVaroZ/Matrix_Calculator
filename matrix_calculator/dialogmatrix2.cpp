#include "dialogmatrix2.h"
#include "ui_dialogmatrix2.h"

DialogMatrix2::DialogMatrix2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMatrix2)
{
    ui->setupUi(this);

    ui->comboBoxRows1->addItem("1");
    ui->comboBoxRows1->addItem("2");
    ui->comboBoxRows1->addItem("3");
    ui->comboBoxRows1->addItem("4");
    ui->comboBoxRows1->addItem("5");
    ui->comboBoxRows1->addItem("6");
    ui->comboBoxRows1->addItem("7");
    ui->comboBoxRows1->addItem("8");
    ui->comboBoxRows1->addItem("9");
    ui->comboBoxRows1->addItem("10");

    ui->comboBoxColumns1->addItem("1");
    ui->comboBoxColumns1->addItem("2");
    ui->comboBoxColumns1->addItem("3");
    ui->comboBoxColumns1->addItem("4");
    ui->comboBoxColumns1->addItem("5");
    ui->comboBoxColumns1->addItem("6");
    ui->comboBoxColumns1->addItem("7");
    ui->comboBoxColumns1->addItem("8");
    ui->comboBoxColumns1->addItem("9");
    ui->comboBoxColumns1->addItem("10");

    ui->comboBoxRows2->addItem("1");
    ui->comboBoxRows2->addItem("2");
    ui->comboBoxRows2->addItem("3");
    ui->comboBoxRows2->addItem("4");
    ui->comboBoxRows2->addItem("5");
    ui->comboBoxRows2->addItem("6");
    ui->comboBoxRows2->addItem("7");
    ui->comboBoxRows2->addItem("8");
    ui->comboBoxRows2->addItem("9");
    ui->comboBoxRows2->addItem("10");

    ui->comboBoxColumns2->addItem("1");
    ui->comboBoxColumns2->addItem("2");
    ui->comboBoxColumns2->addItem("3");
    ui->comboBoxColumns2->addItem("4");
    ui->comboBoxColumns2->addItem("5");
    ui->comboBoxColumns2->addItem("6");
    ui->comboBoxColumns2->addItem("7");
    ui->comboBoxColumns2->addItem("8");
    ui->comboBoxColumns2->addItem("9");
    ui->comboBoxColumns2->addItem("10");

    connect(ui->getData1Button, SIGNAL(clicked()), this, SLOT(getDataFromTable1()));
    connect(ui->getData2Button, SIGNAL(clicked()), this, SLOT(getDataFromTable2()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addMatrixes_clicked()));
    connect(ui->subtractButton, SIGNAL(clicked()), this, SLOT(subtractMatrixes_clicked()));
    connect(ui->multiplyButton, SIGNAL(clicked()), this, SLOT(multiplyMatrixes_clicked()));
    connect(ui->fill1Button, SIGNAL(clicked()), this, SLOT(fillWithEqual1_clicked()));
    connect(ui->fill2Button, SIGNAL(clicked()), this, SLOT(fillWithEqual2_clicked()));

    connect(ui->comboBoxRows1, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable1()));
    connect(ui->comboBoxColumns1, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable1()));
    connect(ui->comboBoxRows2, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable2()));
    connect(ui->comboBoxColumns2, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable2()));
}

DialogMatrix2::~DialogMatrix2()
{
    delete ui;
}

void DialogMatrix2::addMatrixes_clicked()
{
    if (!(a.getRows() == b.getRows() && a.getColumns() == b.getColumns()))
    {
        QMessageBox::warning(this, "Error", "Matrix dimensions must be the same");
        return;
    }

    Matrix c = a + b;

    ui->table3Widget->setRowCount(c.getRows());
    ui->table3Widget->setColumnCount(c.getColumns());
    ui->table3Widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table3Widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < ui->table3Widget->rowCount(); i++)
    {
        for (int j = 0; j < ui->table3Widget->columnCount(); j++)
        {
            double element = c.getElement(i, j);

            QString value = QString::number(element);

            ui->table3Widget->setItem(i, j, new QTableWidgetItem(value));
        }
    }
}

void DialogMatrix2::subtractMatrixes_clicked()
{
    if (!(a.getRows() == b.getRows() && a.getColumns() == b.getColumns()))
    {
        QMessageBox::warning(this, "Error", "Matrix dimensions must be the same");
        return;
    }

    Matrix c = a - b;

    ui->table3Widget->setRowCount(c.getRows());
    ui->table3Widget->setColumnCount(c.getColumns());
    ui->table3Widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table3Widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < ui->table3Widget->rowCount(); i++)
    {
        for (int j = 0; j < ui->table3Widget->columnCount(); j++)
        {
            double element = c.getElement(i, j);

            QString value = QString::number(element);

            ui->table3Widget->setItem(i, j, new QTableWidgetItem(value));
        }
    }
}

void DialogMatrix2::multiplyMatrixes_clicked()
{
    if (a.getColumns() != b.getRows())
    {
        QMessageBox::warning(this, "Error", "Number of the columns of the 1st matrix and number of the rows of the 2nd matrix must be the same");
        return;
    }

    Matrix c = a * b;

    ui->table3Widget->setRowCount(c.getRows());
    ui->table3Widget->setColumnCount(c.getColumns());
    ui->table3Widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table3Widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < ui->table3Widget->rowCount(); i++)
    {
        for (int j = 0; j < ui->table3Widget->columnCount(); j++)
        {
            double element = c.getElement(i, j);

            QString value = QString::number(element);

            ui->table3Widget->setItem(i, j, new QTableWidgetItem(value));
        }
    }
}

void DialogMatrix2::fillWithEqual1_clicked()
{
    QString value = ui->value1Edit->text();

    if (value == "")
    {
        QMessageBox::warning(this, "Error", "Empty input");
        return;
    }
    else if (value.toDouble() == 0 && value != "0")
    {
        QMessageBox::warning(this, "Error", "Incorrect value input");
        ui->value1Edit->clear();
        return;
    }

    for (int i = 0; i < ui->table1Widget->rowCount(); i++)
    {
        for (int j = 0; j < ui->table1Widget->columnCount(); j++)
        {
            ui->table1Widget->setItem(i, j, new QTableWidgetItem(value));
        }
    }

    double value_d = value.toDouble();

    a.fill(value_d);
}

void DialogMatrix2::fillWithEqual2_clicked()
{
    QString value = ui->value2Edit->text();

    if (value == "")
    {
        QMessageBox::warning(this, "Error", "Empty input");
        return;
    }
    else if (value.toDouble() == 0 && value != "0")
    {
        QMessageBox::warning(this, "Error", "Incorrect value input");
        ui->value2Edit->clear();
        return;
    }

    for (int i = 0; i < ui->table2Widget->rowCount(); i++)
    {
        for (int j = 0; j < ui->table2Widget->columnCount(); j++)
        {
            ui->table2Widget->setItem(i, j, new QTableWidgetItem(value));
        }
    }

    double value_d = value.toDouble();

    b.fill(value_d);
}

void DialogMatrix2::updateTable1()
{
    int row_choice = ui->comboBoxRows1->currentIndex();
    int column_choice = ui->comboBoxColumns1->currentIndex();

    ui->table1Widget->setRowCount(row_choice + 1);
    ui->table1Widget->setColumnCount(column_choice + 1);
    ui->table1Widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table1Widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void DialogMatrix2::updateTable2()
{
    int row_choice = ui->comboBoxRows2->currentIndex();
    int column_choice = ui->comboBoxColumns2->currentIndex();

    ui->table2Widget->setRowCount(row_choice + 1);
    ui->table2Widget->setColumnCount(column_choice + 1);
    ui->table2Widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table2Widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void DialogMatrix2::getDataFromTable1()
{
    Matrix temp(ui->table1Widget->rowCount(), ui->table1Widget->columnCount());

    for (int i = 0; i < ui->table1Widget->rowCount(); i++)
    {
        for (int j = 0; j < ui->table1Widget->columnCount(); j++)
        {
            bool flag = ui->table1Widget->item(i, j)->text().isEmpty();

            if (!flag) // the cell is not empty
            {
                QString cell_data = ui->table1Widget->item(i, j)->text();

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

    a = temp;
}

void DialogMatrix2::getDataFromTable2()
{
    Matrix temp(ui->table2Widget->rowCount(), ui->table2Widget->columnCount());

    for (int i = 0; i < ui->table2Widget->rowCount(); i++)
    {
        for (int j = 0; j < ui->table2Widget->columnCount(); j++)
        {
            bool flag = ui->table2Widget->item(i, j)->text().isEmpty();

            if (!flag) // the cell is not empty
            {
                QString cell_data = ui->table2Widget->item(i, j)->text();

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

    b = temp;
}
