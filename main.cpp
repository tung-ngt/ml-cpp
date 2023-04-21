#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix b
    {
        {1, 1},
        {0, 1},
    };
    
    (b*5).show();



    // double r1[] = {4, 1, -1};
    // double r2[] = {2, 7, 1};
    // double r3[] = {1, -3, 12};
    // double *temp[] = {r1, r2, r3};
    // matrix.setMatrix(temp);

    // Matrix b(3, 1);
    // double b1[] = {3};
    // double b2[] = {19};
    // double b3[] = {31};
    // double *tempb[] = {b1, b2, b3};
    // b.setMatrix(tempb);

    // Matrix inverted_matrix = matrix.inverse();

    // inverted_matrix.product(b).show();

    return 0;
}