#pragma once
#include "Header.h"

class Vector {
private:

    int x;
    int y;
    int z;

public:
    Vector(int x_coordinate, int y_coordinate, int z_coordinate) {
        x = x_coordinate;
        y = y_coordinate;
        z = z_coordinate;
    }

    void print() const {
        std::cout << "(" << x << "," << y << "," << z << ")";
    }

    int length() const {
        return sqrt(x * x + y * y + z * z);
    }

    bool operator ==(const Vector& Other) {
        return x == Other.x && y == Other.y && z == Other.z;
    }

    Vector multiplyByScalar(int scalar) {
        Vector Result_vector(x * scalar, y * scalar, z * scalar);
        return Result_vector;
    }

    Vector operator*(int scalar) const {
        Vector Result_vector(x * scalar, y * scalar, z * scalar);
        return Result_vector;
    }

    Vector operator+(const Vector& Other) const {
        int result_x = x + Other.x;
        int result_y = y + Other.y;
        int result_z = z + Other.z;
        return Vector(result_x, result_y, result_z);
    }

    Vector operator-(const Vector& Other) const {
        int result_x = x - Other.x;
        int result_y = y - Other.y;
        int result_z = z - Other.z;
        return Vector(result_x, result_y, result_z);
    }

    static int Scalar_product(const Vector& Vector_1, const Vector& Vector_2) {
        return Vector_1.x * Vector_2.x + Vector_1.y * Vector_2.y + Vector_1.z * Vector_2.z;
    }

    static Vector Vector_product(const Vector& Vector_1, const Vector& Vector_2);

    static int Mixed_product(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3);

    static bool isCollinear(const Vector& Vector_1, const Vector& Vector_2) {
        if (Vector_1.x / Vector_2.x == Vector_1.y / Vector_2.y &&
            Vector_1.y / Vector_2.y == Vector_1.z / Vector_2.z) {
            return true;
        }
        return false;
    }

    static bool isPerpendicular(const Vector& Vector_1, const Vector& Vector_2) {
        if (Vector::Scalar_product(Vector_1, Vector_2) == 0) {
            return true;
        }
        return false;
    }

    static bool isComplanar(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3) {
        if (Vector::Mixed_product(Vector_1, Vector_2, Vector_3) == 0) {
            return true;
        }
        return false;
    }

    static double cosine(const Vector& Vector_1, const Vector& Vector_2) {
        return Scalar_product(Vector_1, Vector_2) / (Vector_1.length() * Vector_2.length());
    }

    static double sinus(const Vector& Vector_1, const Vector& Vector_2) {
        return sqrt(1 - std::pow(Vector::cosine(Vector_1, Vector_2), 2));
    }
};