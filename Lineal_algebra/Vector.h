#pragma once
#include "Header.h"

class Vector {
private:

    double x;
    double y;
    double z;

public:
    Vector();

    Vector(double x_coordinate, double y_coordinate, double z_coordinate);

    void print() const;

    double length() const;

    static double projection_of_vector_onto_vector(const Vector& Vector_1, const Vector& Vector_2);

    bool operator==(const Vector& Other);

    bool operator!=(const Vector& Other);

    Vector operator*(double scalar) const;

    Vector operator+(const Vector& Other) const;

    Vector operator-(const Vector& Other) const;

    static double Scalar_product(const Vector& Vector_1, const Vector& Vector_2);

    static Vector Vector_product(const Vector& Vector_1, const Vector& Vector_2);

    static double Mixed_product(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3);

    static double triangle_area(const Vector& Vector_1, const Vector& Vector_2);

    static double parallelogram_area(const Vector& Vector_1, const Vector& Vector_2);

    static double pyramid_volume(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3);

    static double parallelepiped_volume(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3);

    static bool isCollinear(const Vector& Vector_1, const Vector& Vector_2);

    static bool isOrthogonal(const Vector& Vector_1, const Vector& Vector_2);

    static bool isComplanar(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3);

    static double cosine(const Vector& Vector_1, const Vector& Vector_2);

    static double sinus(const Vector& Vector_1, const Vector& Vector_2);

    std::vector<double> directional_cosines();

    static double angle_between_vectors(const Vector& Vector_1, const Vector& Vector_2);
};