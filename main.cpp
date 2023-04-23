#include <iostream>
#include "Matrix/Matrix.h"
#include "Matrix/MatrixExceptions.h"

using namespace std;

int main()
{
    Matrix A{
        {2, 0},
        {0, 2},
    };
    Matrix B {
        {0, 1},
        {1, 0}
    };
    (A + B).inverse().show(10, 2);
    return 0;
}