#ifndef LINEAR_REGRESION_H
#define LINEAR_REGRESION_H

#include "../Matrix/Matrix.h"

class LinearRegresion
{
private:
    size_t mNoFeatures;
    size_t mNoDatasets;
    Matrix mW;

public:
    LinearRegresion(size_t noFeatures);
    ~LinearRegresion() = default;

    bool train(size_t noDatasets, const Matrix &X, const Matrix &Y);
    Matrix W();
    double predict(const Matrix &X);
};

#endif