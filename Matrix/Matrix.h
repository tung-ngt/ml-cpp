#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include "MatrixExceptions.h"

using std::initializer_list;

class Matrix
{
private:
    size_t mRows, mCols;
    double **mA;
    double mDet;
    bool mHasCalculatedDet;

    void setMatrix(double **a);
    void cleanUp();

    Matrix mM(size_t i, size_t j) const;

    bool rowSwap(size_t rowI, size_t rowJ);
    bool rowScale(size_t rowI, double scaler);
    bool rowAdd(size_t rowI, size_t rowJ, double scaler = 1);

public:
    Matrix();
    ~Matrix();
    Matrix(const Matrix &b);
    Matrix(size_t rows, size_t cols, double initialValue = 0.0);
    Matrix(size_t rows, size_t cols, double **a);
    Matrix(initializer_list<initializer_list<double>> initializerMatrix) throw(InconsistentColumns);

    static Matrix diagonal(size_t size, initializer_list<double> values);
    static Matrix identity(size_t size, double scaledBy = 1);

    Matrix T() const;

    bool setDet();
    bool hasCalculatedDet() const;
    double calculateDet() const throw(NoDeterminant);
    double det() const throw(HaventCalculatedDeterminant, NoDeterminant);

    Matrix dot(const Matrix &b) const throw(IncompatibleShape);
    Matrix operator*(const Matrix &b) const throw(IncompatibleShape);
    Matrix scale(double scaler) const;
    Matrix operator*(double scaler) const;

    Matrix pow(size_t power) const throw(IncompatibleShape);
    Matrix operator^(size_t power) const throw(IncompatibleShape);

    Matrix add(const Matrix &b) const throw(IncompatibleShape);
    Matrix operator+(const Matrix &b) const throw(IncompatibleShape);

    Matrix add(double a) const;
    Matrix operator+(double a) const;

    bool equals(const Matrix &b) const;
    bool operator==(const Matrix &b) const;

    void operator=(const Matrix &b);

    size_t rows() const;
    size_t cols() const;

    double at(size_t i, size_t j) const;

    Matrix inverse() const;

    void show(size_t colWidth = 5, size_t precision = 1) const;
};

Matrix operator*(double scaler, const Matrix &matrix);
Matrix operator+(double a, const Matrix &matrix); 

#endif