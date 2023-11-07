#include "Header.h"

int main() {
    try
    {
        Vector a(2, 3, 4);
        std::cout << a.length();
        std::cout << "\n\n";

        Vector b = a * 3;
        b.print();
        std::cout << "\n\n";

        Vector c = a + b;
        c.print();
        std::cout << "\n\n";

        Vector d = c - b;
        if (d == a) { std::cout << "True"; }
        std::cout << "\n\n";

        std::cout << Vector::Scalar_product(a, b);
        std::cout << "\n\n";

        Vector v = Vector::Vector_product(a, d);
        v.print();
        std::cout << "\n\n";
        Vector p(4, 7, 1), k(2, 9, 5);
        Vector g = Vector::Vector_product(p, k);
        g.print();
        std::cout << "\n\n";

        std::cout << Vector::Mixed_product(a, p, k);
        std::cout << "\n\n";

        Vector l(3, 3, 3), m(4, 4, 4);
        if(Vector::isCollinear(l, m)) { std::cout << "True"; }
        std::cout << "\n\n";

        Vector i(1, 0, 0), j(0, 1, 0);
        if (Vector::isOrthogonal(i, j)) { std::cout << "True"; }
        std::cout << "\n\n";

        Vector q(1, 1, 1);
        if (!Vector::isComplanar(i, j, q)) { std::cout << "False"; } 
        std::cout << "\n\n";

        Vector x(0, 5, 0), y(3, 0, 0);
        std::cout << Vector::angle_between_vectors(x, y);
        std::cout << "\n\n";

        std::cout << Vector::angle_between_vectors(p, k);
        std::cout << "\n\n";

        for (double cosine : a.directional_cosines()) {
            std::cout << cosine << " ";
        }
        std::cout << "\n\n";

        std::cout << Vector::projection_of_vector_onto_vector(p, k); 
        std::cout << "\n\n";

        Vector r(5, -7, 3), t(3, -9, 1), o(4, -7, 8);
        std::cout << Vector::triangle_area(r, t);
        std::cout << "\n\n";

        std::cout << Vector::parallelogram_area(r, t);
        std::cout << "\n\n";

        std::cout << Vector::pyramid_volume(r, t, o);
        std::cout << "\n\n";

        std::cout << Vector::parallelepiped_volume(r, t, o);
        std::cout << "\n\n";



        Matrix A = {
        {-1, 2, 3},
        {4, 10, 6},
        {7, 8, 9},
        };
        A.print();
        std::cout << "\n\n";

        Matrix B = {
            {2, 5, 3},
            {6, 5, 2},
            {9, 3, 7}
        };
        B.print();
        std::cout << "\n\n";

        Matrix C = A + B;
        C.print();
        std::cout << "\n\n";

        C = C * (-2);
        C.print();
        std::cout << "\n\n";

        Matrix G = {
            {1, 2},
            {3, 4}
        };

        Matrix D = G.algebraic_additions();
        D.print();
        std::cout << "\n\n";

        std::cout << B.determinant(); 
        std::cout << "\n\n";

        Matrix F = {
             {2,-3,1},
             {1,4,2},
             {1,-4,0}
        };

        Matrix I = F.inverse_matrix();
        I.print();
        std::cout << "\n\n";

        Matrix O = {
            {1, 5, 8},
            {4, 6, 0},
            {0, 1, 4}
        };
        Matrix Pow = O.pow(3); 
        Pow.print(); 
        std::cout << "\n\n"; 

        Matrix K = { 
            {6},
            {-2},
            {7},
            {4}
        };

        Matrix T = {
            {1, 7, 9 ,0}
        };

        Matrix TK = K * T;
        TK.print(); 
    }
    catch (const std::exception& error)
    {
        std::cout << error.what();
    }
}