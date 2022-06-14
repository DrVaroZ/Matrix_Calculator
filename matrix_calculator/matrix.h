#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

class Matrix
{
private:
    std::vector<std::vector<double>> matrix;
    int rows;
    int columns;

    // function for swapping two rows of a matrix
    void swap(int row1, int row2, int col)
    {
        for (int i = 0; i < col; i++)
        {
            double temp = matrix[row1][i];
            matrix[row1][i] = matrix[row2][i];
            matrix[row2][i] = temp;
        }
    }

public:
    Matrix()
    {
        rows = 0;
        columns = 0;
    }

    Matrix(int r, int c)
    {
        rows = r;
        columns = c;
        matrix = std::vector<std::vector<double>>(r, std::vector<double>(c));
    }

    Matrix(std::vector<std::vector<double>> m)
    {
        if (!m.empty())
        {
            rows = m.size();
            columns = m[0].size();
            matrix = m;
        }
        throw std::length_error("size of the array must be greater than 0");
    }

    double findDeterminant()
    {
        std::vector<std::vector<double>> new_matrix(matrix);

        if (rows != columns)
            throw std::length_error("matrix must be square");

        double num1, num2, det = 1, total = 1; // Initialize result

        int index;
        int n = rows;

        // temporary array for storing row
        std::vector<double> temp(n + 1);

        // loop for traversing the diagonal elements
        for (int i = 0; i < n; i++)
        {
            index = i; // initialize the index

            // finding the index which has non zero value
            while (index < n && new_matrix[index][i] == 0)
            {
                index++;
            }
            if (index == n) // if there is non zero element
            {
                // the determinant of matrix as zero
                continue;
            }
            if (index != i)
            {
                // loop for swapping the diagonal element row and index row
                for (int j = 0; j < n; j++)
                {
                    std::swap(new_matrix[index][j], new_matrix[i][j]);
                }
                // determinant sign changes when we shift rows go through determinant properties
                det = det * pow(-1, index - i);
            }

            // storing the values of diagonal row elements
            for (int j = 0; j < n; j++)
            {
                temp[j] = new_matrix[i][j];
            }

            // traversing every row below the diagonal element
            for (int j = i + 1; j < n; j++)
            {
                num1 = temp[i]; // value of diagonal element
                num2 = new_matrix[j][i]; // value of next row element

                // traversing every column of row and multiplying to every row
                for (int k = 0; k < n; k++)
                {
                    // multiplying to make the diagonal element and next row element equal
                    new_matrix[j][k] = (num1 * new_matrix[j][k]) - (num2 * temp[k]);
                }
                total = total * num1; // det(k * A) = k * det(A);
            }
        }

        // multiplying the diagonal elements to get determinant
        for (int i = 0; i < n; i++)
        {
            det = det * new_matrix[i][i];
        }

        return (det / total); // det(k * A) / k = det(A);
    }

    int findRank()
    {
        std::vector<std::vector<double>> new_matrix(matrix);

        int rank = columns;

        for (int row = 0; row < rank; row++)
        {
            // Before we visit current row 'row', we make sure that mat[row][0],....mat[row][row-1] are 0.

            // Diagonal element is not zero
            if (new_matrix[row][row])
            {
                for (int col = 0; col < rows; col++)
                {
                    if (col != row)
                    {
                        // This makes all entries of current column as 0 except entry 'mat[row][row]'
                        double mult = (double)new_matrix[col][row] / new_matrix[row][row];
                        for (int i = 0; i < rank; i++)
                            new_matrix[col][i] -= mult * new_matrix[row][i];
                    }
                }
            }

                /* Diagonal element is already zero. Two cases arise:
                 1) If there is a row below it with non-zero
                    entry, then swap this row with that row
                    and process that row
                 2) If all elements in current column below
                    mat[r][row] are 0, then remove this column
                    by swapping it with last column and
                    reducing number of columns by 1.*/
            else
            {
                bool reduce = true;

                // Find the non-zero element in current column
                for (int i = row + 1; i < rows;  i++)
                {
                    // Swap the row with non-zero element with this row.
                    if (new_matrix[i][row])
                    {
                        swap(row, i, rank);
                        reduce = false;
                        break ;
                    }
                }

                // If we did not find any row with non-zero element in current column, then all values in this column are 0.
                if (reduce)
                {
                    // Reduce number of columns
                    rank--;

                    // Copy the last column here
                    for (int i = 0; i < rows; i ++)
                        new_matrix[i][row] = new_matrix[i][rank];
                }

                // Process this row again
                row--;
            }

        }
        return rank;
    }

