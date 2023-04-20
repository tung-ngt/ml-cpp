#include <iostream>
#include "Matrix.h"
#include <math.h>

using namespace std;

Matrix::Matrix() : m(3), n(3)
{
    a = new double *[m];
    for (size_t i = 0; i < m; i++)
    {
        a[i] = new double[n];
        for (size_t j = 0; j < n; j++)
        {
            a[i][j] = 0;
        }
    }
}
Matrix::Matrix(size_t m, size_t n) : m(m), n(n)
{
    a = new double *[m];
    for (size_t i = 0; i < m; i++)
    {
        a[i] = new double[n];
        for (size_t j = 0; j < n; j++)
        {
            a[i][j] = 0;
        }
    }
}
Matrix::Matrix(size_t m, size_t n, double initial_value) : m(m), n(n)
{
    a = new double *[m];
    for (size_t i = 0; i < m; i++)
    {
        a[i] = new double[n];
        for (size_t j = 0; j < n; j++)
        {
            a[i][j] = initial_value;
        }
    }
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < m; i++)
    {
        delete[] a[i];
    }
    delete[] a;
}

void Matrix::transpose()
{
    double **b;
    b = new double *[n];
    for (size_t i = 0; i < n; i++)
    {
        b[i] = new double[m];
        for (size_t j = 0; j < m; j++)
        {
            b[i][j] = a[j][i];
        }
    }

    for (size_t i = 0; i < m; i++)
    {
        delete[] a[i];
    }
    delete[] a;
    size_t temp = m;
    m = n;
    n = temp;
    a = b;
}
void Matrix::setMatrix(double **a)
{
    this->a = a;
}
Matrix Matrix::T()
{
    double **b;
    b = new double *[n];
    for (size_t i = 0; i < n; i++)
    {
        b[i] = new double[m];
        for (size_t j = 0; j < m; j++)
        {
            b[i][j] = a[j][i];
        }
    }

    Matrix t(n, m);
    t.setMatrix(b);
    return t;
}
void Matrix::show()
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout.width(12);
            cout << right << a[i][j];
        }
        cout << endl;
    }
}

Matrix Matrix::M(size_t i, size_t j)
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

double recursive_det(Matrix a)
{
    double d = 0;
    a.show();
    cout << endl;
    if (a.getM() == 2)
        d += a.getEntry(1, 1) * a.getEntry(2, 2) - a.getEntry(2, 1) * a.getEntry(1, 2);
    else
    {
        for (size_t i = 0; i < a.getM(); i++)
        {
            Matrix m = a.M(1, i + 1);
            d += recursive_det(m) * a.getEntry(1, i + 1) * pow(-1, 1 + i + 1);
        }
    }
    cout << d << endl;
    return d;
}

double Matrix::calculate_det()
{
    det = recursive_det(*this);
    cout << det << endl;
    return det;
}

size_t Matrix::getM()
{
    return m;
}
size_t Matrix::getN()
{
    return n;
}

void Matrix::scaledBy(double scaler)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            a[i][j] *= scaler;
        }
    }
}

Matrix Matrix::scale(double scaler)
{
    Matrix r(m, n);
    double **b;
    b = new double *[m];
    for (size_t i = 0; i < m; i++)
    {
        b[i] = new double[n];
        for (size_t j = 0; j < n; j++)
        {
            b[i][j] = a[j][i] * scaler;
        }
    }
    r.setMatrix(b);
    return r;
}

Matrix Matrix::product(Matrix b)
{
    Matrix product_matrix(m, b.n);
    double **temp = new double *[m];
    for (size_t i = 0; i < m; i++)
    {
        temp[i] = new double[b.n];
        for (size_t j = 0; j < b.n; j++)
        {
            double sum_product = 0;
            for (size_t k = 0; k < n; k++)
            {
                sum_product += a[i][k] * b.a[k][j];
            }
            temp[i][j] = sum_product;
        }
    }
    product_matrix.setMatrix(temp);
    return product_matrix;
}

double Matrix::getEntry(size_t i, size_t j)
{
    return a[i - 1][j - 1];
}

Matrix Matrix::inverse()
{
    if (calculate_det() == 0)
    {
        cout << "Not invertible";
    }

    Matrix inverted_matrix(m, n, 0);

    double **t = new double *[m];

    for (size_t i = 0; i < m; i++)
    {
        t[i] = new double[n * 2];
        for (size_t j = 0; j < n * 2; j++)
        {
            if (j < n)
            {
                t[i][j] = a[i][j];
                continue;
            }

            if (j - n == i)
            {
                t[i][j] = 1;
                continue;
            }

            t[i][j] = 0;
        }
    }

    for (size_t leading = 0; leading < n; leading++)
    {
        double leading_div = t[leading][leading];
        for (size_t j = 0; j < n * 2; j++)
            t[leading][j] /= leading_div;

        for (size_t i = leading + 1; i < m; i++)
        {
            double div = t[i][leading];
            for (size_t j = 0; j < n * 2; j++)
            {
                t[i][j] -= t[leading][j] * div;
            }
        }
    }

    for (size_t leading = n - 1; leading > 0; leading--)
    {
        for (int i = leading - 1; i >= 0; i--)
        {
            double div = t[i][leading];
            for (size_t j = leading; j < n * 2; j++)
            {
                t[i][j] -= t[leading][j] * div;
            }
        }
    }

    double **f = new double *[m];

    for (size_t i = 0; i < m; i++)
    {
        f[i] = new double[n];
        for (size_t j = 0; j < n; j++)
        {
            f[i][j] = t[i][j + n];
        }
    }
    for (size_t i = 0; i < m; i++)
    {
        delete [] t[i];
    }
    delete [] t;

    inverted_matrix.setMatrix(f);
    return inverted_matrix;
}
