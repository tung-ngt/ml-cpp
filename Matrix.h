#pragma once
#include <initializer_list>

using std::initializer_list;

class Matrix
{
private:
    size_t rows, cols;
    double **mA;
    double mDet;

    void setMatrix(double **a);
    void cleanUp();

    double calculateDet() const;

public:
    double det;

    Matrix();
    ~Matrix();
    Matrix(const Matrix &b);
    Matrix(size_t rows, size_t cols, double **a);
    Matrix(size_t rows, size_t cols, double initialValue = 0.0);
    Matrix(initializer_list<initializer_list<double>> initializerMatrix);

    Matrix T() const;

    Matrix C(size_t i, size_t j) const;
    Matrix M(size_t i, size_t j) const;

    double det() const;

    Matrix product(const Matrix &b) const;
    Matrix operator*(const Matrix &b) const;
    Matrix scale(double scaler) const;
    Matrix operator*(double scaler) const;

    size_t getRows() const;
    size_t getCols() const;

    double at(size_t i, size_t j) const;

    // Matrix inverse();

    void show(size_t colWidth = 5, size_t precision = 1) const;
};

Matrix operator*(double scaler, const Matrix &matrix);