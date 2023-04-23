#include <iostream>
#include "Matrix/Matrix.h"
#include "LinearRegresion/LinearRegresion.h"

using namespace std;

int main()
{       
    LinearRegresion model(1);
   
    Matrix X {{147, 150, 153, 158, 163, 165, 168, 170, 173, 175, 178, 180, 183}};
    X = X.T();
    Matrix Y{{49, 50, 51, 54, 58, 59, 60, 62, 63, 64, 66, 67, 68}};
    Y = Y.T();

    model.train(13, X, Y);
    cout << model.predict(Matrix{{155}}) << endl;
    Matrix W = model.W();
    cout << (W.at(0, 0) + W.at(1, 0) * 155);
    return 0;
}