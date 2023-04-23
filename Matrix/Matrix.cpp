#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <cmath>

#include "MatrixExceptions.h"
#include "Matrix.h"

using std::copy;
using std::cout;
using std::endl;
using std::initializer_list;
using std::setprecision;
using std::setw;

Matrix::Matrix()
{
    mRows = 0;
    mCols = 0;
    mA = NULL;
    mDet = 0;
    mHasCalculatedDet = false;
}

Matrix::~Matrix()
{
    cleanUp();
}

Matrix::Matrix(const Matrix &b)
{
    this->mRows = b.mRows;
    this->mCols = b.mCols;
    this->mDet = b.mDet;
    this->mHasCalculatedDet = b.mHasCalculatedDet;
    this->mA = new double *[this->mRows];

    for (size_t i = 0; i < mRows; i++)
    {
        this->mA[i] = new double[this->mCols];
        for (size_t j = 0; j < mCols; j++)
        {
            this->mA[i][j] = b.mA[i][j];
        }
    }
}

Matrix::Matrix(size_t rows, size_t cols, double **a)
{
    mRows = rows;
    mCols = cols;
    mDet = 0;
    mHasCalculatedDet = false;
    setMatrix(a);
}

Matrix::Matrix(size_t rows, size_t cols, double initialValue)
{
    mRows = rows;
    mCols = cols;
    mDet = 0;
    mHasCalculatedDet = false;
    mA = new double *[rows];
    for (size_t i = 0; i < rows; i++)
    {
        mA[i] = new double[cols];
        for (size_t j = 0; j < cols; j++)
        {
            mA[i][j] = initialValue;
        }
    }
}

Matrix::Matrix(initializer_list<initializer_list<double>> initializerMatrix) throw(InconsistentColumns)
{
    mRows = initializerMatrix.size();
    mCols = initializerMatrix.begin()->size();
    mDet = 0;
    mHasCalculatedDet = false;

    auto pR = initializerMatrix.begin();
    for (size_t i = 0; i < mRows; i++, pR++)
    {
        if (pR->size() != mCols)
        {
            mRows = 0;
            mCols = 0;
            throw InconsistentColumns("Failed");
        }
    }

    mA = new double *[mRows];
    auto pI = initializerMatrix.begin();
    for (size_t i = 0; i < mRows; i++, pI++)
    {
        mA[i] = new double[mCols];
        copy(pI->begin(), pI->end(), mA[i]);
    }
}

Matrix Matrix::diagonal(size_t size, initializer_list<double> values)
{
    Matrix diag(size, size);
    auto pL = values.begin();
    for (size_t i = 0; i < size && pL != values.end(); i++, pL++)
    {
        diag.mA[i][i] = *pL;
    }
    return diag;
}

Matrix Matrix::identity(size_t size, double scaledBy)
{
    Matrix I(size, size);
    for (size_t i = 0; i < size; i++)
    {
        I.mA[i][i] = 1 * scaledBy;
    }
    return I;
}

void Matrix::cleanUp()
{
    if (mA == NULL)
    {
        return;
    }

    for (size_t i = 0; i < mRows; i++)
    {
        if (mCols == 1)
            delete mA[i];
        else
            delete[] mA[i];
    }
    if (mRows == 1)
        delete mA;
    else
        delete[] mA;
    
}

void Matrix::setMatrix(double **a)
{
    cleanUp();
    mA = a;
}

Matrix Matrix::T() const
{
    double **b;
    b = new double *[mCols];
    for (size_t i = 0; i < mCols; i++)
    {
        b[i] = new double[mRows];
        for (size_t j = 0; j < mRows; j++)
        {
            b[i][j] = mA[j][i];
        }
    }
    Matrix t(mCols, mRows);
    t.setMatrix(b);
    return t;
}

void Matrix::show(size_t colWidth, size_t precision) const
{
    for (size_t i = 0; i < mRows; i++)
    {
        for (size_t j = 0; j < mCols; j++)
        {
            cout << setw(colWidth) << std::fixed << setprecision(precision) << std::right << mA[i][j];
        }
        cout << endl;
    }
}

Matrix Matrix::mM(size_t i, size_t j) const
{
    Matrix minor(mRows - 1, mCols - 1);

    double **b = new double *[mRows - 1];

    int b_i = 0;
    int b_j = 0;

    for (size_t _i = 0; _i < mRows; _i++)
    {
        if (_i != i)
        {
            b[b_i] = new double[mCols - 1];
            b_j = 0;
            for (size_t _j = 0; _j < mCols; _j++)
            {
                if (_j != j)
                {
                    b[b_i][b_j] = mA[_i][_j];
                    b_j++;
                }
            }
            b_i++;
        }
    }
    minor.setMatrix(b);
    return minor;
}

