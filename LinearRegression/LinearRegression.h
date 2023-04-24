#ifndef LINEAR_REGRESION_H
#define LINEAR_REGRESION_H

#include "../Matrix/Matrix.h"

class LinearRegression
{
private:
    size_t mNoFeatures;
    size_t mNoDatasets;
    Matrix mX;
    Matrix mY;
    Matrix mW;

public:
    LinearRegression(size_t noFeatures);
    ~LinearRegression() = default;

    bool initDatasets(size_t noDatasets, const Matrix &X_in, const Matrix &Y_in);
    bool train();
    Matrix gradientDecent(double learningRate, size_t maxIteration, const Matrix &initialW);
    Matrix W();

    double predict(const Matrix &X);
};

#endif