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
    Matrix(int size) : rows_(size), cols_(size), data_(size, std::vector<int>(size, 0)) {}

    Matrix(std::initializer_list<std::initializer_list<int>> list) {
        rows_ = list.size();
        cols_ = list.size();
        data_.resize(rows_);

        int row_index = 0;
        for (auto& row : list) {
            if (rows_ != cols_ || row.size() != cols_) {
                throw std::invalid_argument("The program does not support non-square matrices yet!");
            }

            data_[row_index] = std::vector<int>(row.begin(), row.end());
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
        Matrix Result(rows_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Result.data_[i][j] = data_[i][j] * scalar;
            }
        }
        return Result;
    }

    Matrix operator *(int scalar) {
        Matrix Result(rows_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Result.data_[i][j] = data_[i][j] * scalar;
            }
        }
        return Result;
    }

    Matrix operator +(const Matrix& Other) {
        Matrix Result(rows_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Result.data_[i][j] = data_[i][j] + Other.data_[i][j];
            }
        }
        return Result;
    }

    Matrix operator -(const Matrix& Other) {
        Matrix Result(rows_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Result.data_[i][j] = data_[i][j] - Other.data_[i][j];
            }
        }
        return Result;
    }

    int determinant() {
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

    Matrix algebraic_additions() {
        Matrix Result(rows_);

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                Matrix smallerMatrix = deleteRowAndColumn(i, j);
                int det = smallerMatrix.determinant();
                Result[i][j] = det * std::pow(-1, i + j);
            }
        }

        return Result;
    }
};   