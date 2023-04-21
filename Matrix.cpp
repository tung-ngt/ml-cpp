#include <iostream>
#include <iomanip>
#include <initializer_list>

#include "Matrix.h"

using std::cout;
using std::copy;
using std::initializer_list;
using std::setw;
using std::setprecision;
using std::endl;

Matrix::Matrix() : rows(0), cols(0), mA(NULL)
{}

Matrix::~Matrix()
{
    cout << "deintialize matrix: \n";
    show();
    cleanUp();
}

Matrix::Matrix(const Matrix &b)
{
    this->rows = b.rows;
    this->cols = b.cols;

    this->mA = new double*[this->rows];


    for (size_t i = 0; i < rows; i++)
    {
        this->mA[i] = new double[this->cols];
        for (size_t j = 0; i < cols; i++)
        { this->mA[i][j] = b.mA[i][j]; }
    }
}

Matrix::Matrix(size_t rows, size_t cols, double **a) : rows(rows), cols(cols)
{ setMatrix(a); }

Matrix::Matrix(size_t cols, size_t rows, double initialValue): 
    rows(rows), cols(cols)
{
    mA = new double*[rows];
    for (size_t i = 0; i < rows; i++)
    {
        mA[i] = new double[cols];
        for (size_t j = 0; j < cols; j++)
        { mA[i][j] = initialValue; }
    }
}


Matrix::Matrix(initializer_list<initializer_list<double>> initializerMatrix)
{
    rows = initializerMatrix.size();
    cols = initializerMatrix.begin()->size();

    auto pR = initializerMatrix.begin();
    for (size_t i = 0; i < rows; i++, pR++)
    {
        if (pR->size() != cols)
        {
            rows = 0;
            cols = 0;
            throw "Inconsistent cols";
        }
    }

    mA = new double*[rows];
    auto pI = initializerMatrix.begin();
    for (size_t i = 0; i < rows; i++, pI++)
    {
        mA[i] = new double[cols];
        copy(pI->begin(), pI->end(), mA[i]);
    }
}

void Matrix::cleanUp()
{
    if (mA == NULL)
    { return; }
    
    for (size_t i = 0; i < rows; i++)
    {
        delete[] mA[i];
    }
    delete[] mA;
}

void Matrix::setMatrix(double **a)
{
    cleanUp();
    this->mA = a;
}

Matrix Matrix::T() const
{
    double **b;
    b = new double*[cols];
    for (size_t i = 0; i < cols; i++)
    {
        b[i] = new double[rows];
        for (size_t j = 0; j < rows; j++)
        {
            b[i][j] = mA[j][i];
        }
    }
    Matrix t(rows, cols);
    t.setMatrix(b);
    return t;
}

void Matrix::show(size_t colWidth, size_t precision) const
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            cout << 
            setw(colWidth) << 
            std::fixed << 
            setprecision(precision) << 
            std::right << 
            mA[i][j];
        }
        cout << endl;
    }
}

Matrix Matrix::M(size_t i, size_t j) const
{
    Matrix minor(m - 1, n - 1);

    double **b;

    b = new double *[m - 1];

    int b_i = 0;
    int b_j = 0;
    for (size_t _i = 0; _i < m; _i++)
    {
        if (_i != i - 1)
        {
            b[b_i] = new double[n - 1];
            for (size_t _j = 0; _j < n; _j++)
            {
                if (_j != j - 1)
                {
                    b[b_i][b_j] = a[_i][_j];
                    b_j++;
                }
            }
            b_j = 0;
            b_i++;
        }
    }
    minor.setMatrix(b);
    return minor;
}

// double recursive_det(Matrix a)
// {
//     double d = 0;
//     a.show();
//     cout << endl;
//     if (a.getM() == 2)
//         d += a.getEntry(1, 1) * a.getEntry(2, 2) - a.getEntry(2, 1) * a.getEntry(1, 2);
//     else
//     {
//         for (size_t i = 0; i < a.getM(); i++)
//         {
//             Matrix m = a.M(1, i + 1);
//             d += recursive_det(m) * a.getEntry(1, i + 1) * pow(-1, 1 + i + 1);
//         }
//     }
//     cout << d << endl;
//     return d;
// }

// double Matrix::calculate_det()
// {
//     det = recursive_det(*this);
//     cout << det << endl;
//     return det;
// }

size_t Matrix::getCols() const
{
    return cols;
}
size_t Matrix::getRows() const
{
    return rows;
}

Matrix Matrix::scale(double scaler) const
{
    double **temp = new double*[rows];
    for (size_t i = 0; i < rows; i++)
    {
        temp[i] = new double[cols];
        for (size_t j = 0; j < cols; j++)
        { temp[i][j] = mA[i][j] * scaler; }
    }

    Matrix r(rows, cols);
    r.setMatrix(temp);
    return r;
}

Matrix Matrix::product(const Matrix &b) const
{
    Matrix productMatrix(this->rows, b.cols);
    double **temp = new double*[this->rows];

    for (size_t i = 0; i < this->rows; i++)
    {
        temp[i] = new double[b.cols];
        for (size_t j = 0; j < b.cols; j++)
        {
            double sumProduct = 0;
            for (size_t k = 0; k < this->cols; k++)
            {
                sumProduct += mA[i][k] * b.mA[k][j];
            }
            temp[i][j] = sumProduct;
        }
    }
    productMatrix.setMatrix(temp);
    return productMatrix;
}

Matrix Matrix::operator*(const Matrix &b) const
{ return product(b); }

Matrix Matrix::operator*(double scaler) const
{ return scale(scaler); }

double Matrix::at(size_t i, size_t j) const
{ return mA[i][j]; }

Matrix operator*(double scaler, const Matrix &matrix)
{ return matrix.scale(scaler); }

// Matrix Matrix::inverse()
// {
//     if (calculate_det() == 0)
//     {
//         cout << "Not invertible";
//     }

//     Matrix inverted_matrix(m, n, 0);

//     double **t = new double *[m];

//     for (size_t i = 0; i < m; i++)
//     {
//         t[i] = new double[n * 2];
//         for (size_t j = 0; j < n * 2; j++)
//         {
//             if (j < n)
//             {
//                 t[i][j] = a[i][j];
//                 continue;
//             }

//             if (j - n == i)
//             {
//                 t[i][j] = 1;
//                 continue;
//             }

//             t[i][j] = 0;
//         }
//     }

//     for (size_t leading = 0; leading < n; leading++)
//     {
//         double leading_div = t[leading][leading];
//         for (size_t j = 0; j < n * 2; j++)
//             t[leading][j] /= leading_div;

//         for (size_t i = leading + 1; i < m; i++)
//         {
//             double div = t[i][leading];
//             for (size_t j = 0; j < n * 2; j++)
//             {
//                 t[i][j] -= t[leading][j] * div;
//             }
//         }
//     }

//     for (size_t leading = n - 1; leading > 0; leading--)
//     {
//         for (int i = leading - 1; i >= 0; i--)
//         {
//             double div = t[i][leading];
//             for (size_t j = leading; j < n * 2; j++)
//             {
//                 t[i][j] -= t[leading][j] * div;
//             }
//         }
//     }

//     double **f = new double *[m];

//     for (size_t i = 0; i < m; i++)
//     {
//         f[i] = new double[n];
//         for (size_t j = 0; j < n; j++)
//         {
//             f[i][j] = t[i][j + n];
//         }
//     }
//     for (size_t i = 0; i < m; i++)
//     {
//         delete [] t[i];
//     }
//     delete [] t;

//     inverted_matrix.setMatrix(f);
//     return inverted_matrix;
// }
