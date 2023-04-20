#pragma once
#include <iostream>

using namespace std;

class Matrix
{
private:
    size_t m, n;
    double **a;

public:
    double det;

    Matrix();
    Matrix(size_t m, size_t n);
    Matrix(size_t m, size_t n, double initial_value);
    ~Matrix();

    void transpose();
    Matrix T();

    Matrix C(size_t i, size_t j);
    Matrix M(size_t i, size_t j);

    double calculate_det();

    void scaledBy(double scaler);
    Matrix scale(double scaler);

    Matrix product(Matrix b);

    size_t getM();
    size_t getN();

    Matrix inverse();
    Matrix invert();

    double getEntry(size_t i, size_t j);

    void setMatrix(double **a);
    void show();
};
