#pragma once
#include "Header.h"

class Vector {
private:

    double x;
    double y;
    double z;

public:
    Vector(double x_coordinate, double y_coordinate, double z_coordinate);

    void print() const;

    double length() const;

    bool operator ==(const Vector& Other);

    Vector operator*(double scalar) const;

    Vector operator+(const Vector& Other) const;

    Vector operator-(const Vector& Other) const;

    static double Scalar_product(const Vector& Vector_1, const Vector& Vector_2);

    static Vector Vector_product(const Vector& Vector_1, const Vector& Vector_2);

    static double Mixed_product(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3);

    static bool isCollinear(const Vector& Vector_1, const Vector& Vector_2);

    static bool isPerpendicular(const Vector& Vector_1, const Vector& Vector_2);

    static bool isComplanar(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3);

    static double cosine(const Vector& Vector_1, const Vector& Vector_2);

    static double sinus(const Vector& Vector_1, const Vector& Vector_2);
};