//
//  main.cpp
//  matrix_sum
//
//  Created by  Mister on 22.11.2020.
//

#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>

class Matrix {
private:
    int num_rows;
    int num_cols;
    std::vector<std::vector<int>> matrix;
public:
    Matrix() {
        num_rows = 0;
        num_cols = 0;
        matrix.assign(num_rows, std::vector<int>(num_cols));
    }
    Matrix(int rows, int cols) {
        CheckRange(rows, cols);
        num_rows = rows;
        num_cols = cols;
        matrix.assign(num_rows, std::vector<int>(num_cols));
    }
    void Reset(int rows, int cols) {
        CheckRange(rows, cols);
        num_rows = rows;
        num_cols = cols;
        matrix.assign(num_rows, std::vector<int>(num_cols));
    }
    int At(int row, int col) const {
        if (row > num_rows || col > num_cols) {
            throw std::out_of_range("Error in Row or Col");
        }
        return matrix.at(row).at(col);
    }
    int& At(int row, int col) {
        if (row > num_rows || col > num_cols) {
            throw std::out_of_range("Error in Row or Col");
        }
        return matrix.at(row).at(col);
    }
    int GetNumRows() const {
        return num_rows;
    }
    int GetNumColumns() const {
        return num_cols;
    }
    void CheckRange(const int& rows, const int& cols) {
        if (rows < 0 || cols < 0) {
            throw std::out_of_range("Row or Col less then 0");
        }
    }
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if ((lhs.GetNumRows() == 0 || lhs.GetNumColumns() == 0) && (rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0)) {
        Matrix matrix;
        return matrix;
    }
    if (lhs.GetNumRows() != rhs.GetNumRows()) {
        throw std::invalid_argument("Rows aren't equal");
    }
    if (lhs.GetNumColumns() != rhs.GetNumColumns()) {
        throw std::invalid_argument("Columns aren't equal");
    }
    Matrix sumOfTwoMatrix(lhs.GetNumRows(), lhs.GetNumColumns());
    for (int i = 0; i < lhs.GetNumRows(); ++i) {
        for (int j = 0; j < lhs.GetNumColumns(); ++j) {
            sumOfTwoMatrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }
    return sumOfTwoMatrix;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if ((lhs.GetNumRows() == 0 || lhs.GetNumColumns() == 0) && (rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0)) {  // Если в обеих матрицах одновременно есть хотя бы одно нулевое измерение
        return true;
    }
    if ((lhs.GetNumRows() != rhs.GetNumRows()) || (lhs.GetNumColumns() != rhs.GetNumColumns())) {  // Если размерности не сопадают, то сразу говорим, что не равны
        return false;
    } else {  // Размерности совпали, тогда проверяем поэлеметно
        for (int i = 0; i < lhs.GetNumRows(); ++i) {
            for (int j = 0; j < lhs.GetNumColumns(); ++j) {
                if (lhs.At(i, j) != rhs.At(i, j)) {  // Если элемент не совпал
                    return false;
                }
            }
        }
    }
    return true;
}

std::istream& operator>>(std::istream& stream, Matrix& matrix) {
    int rows, cols;
    stream >> rows >> cols;
    matrix.Reset(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            stream >> matrix.At(i, j);
        }
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix) {
    stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << "\n";
    for (int i = 0; i < matrix.GetNumRows(); ++i) {
        for (int j = 0; j < matrix.GetNumColumns(); ++j) {
            stream << matrix.At(i, j) << " ";
        }
        stream << "\n";
    }
    return stream;
}

int main() {
    Matrix one(2,0);
    Matrix two(0,3);
    std::cout << (one + two) << std::endl;
    return 0;
}
