#include "Vector.h"

//Vector::Vector(double x_coordinate = 0, double y_coordinate = 0, double z_coordinate = 0)
//{
//    x = x_coordinate;
//    y = y_coordinate;
//    z = z_coordinate;
//}

double Vector::get_x()
{
    return x;
}

double Vector::get_y()
{
    return y;
}

double Vector::get_z()
{
    return z;
}

void Vector::print() const 
{
    std::cout << "(" << x << ";" << y << ";" << z << ")";
}

double Vector::length() const 
{
    return sqrt(x * x + y * y + z * z);
}

double Vector::projection_of_vector_onto_vector(const Vector& Vector_1, const Vector& Vector_2)
{
    return abs(Scalar_product(Vector_1, Vector_2) / Vector_2.length());
}

bool Vector::operator==(const Vector& Other) 
{
    return this->x == Other.x && this->y == Other.y && this->z == Other.z;
}

bool Vector::operator!=(const Vector& Other)
{
    return this->x != Other.x || this->y != Other.y || this->z != Other.z;
}

Vector Vector::operator*(double scalar) const
{
    Vector Result_vector(x * scalar, y * scalar, z * scalar);
    return Result_vector;
}

Vector Vector::operator+(const Vector& Other) const 
{
    double result_x = this->x + Other.x;
    double result_y = this->y + Other.y;
    double result_z = this->z + Other.z;
    return Vector(result_x, result_y, result_z);
}

Vector Vector::operator-(const Vector& Other) const 
{
    double result_x = this->x - Other.x;
    double result_y = this->y - Other.y;
    double result_z = this->z - Other.z;
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
        {i,          j,          k         }, 
        {Vector_1.x, Vector_1.y, Vector_1.z},
        {Vector_2.x, Vector_2.y, Vector_2.z}
    };

    double new_x = Vector_matrix.algebraic_addition(0, 0); if (new_x == -0) { new_x = 0; }
    double new_y = Vector_matrix.algebraic_addition(0, 1); if (new_y == -0) { new_y = 0; } 
    double new_z = Vector_matrix.algebraic_addition(0, 2); if (new_z == -0) { new_z = 0; } 

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

double Vector::triangle_area(const Vector& Vector_1, const Vector& Vector_2)
{
    return Vector_product(Vector_1, Vector_2).length() * (1.0 / 2.0);
}

double Vector::parallelogram_area(const Vector& Vector_1, const Vector& Vector_2)
{
    return Vector_product(Vector_1, Vector_2).length();
}

double Vector::pyramid_volume(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3)
{
    return abs(Mixed_product(Vector_1, Vector_2, Vector_3)) * (1.0 / 6.0);
}

double Vector::parallelepiped_volume(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3)
{
    return abs(Mixed_product(Vector_1, Vector_2, Vector_3));
}

bool Vector::isCollinear(const Vector& Vector_1, const Vector& Vector_2) 
{
    return (Vector_product(Vector_1, Vector_2).length() == 0);
}

bool Vector::isOrthogonal(const Vector& Vector_1, const Vector& Vector_2)
{
    return (Scalar_product(Vector_1, Vector_2) == 0);
}

bool Vector::isComplanar(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3) 
{
    return (Mixed_product(Vector_1, Vector_2, Vector_3) == 0);
}

double Vector::cosine(const Vector& Vector_1, const Vector& Vector_2) 
{
    return Scalar_product(Vector_1, Vector_2) / (Vector_1.length() * Vector_2.length());
}

double Vector::sine(const Vector& Vector_1, const Vector& Vector_2)
{
    return sqrt(1 - std::pow(Vector::cosine(Vector_1, Vector_2), 2));
}

double Vector::tangent(const Vector& Vector_1, const Vector& Vector_2)
{
    return sine(Vector_1, Vector_2) / cosine(Vector_1, Vector_2);
}

double Vector::cotangent(const Vector& Vector_1, const Vector& Vector_2)
{
    return 1.0 / tangent(Vector_1, Vector_2); 
}

std::vector<double> Vector::directional_cosines()
{
    Vector x_vector(1, 0, 0), y_vector(0, 1, 0), z_vector(0, 0, 1);
    std::vector<double> cosines = { cosine(*this, x_vector), cosine(*this, y_vector), cosine(*this, z_vector) };
    return cosines; 
}

double Vector::angle_between_vectors(const Vector& Vector_1, const Vector& Vector_2)
{
    return acos(cosine(Vector_1, Vector_2)) * 180 / 3.14159265358979323846;
}
