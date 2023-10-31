#pragma once
#include "Header.h"

class Matrix {
private:

    friend class Vector;

    int rows_;
    int cols_;
    std::vector<std::vector<int>> data_;

    Matrix deleteRowAndColumn(int rowIndex, int columnIndex) const {
        Matrix Result = *this;

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
    Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(rows, std::vector<int>(cols, 0)) {}

    Matrix(std::initializer_list<std::initializer_list<int>> list) {
        rows_ = list.size();
        cols_ = 0; 
        int row_index = 0;

        for (const auto& row : list) {
            if (cols_ == 0) {
                cols_ = row.size(); 
            }
            else if (row.size() != cols_) {
                throw std::invalid_argument("Invalid matrix definition! Rows have different column counts.");
            }

            data_.push_back(row);
            row_index++;
        }
    }

    void print() const {
        std::vector<int> max_lengths(cols_, 0);

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                int valueLength = std::to_string(data_[i][j]).size();
                if (valueLength > max_lengths[j]) {
                    max_lengths[j] = valueLength;
                }
            }
        }

        for (int i = 0; i < rows_; i++) {
            std::cout << "(";
            for (int j = 0; j < cols_; j++) {
                std::string string_value = std::to_string(data_[i][j]);
                for (int space = 0; space < max_lengths[j] - string_value.size(); space++) {
                    std::cout << " ";
                }
                j == cols_ - 1 ? std::cout << string_value : std::cout << string_value << " ";
            }
            i == rows_ - 1 ? std::cout << ")" : std::cout << ")\n";
        }
    }

    void print_det() const {
        std::vector<int> max_lengths(cols_, 0);

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                int valueLength = std::to_string(data_[i][j]).size();
                if (valueLength > max_lengths[j]) {
                    max_lengths[j] = valueLength;
                }
            }
        }

        for (int i = 0; i < rows_; i++) {
            std::cout << "|";
            for (int j = 0; j < cols_; j++) {
                std::string string_value = std::to_string(data_[i][j]);
                for (int space = 0; space < max_lengths[j] - string_value.size(); space++) {
                    std::cout << " ";
                }
                j == cols_ - 1 ? std::cout << string_value : std::cout << string_value << " ";
            }
            i == rows_ - 1 ? std::cout << "|" : std::cout << "|\n";
        }
    }

    std::vector<int>& operator[](int row) {
        if (row >= 0 && row <= rows_) {
            return data_[row];
        }
        else {
            throw std::out_of_range("Index out of range!");
        }
    }

    Matrix multiplyByScalar(int scalar) {
        Matrix Result(rows_, cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Result.data_[i][j] = data_[i][j] * scalar;
            }
        }
        return Result;
    }

    Matrix operator *(int scalar) {
        Matrix Result(rows_, cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Result.data_[i][j] = data_[i][j] * scalar;
            }
        }
        return Result;
    }

    Matrix operator +(const Matrix& Other) {
        if (rows_ != Other.rows_ || cols_ != Other.cols_) {
            throw std::invalid_argument("Error! Matrix sizes are not equal!");
        }
        Matrix Result(rows_, cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Result.data_[i][j] = data_[i][j] + Other.data_[i][j];
            }
        }
        return Result;
    }

    Matrix operator -(const Matrix& Other) {
        if (rows_ != Other.rows_ || cols_ != Other.cols_) {
            throw std::invalid_argument("Error! Matrix sizes are not equal!");
        }
        Matrix Result(rows_, cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Result.data_[i][j] = data_[i][j] - Other.data_[i][j];
            }
        }
        return Result;
    }

    int determinant() {
        if (rows_ != cols_) {
            throw std::invalid_argument("Error! The number of rows is not equal to the number of columns!");
        }

        if (cols_ == 1 && rows_ == 1) {
            return data_[0][0];
        }

        if (cols_ == 2 && rows_ == 2) {
            return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
        }

        int determinant = 0;
        for (int j = 0; j < cols_; j++) {
            Matrix smallerMatrix = deleteRowAndColumn(0, j);
            int minorDet = smallerMatrix.determinant();
            determinant += data_[0][j] * std::pow(-1, j) * minorDet;
        }
        return determinant;
    }

    int algebraic_addition(int row, int col) {
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            throw std::out_of_range("Error! Index out of range!");
        }

        Matrix smallerMatrix = deleteRowAndColumn(row, col);
        int det = smallerMatrix.determinant();

        return det * std::pow(-1, row + col);
    }

    Matrix algebraic_additions() {
        if (rows_ != cols_) {
            throw std::invalid_argument("Error! The number of rows is not equal to the number of columns!");
        }

        Matrix Result(rows_, cols_);

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Result[i][j] = this->algebraic_addition(i, j);
            }
        }

        return Result;
    }
};   