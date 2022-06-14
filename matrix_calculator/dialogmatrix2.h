#ifndef DIALOGMATRIX2_H
#define DIALOGMATRIX2_H

#include "matrix.h"
#include <QDialog>
#include <QTableWidget>
#include <QMessageBox>

namespace Ui {
class DialogMatrix2;
}

class DialogMatrix2 : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMatrix2(QWidget *parent = nullptr);
    ~DialogMatrix2();

private slots:
    void updateTable1();

    void getDataFromTable1();

    void updateTable2();

    void getDataFromTable2();

    void addMatrixes_clicked();

    void subtractMatrixes_clicked();

    void multiplyMatrixes_clicked();

    void fillWithEqual1_clicked();

    void fillWithEqual2_clicked();

private:
    Ui::DialogMatrix2 *ui;
    Matrix a;
    Matrix b;
};

#endif // DIALOGMATRIX2_H
