#include "LinearRegresion.h"

LinearRegresion::LinearRegresion(size_t noFeatures) : mNoFeatures(noFeatures)
{
}

bool LinearRegresion::train(size_t noDatasets, const Matrix &X_in, const Matrix &Y_in)
{
    mNoDatasets = noDatasets;
    if (X_in.cols() != mNoFeatures)
        return false;

    if (X_in.rows() != mNoDatasets || Y_in.rows() != mNoDatasets)
        return false;

    Matrix X = X_in;
    Matrix Y = Y_in;
    Matrix XBar = Matrix(noDatasets, 1, 1).hStack(X);
    Matrix XBarT = XBar.T();
    Matrix A = XBarT * XBar;
    Matrix B = XBarT * Y;
    mW = A.inverse() * B;
    return true;
}

Matrix LinearRegresion::W()
{
    return mW;
}

double LinearRegresion::predict(const Matrix &x)
{
    return double(Matrix(1, 1, 1).hStack(x) * mW);
}