bool Matrix::setDet()
{
    try
    {
        mDet = calculateDet();
        mHasCalculatedDet = true;
        return true;
    }
    catch (NoDeterminant &e)
    {
        std::cerr << e.what() << '\n';
        mDet = 0;
        mHasCalculatedDet = false;
        return false;
    }
}

bool Matrix::hasCalculatedDet() const
{
    return mHasCalculatedDet;
}

double Matrix::calculateDet() const throw(NoDeterminant)
{
    double d;
    if (mRows != mCols)
    {
        throw NoDeterminant(mRows, mCols);
    }

    d = 0;
    if (rows() == 2)
    {
        d += at(0, 0) * at(1, 1) - at(1, 0) * at(0, 1);
    }
    else
    {
        for (size_t i = 0; i < mCols; i++)
        {
            if (at(0, i) == 0)
            {
                continue;
            }
            Matrix minor = mM(0, i);
            d += minor.calculateDet() * at(0, i) * std::pow(-1, 1 + (i + 1));
        }
    }
    return d;
}

double Matrix::det() const throw(HaventCalculatedDeterminant, NoDeterminant)
{
    if (mRows != mCols)
    {
        throw NoDeterminant(mRows, mCols);
    }

    if (!mHasCalculatedDet)
    {
        throw HaventCalculatedDeterminant();
    }

    return mDet;
}

size_t Matrix::cols() const
{
    return mCols;
}
size_t Matrix::rows() const
{
    return mRows;
}

Matrix Matrix::scale(double scaler) const
{

    double **temp = new double *[mRows];
    for (size_t i = 0; i < mRows; i++)
    {
        temp[i] = new double[mCols];
        for (size_t j = 0; j < mCols; j++)
        {
            temp[i][j] = mA[i][j] * scaler;
        }
    }

    Matrix r(mRows, mCols);
    r.setMatrix(temp);
    return r;
}

Matrix Matrix::dot(const Matrix &b) const throw(IncompatibleShape)
{
    if (this->mCols != b.mRows)
    {
        throw IncompatibleShape(this->mRows, this->mCols, b.mRows, b.mCols, '*');
    }
    Matrix productMatrix(this->mRows, b.mCols);
    double **temp = new double *[this->mRows];

    for (size_t i = 0; i < this->mRows; i++)
    {
        temp[i] = new double[b.mCols];
        for (size_t j = 0; j < b.mCols; j++)
        {
            double sumProduct = 0;
            for (size_t k = 0; k < this->mCols; k++)
            {
                sumProduct += mA[i][k] * b.mA[k][j];
            }
            temp[i][j] = sumProduct;
        }
    }
    productMatrix.setMatrix(temp);
    return productMatrix;
}

Matrix Matrix::operator*(const Matrix &b) const throw(IncompatibleShape)
{
    return dot(b);
}

Matrix Matrix::operator*(double scaler) const
{
    return scale(scaler);
}

Matrix Matrix::pow(size_t power) const throw(IncompatibleShape)
{
    if (mRows != mCols)
    {
        throw IncompatibleShape(mRows, mCols, mRows, mCols, '^');
    }

    Matrix result = Matrix::identity(mRows);
    Matrix base(*this);

    while (power > 0)
    {
        if (power % 2 == 1)
        {
            result = result * base;
        }
        base = base * base;
        power /= 2;
    }
    return result;
}

Matrix Matrix::operator^(size_t power) const throw(IncompatibleShape)
{
    return pow(power);
}

double Matrix::at(size_t i, size_t j) const
{
    return mA[i][j];
}

Matrix operator*(double scaler, const Matrix &matrix)
{
    return matrix.scale(scaler);
}

Matrix Matrix::inverse() const
{
    try
    {
        if (det() == 0)
        {
            throw "Not invertible\n";
        }
    }
    catch (NoDeterminant &e)
    {
        cout << "Can not invert Matrix " << e.rows() << "x" << e.cols();
    }
    catch (HaventCalculatedDeterminant &e)
    {
        if (calculateDet() == 0)
        {
            throw "Not invertible\n";
        }
    }

    Matrix input(*this);
    Matrix output = Matrix::identity(mRows);

    // Top down leading 1
    for (size_t leading = 0; leading < mRows; leading++)
    {
        // Swap leading row to top
        for (size_t lR = leading; lR < mRows; lR++)
        {
            if (input.at(lR, leading) != 0)
            {
                input.rowSwap(leading, lR);
                output.rowSwap(leading, lR);
                break;
            }
        }

        double leadingDivisor = input.at(leading, leading);

        input.rowScale(leading, 1 / leadingDivisor);
        output.rowScale(leading, 1 / leadingDivisor);

        for (size_t i = leading + 1; i < mRows; i++)
        {
            double scaler = input.at(i, leading);

            input.rowAdd(leading, i, -scaler);
            output.rowAdd(leading, i, -scaler);
        }
    }

    // Bottom up reduce row echelon
    for (size_t leading = mRows - 1; leading > 0; leading--)
    {
        for (int i = leading - 1; i >= 0; i--)
        {
            double scaler = input.at(i, leading);

            input.rowAdd(leading, i, -scaler);
            output.rowAdd(leading, i, -scaler);
        }
    }

    return output;
}

