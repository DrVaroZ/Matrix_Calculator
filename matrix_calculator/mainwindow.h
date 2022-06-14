#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogmatrix1.h"
#include "dialogmatrix2.h"
#include "dialogsolversle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void matrix1_operations_dialog_clicked();

    void matrix2_operations_dialog_clicked();

    void sle_solver_dialog_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