    Matrix transpose()
    {
        Matrix new_matrix(columns, rows);

        for (int i = 0; i < new_matrix.getRows(); i++)
        {
            for (int j = 0; j < new_matrix.getColumns(); j++)
            {
                new_matrix.matrix[i][j] = matrix[j][i];
            }
        }

        return new_matrix;
    }

    bool checkIfSymmetrical()
    {
        Matrix new_matrix(rows, columns);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                new_matrix.matrix[i][j] = matrix[j][i];
            }
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (new_matrix.matrix[i][j] != matrix[i][j])
                    return false;
            }
        }

        return true;
    }

    // function to reduce matrix to reduced row echelon form.
    int performOperation()
    {
        int k = 0;
        int c;
        int flag = 0;

        // Performing elementary operations
        for (int i = 0; i < rows; i++)
        {
            if (matrix[i][i] == 0)
            {
                c = 1;
                while ((i + c) < rows && matrix[i + c][i] == 0)
                    c++;
                if ((i + c) == rows)
                {
                    flag = 1;
                    break;
                }
                for (int j = i, k = 0; k <= rows; k++)
                    std::swap(matrix[j][k], matrix[j+c][k]);
            }

            for (int j = 0; j < rows; j++)
            {
                // Excluding all i == j
                if (i != j)
                {
                    // Converting Matrix to reduced row
                    // echelon form(diagonal matrix)
                    double pro = matrix[j][i] / matrix[i][i];

                    for (k = 0; k <= rows; k++)
                        matrix[j][k] = matrix[j][k] - (matrix[i][k]) * pro;
                }
            }
        }
        return flag;
    }

    // To check whether infinite solutions exists or no solution exists
    int checkConsistency(int flag)
    {
        int i, j;
        double sum;

        // flag == 2 for infinite solution
        // flag == 3 for No solution
        flag = 3;
        for (i = 0; i < rows; i++)
        {
            sum = 0;
            for (j = 0; j < rows; j++)
                sum = sum + matrix[i][j];
            if (sum == matrix[i][j])
                flag = 2;
        }
        return flag;
    }

    Matrix& operator+=(const Matrix& m)
    {
        if (!(rows == m.getRows() && columns == m.getColumns()))
            throw std::length_error("Matrix dimensions must be the same");

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] += m.matrix[i][j];
            }
        }

        return *this;
    }

    Matrix& operator-=(const Matrix& m)
    {
        if (!(rows == m.getRows() && columns == m.getColumns()))
            throw std::length_error("Matrix dimensions must be the same");

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] -= m.matrix[i][j];
            }
        }

        return *this;
    }

    Matrix operator*=(const Matrix& m)
    {
        if (columns != m.getRows())
            throw std::length_error("Number of columns in the 1st matrix and number of rows in the 2nd matrix must be the same");

        Matrix new_matrix(rows, m.getColumns());

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < m.getColumns(); j++)
            {
                new_matrix.matrix[i][j] = 0;
                for (int k = 0; k < columns; k++)
                {
                    new_matrix.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
                }
            }
        }

        return new_matrix;
    }

    Matrix& operator*=(const double& scalar)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] *= scalar;
            }
        }

        return *this;
    }

    bool operator==(const Matrix& m)
    {
        if (!(rows == m.getRows() && columns == m.getColumns()))
            return false;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (matrix[i][j] != m.matrix[i][j])
                    return false;
            }
        }

        return true;
    }

    int getRows() const
    {
        return rows;
    }

    int getColumns() const
    {
        return columns;
    }

    std::vector<std::vector<double>> getMatrix() const
    {
        return matrix;
    }

    void fill(const double& value)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = value;
            }
        }
    }

    double getElement(int row, int column)
    {
        return matrix[row][column];
    }

    void insertElement(int row, int column, const double& value)
    {
        matrix[row][column] = value;
    }
};

inline Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    return Matrix(lhs) += rhs;
}

inline Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
    return Matrix(lhs) -= rhs;
}

inline Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
    return Matrix(lhs) *= rhs;
}

inline Matrix operator*(const double& scalar, const Matrix& m)
{
    return Matrix(m) *= scalar;
}

#endif // MATRIX_H