bool Matrix::rowSwap(size_t rowI, size_t rowJ)
{
    if (rowI > (mRows - 1) || rowJ > (mRows - 1))
    {
        return false;
    }

    if (mA == NULL)
    {
        return false;
    }

    if (mA[rowI] == NULL || mA[rowJ] == NULL)
    {
        return false;
    }

    std::swap(mA[rowI], mA[rowJ]);
    return true;
}

bool Matrix::rowScale(size_t rowI, double scaler)
{
    if (rowI > (mRows - 1))
    {
        return false;
    }

    if (mA == NULL || mA[rowI] == NULL)
    {
        return false;
    }

    double *&operationRow = mA[rowI];

    for (size_t j = 0; j < mCols; j++)
    {
        operationRow[j] *= scaler;
    }

    return true;
}

bool Matrix::rowAdd(size_t rowI, size_t rowJ, double scaler)
{
    if (rowI > (mRows - 1) || rowJ > (mRows - 1))
    {
        return false;
    }

    if (mA == NULL)
    {
        return false;
    }

    if (mA[rowI] == NULL || mA[rowJ] == NULL)
    {
        return false;
    }

    double *&operationRowI = mA[rowI];
    double *&operationRowJ = mA[rowJ];

    for (size_t j = 0; j < mCols; j++)
    {
        operationRowJ[j] += scaler * operationRowI[j];
    }

    return true;
}

void Matrix::operator=(const Matrix &b)
{
    cleanUp();
    this->mRows = b.mRows;
    this->mCols = b.mCols;
    this->mDet = 0;
    this->mHasCalculatedDet = false;

    this->mA = new double *[b.mRows];

    for (size_t i = 0; i < b.mRows; i++)
    {
        this->mA[i] = new double[b.mCols];
        for (size_t j = 0; j < b.mCols; j++)
        {
            this->mA[i][j] = b.mA[i][j];
        }
    }
}

bool Matrix::equals(const Matrix &b) const
{
    if (this->mRows != b.mRows || this->mCols != b.mCols)
    {
        return false;
    }

    for (size_t i = 0; i < mRows; i++)
        for (size_t j = 0; j < mCols; j++)
            if (this->at(i, j) != b.at(i, j))
                return false;

    return true;
}

bool Matrix::operator==(const Matrix &b) const
{
    return equals(b);
}

Matrix Matrix::add(const Matrix &b) const throw(IncompatibleShape)
{
    if (this->mRows != b.mRows || this->mCols != b.mCols)
    {
        throw IncompatibleShape(this->mRows, this->mCols, b.mRows, b.mCols, '+');
    }

    Matrix result(*this);
    for (size_t i = 0; i < this->mRows; i++)
    {
        for (size_t j = 0; j < this->mCols; j++)
        {
            result.mA[i][j] += b.at(i, j);
        }
    }

    return result;
}

Matrix Matrix::operator+(const Matrix &b) const throw(IncompatibleShape)
{
    return add(b);
}

Matrix Matrix::add(double a) const
{
    Matrix result(*this);
    for (size_t i = 0; i < mRows; i++)
        for (size_t j = 0; j < mCols; j++)
            result.mA[i][j] += a;

    return result;
}

Matrix Matrix::operator+(double a) const
{
    return add(a);
}

Matrix operator+(double a, const Matrix &matrix)
{
    return matrix.add(a);
}

Matrix Matrix::vStack(const Matrix &b) const throw(IncompatibleShape)
{
    if (this->mCols != b.mCols)
    {
        throw IncompatibleShape(this->mRows, this->mCols, b.mRows, b.mCols, '-');
    }

    Matrix result(this->mRows + b.mRows, this->mCols);

    for (size_t i = 0; i < this->mRows; i++)
        for (size_t j = 0; j < this->mCols; j++)
            result.mA[i][j] = this->mA[i][j];

    for (size_t i = 0; i < b.mRows; i++)
        for (size_t j = 0; j < b.mCols; j++)
            result.mA[i + this->mRows][j] = b.mA[i][j];

    return result;
}

Matrix Matrix::hStack(const Matrix &b) const throw(IncompatibleShape)
{
    if (this->mRows != b.mRows)
    {
        throw IncompatibleShape(this->mRows, this->mCols, b.mRows, b.mCols, '|');
    }

    Matrix result(this->mRows, this->mCols + b.mCols);

    for (size_t j = 0; j < this->mCols; j++)
        for (size_t i = 0; i < this->mRows; i++)
            result.mA[i][j] = this->mA[i][j];

    for (size_t j = 0; j < b.mCols; j++)
        for (size_t i = 0; i < b.mRows; i++)
            result.mA[i][j + this->mCols] = b.mA[i][j];

    return result;
}