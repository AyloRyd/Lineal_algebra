#pragma once
#include "Header.h"

class Matrix {
private:

    friend class Vector;

    int rows_;
    int cols_;
    std::vector<std::vector<double>> data_;

    Matrix deleteRowAndColumn(int rowIndex, int columnIndex) const;

        if (rowIndex < Result.rows_) {
            Result.data_.erase(Result.data_.begin() + rowIndex);
            Result.rows_--;

            for (auto& row : Result.data_) {
                if (columnIndex < row.size()) {
                    row.erase(row.begin() + columnIndex);
                }
            }
            Result.cols_--;
        }
        else {
            std::cerr << "Index out of range!" << std::endl;
        }

        return Result;
    }

public:
    Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(rows, std::vector<double>(cols, 0)) {}

    Matrix(int rows, int cols, double value) : rows_(rows), cols_(cols), data_(rows, std::vector<double>(cols, value)) {}

    Matrix(std::initializer_list<std::initializer_list<double>> list);

    void print() const;

    void print_det() const;

    std::vector<double>& operator[](int row);

    Matrix operator *(double scalar);

    Matrix operator *(const Matrix& Other);

    Matrix operator +(const Matrix& Other); 

    Matrix operator -(const Matrix& Other);

    Matrix inverse_matrix();

    Matrix pow(int power);

    double determinant();

    double algebraic_addition(int row, int col);

    Matrix algebraic_additions();

    Matrix transpose();
};   