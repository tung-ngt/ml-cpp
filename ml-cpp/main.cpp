#include <iostream>
#include "Matrix/Matrix.h"
#include "LinearRegression/LinearRegression.h"

using namespace std;

int main()
{
    LinearRegression model(1);

    Matrix X{{147, 150, 153, 158, 163, 165, 168, 170, 173, 175, 178, 180, 183}};
    X = X.T();
    Matrix Y{{49, 50, 51, 54, 58, 59, 60, 62, 63, 64, 66, 67, 68}};
    Y = Y.T();

    
    model.initDatasets(13, X, Y);
    model.train();

    Matrix initialW{
        {-20},
        {0.5}
    };
    model.gradientDecent(0.00007, 10000, initialW).show(10, 4);
    model.W().show();
    return 0;
}