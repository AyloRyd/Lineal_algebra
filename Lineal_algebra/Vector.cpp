#include "Vector.h"

Vector::Vector(double x_coordinate, double y_coordinate, double z_coordinate)
{
    x = x_coordinate;
    y = y_coordinate;
    z = z_coordinate;
}

void Vector::print() const 
{
    std::cout << "(" << x << "," << y << "," << z << ")";
}

double Vector::length() const 
{
    return sqrt(x * x + y * y + z * z);
}

bool Vector::operator==(const Vector& Other) 
{
    return x == Other.x && y == Other.y && z == Other.z;
}

Vector Vector::operator*(double scalar) const
{
    Vector Result_vector(x * scalar, y * scalar, z * scalar);
    return Result_vector;
}

Vector Vector::operator+(const Vector& Other) const 
{
    double result_x = x + Other.x;
    double result_y = y + Other.y;
    double result_z = z + Other.z;
    return Vector(result_x, result_y, result_z);
}

Vector Vector::operator-(const Vector& Other) const 
{
    double result_x = x - Other.x;
    double result_y = y - Other.y;
    double result_z = z - Other.z;
    return Vector(result_x, result_y, result_z);
}

double Vector::Scalar_product(const Vector& Vector_1, const Vector& Vector_2)
{
    return Vector_1.x * Vector_2.x + Vector_1.y * Vector_2.y + Vector_1.z * Vector_2.z;
}

Vector Vector::Vector_product(const Vector& Vector_1, const Vector& Vector_2)
{
    double i = 1, j = 1, k = 1;
    Matrix Vector_matrix = {
        {i, j, k},
        {Vector_1.x, Vector_1.y, Vector_1.z},
        {Vector_2.x, Vector_2.y, Vector_2.z}
    };

    double new_x = Vector_matrix.algebraic_addition(0, 0);
    double new_y = Vector_matrix.algebraic_addition(0, 1);
    double new_z = Vector_matrix.algebraic_addition(0, 2);

    return Vector(new_x, new_y, new_z);
}

double Vector::Mixed_product(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3)
{
    Matrix Vector_matrix = {
        {Vector_3.x, Vector_3.y, Vector_3.z},
        {Vector_1.x, Vector_1.y, Vector_1.z},
        {Vector_2.x, Vector_2.y, Vector_2.z}
    };

    return Vector_matrix.determinant();
}

bool Vector::isCollinear(const Vector& Vector_1, const Vector& Vector_2) 
{
    if (Vector_product(Vector_1, Vector_2).length() == 0) {
        return true;
    }
    return false;
}

bool Vector::isPerpendicular(const Vector& Vector_1, const Vector& Vector_2) 
{
    if (Scalar_product(Vector_1, Vector_2) == 0) {
        return true;
    }
    return false;
}

bool Vector::isComplanar(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3) 
{
    if (Mixed_product(Vector_1, Vector_2, Vector_3) == 0) {
        return true;
    }
    return false;
}

double Vector::cosine(const Vector& Vector_1, const Vector& Vector_2) 
{
    return Scalar_product(Vector_1, Vector_2) / (Vector_1.length() * Vector_2.length());
}

double Vector::sinus(const Vector& Vector_1, const Vector& Vector_2) 
{
    return sqrt(1 - std::pow(Vector::cosine(Vector_1, Vector_2), 2));
}
