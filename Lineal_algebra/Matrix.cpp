#include "Matrix.h"

Matrix Matrix::deleteRowAndColumn(int rowIndex, int columnIndex) const 
{
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

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list)
{
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

void Matrix::print() const
{
    std::vector<int> max_lengths(cols_, 0);

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            int valueLength = countDigitsInDouble(data_[i][j]);
            if (valueLength > max_lengths[j]) {
                max_lengths[j] = valueLength;
            }
        }
    }

    for (int i = 0; i < rows_; i++) {
        std::cout << "(";
        for (int j = 0; j < cols_; j++) {
            int valueLength = countDigitsInDouble(data_[i][j]);
            for (int space = 0; space < max_lengths[j] - valueLength; space++) {
                std::cout << " ";
            }
            j == cols_ - 1 ? std::cout << data_[i][j] : std::cout << data_[i][j] << "  ";
        }
        i == rows_ - 1 ? std::cout << ")" : std::cout << ")\n";
    }
}

std::vector<double>& Matrix::operator[](int row)
{
    if (row >= 0 && row <= rows_) {
        return data_[row];
    }
    else {
        throw std::out_of_range("Index out of range!");
    }
}

Matrix Matrix::operator *(double scalar)
{
    Matrix Result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            Result.data_[i][j] = data_[i][j] * scalar;
        }
    }
    return Result;
}

Matrix Matrix::operator *(const Matrix& Other)
{
    if (cols_ != Other.rows_) {
        throw std::invalid_argument("Error! The number of columns of the first matrix is not equal to the number of rows of the second matrix!");
    }
    Matrix Result(rows_, Other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < Other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                Result.data_[i][j] += data_[i][k] * Other.data_[k][j];
            }
        }
    }
    return Result;
}

Matrix Matrix::operator +(const Matrix& Other) 
{
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

Matrix Matrix::operator -(const Matrix& Other)
{
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

Matrix Matrix::inverse_matrix()
{
    Matrix Result(rows_, cols_);
    return this->algebraic_additions().transpose() * (1.0 / this->determinant());
}

Matrix Matrix::pow(int power)
{
    Matrix Result = *this;
    if (power < 0) {
        throw std::invalid_argument("Exponent should be a non-negative integer");
    }

    if (power == 0) {
        if (rows_ != cols_) {
            throw std::invalid_argument("Matrix must be square for exponentiation to 0");
        }
        Matrix Result_0(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            Result_0.data_[i][i] = 1;
        }
        return Result_0;
    }

    if (power == 1) {
        return *this;
    }

    for (int i = 0; i < power - 1; i++) {
        Result = Result * *this;
    }
    return Result;
}

double Matrix::determinant()
{
    if (rows_ != cols_) {
        throw std::invalid_argument("Error! The number of rows is not equal to the number of columns!");
    }

    if (cols_ == 1 && rows_ == 1) {
        return data_[0][0];
    }

    if (cols_ == 2 && rows_ == 2) {
        return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
    }

    double determinant = 0;
    for (int j = 0; j < cols_; j++) {
        Matrix smallerMatrix = deleteRowAndColumn(0, j);
        double minorDet = smallerMatrix.determinant();
        determinant += data_[0][j] * std::pow(-1, j) * minorDet;
    }
    return determinant;
}

double Matrix::algebraic_addition(int row, int col)
{
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Error! Index out of range!");
    }

    Matrix smallerMatrix = deleteRowAndColumn(row, col);
    double det = smallerMatrix.determinant();

    return det * std::pow(-1, row + col);
}

Matrix Matrix::algebraic_additions()
{
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

Matrix Matrix::transpose()
{
    Matrix Result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            Result.data_[i][j] = data_[j][i];
        }
    }
    return Result;
}
