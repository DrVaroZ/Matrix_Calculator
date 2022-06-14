#ifndef DIALOGMATRIX1_H
#define DIALOGMATRIX1_H

#include "matrix.h"
#include <QDialog>
#include <QTableWidget>
#include <QMessageBox>

namespace Ui {
class DialogMatrix1;
}

class DialogMatrix1 : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMatrix1(QWidget *parent = nullptr);
    ~DialogMatrix1();

private slots:
    void updateTable();

    void getDataFromTable();

    void checkIfSymmetric_clicked();

    void findDeterminant_clicked();

    void findRank_clicked();

    void transpose_clicked();

    void fillWithEqual_clicked();

    void scalarMultiplication_clicked();

private:
    Ui::DialogMatrix1 *ui;
    Matrix m;
};

#endif // DIALOGMATRIX1_H
