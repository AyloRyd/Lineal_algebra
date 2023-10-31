#include "Vector.h"

Vector Vector::Vector_product(const Vector& Vector_1, const Vector& Vector_2)
{
    int i = 1, j = 1, k = 1;
    Matrix Vector_matrix = {
        {i, j, k},
        {Vector_1.x, Vector_1.y, Vector_1.z},
        {Vector_2.x, Vector_2.y, Vector_2.z}
    };

    Matrix Algebraic_additions = Vector_matrix.algebraic_additions();

    int new_x = Algebraic_additions[0][0];
    int new_y = Algebraic_additions[0][1];
    int new_z = Algebraic_additions[0][2];

    return Vector(new_x, new_y, new_z);
}

int Vector::Mixed_product(const Vector& Vector_1, const Vector& Vector_2, const Vector& Vector_3)
{
    Matrix Vector_matrix = {
        {Vector_3.x, Vector_3.y, Vector_3.z},
        {Vector_1.x, Vector_1.y, Vector_1.z},
        {Vector_2.x, Vector_2.y, Vector_2.z}
    };

    return Vector_matrix.determinant();
}
