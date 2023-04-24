#include "LinearRegression.h"
#include <cmath>

LinearRegression::LinearRegression(size_t noFeatures) : mNoFeatures(noFeatures)
{
}

bool LinearRegression::initDatasets(size_t noDatasets, const Matrix &X_in, const Matrix &Y_in)
{
    mNoDatasets = noDatasets;
    if (X_in.cols() != mNoFeatures)
        return false;

    if (X_in.rows() != mNoDatasets || Y_in.rows() != mNoDatasets)
        return false;

    mX = X_in;
    mY = Y_in;
}

bool LinearRegression::train()
{

    Matrix X = mX;
    Matrix Y = mY;
    Matrix XBar = Matrix(mNoDatasets, 1, 1).hStack(X);
    Matrix XBarT = XBar.T();
    Matrix A = XBarT * XBar;
    Matrix B = XBarT * Y;
    mW = A.inverse() * B;
    return true;
}

Matrix LinearRegression::gradientDecent(double learningRate, size_t maxIteration, const Matrix &initialW)
{

    Matrix X = mX;
    Matrix Y = mY;
    Matrix W = initialW;
    Matrix XBar = Matrix(mNoDatasets, 1, 1).hStack(X);
    Matrix XBarT = XBar.T();

    for (size_t i = 0; i < maxIteration; i++)
    {
        Matrix gradientAtW0 = (1.0/mNoDatasets)*(XBarT * ((XBar * W) + Y.scale(-1)));
        std::cout << i << std::endl;
        std::cout << "w" << std::endl;
        std::cout << "cost: " << (0.5 * std::pow((Y + (XBar*W).scale(-1)).norm(2), 2)) << std::endl;
        W.show(10, 4);
        std::cout << "gradient" << std::endl;
        ((-learningRate) * gradientAtW0).show(10, 4);
        std::cout << std::endl << std::endl;

        Matrix newW = W + ((-learningRate) * gradientAtW0);
        if (newW == W)
        {
            return newW;
        }
        W = newW;
    }
    return W;
}

Matrix LinearRegression::W()
{
    return mW;
}

double LinearRegression::predict(const Matrix &x)
{
    return double(Matrix(1, 1, 1).hStack(x) * mW);
}
