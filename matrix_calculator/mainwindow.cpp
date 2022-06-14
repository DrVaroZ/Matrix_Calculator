#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->matrix1DialogButton, SIGNAL(clicked()), this, SLOT(matrix1_operations_dialog_clicked()));
    connect(ui->matrix2DialogButton, SIGNAL(clicked()), this, SLOT(matrix2_operations_dialog_clicked()));
    connect(ui->sleButton, SIGNAL(clicked()), this, SLOT(sle_solver_dialog_clicked()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::matrix1_operations_dialog_clicked()
{
    DialogMatrix1 *form;
    form = new DialogMatrix1(this);
    form->setModal(false);
    form->show();
}

void MainWindow::matrix2_operations_dialog_clicked()
{
    DialogMatrix2 *form;
    form = new DialogMatrix2(this);
    form->setModal(false);
    form->show();
}

void MainWindow::sle_solver_dialog_clicked()
{
    DialogSolverSLE *form;
    form = new DialogSolverSLE(this);
    form->setModal(false);
    form->show();
}
