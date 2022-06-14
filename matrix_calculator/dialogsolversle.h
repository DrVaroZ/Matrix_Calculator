#ifndef DIALOGSOLVERSLE_H
#define DIALOGSOLVERSLE_H

#include "matrix.h"
#include <QDialog>
#include <QTableWidget>
#include <QMessageBox>

namespace Ui {
class DialogSolverSLE;
}

class DialogSolverSLE : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSolverSLE(QWidget *parent = nullptr);
    ~DialogSolverSLE();

private slots:
    void updateTable();

    void getDataFromTable();

    void solveSLE_clicked();

private:
    Ui::DialogSolverSLE *ui;
    Matrix m;
};

#endif // DIALOGSOLVERSLE_H
