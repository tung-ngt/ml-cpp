#ifndef MATRIX_EXCEPTIONS_H
#define MATRIX_EXCEPTIONS_H

#include <iostream>
#include <string>
#include <sstream>

class InconsistentColumns : public std::exception
{
private:
    std::string message;

public:
    InconsistentColumns(const std::string &msg)
    {
        message = msg;
    };

    ~InconsistentColumns() throw(){};
    std::string what()
    {
        return message;
    };
};

class NoDeterminant : public std::exception
{
private:
    size_t mRows;
    size_t mCols;

public:
    NoDeterminant(const size_t &rows, const size_t &cols) : mRows(rows), mCols(cols){};

    size_t rows()
    {
        return mRows;
    };
    size_t cols()
    {
        return mCols;
    };

    std::string what()
    {
        std::stringstream ss;
        ss << "Can not calculate determinant of Matrix " << mRows << "x" << mCols;

        return ss.str();
    };
};

class HaventCalculatedDeterminant : public std::exception
{
public:
    std::string what()
    {
        return "Havent calculated the determinant. Please call calculateDet!";
    };
};

class IncompatibleShape : public std::exception
{
private:
    size_t mARows;
    size_t mACols;
    size_t mBRows;
    size_t mBCols;
    char mOperation;

public:
    IncompatibleShape(size_t aRows, size_t aCols, size_t bRows, size_t bCols, char operation)
    {
        mARows = aRows;
        mACols = aCols;
        mBRows = bRows;
        mBCols = bCols;
        mOperation = operation;
    };

    size_t aRows()
    {
        return mARows;
    };
    size_t aCols()
    {
        return mACols;
    };
    size_t bRows()
    {
        return mBRows;
    };
    size_t bCols()
    {
        return mBCols;
    };
    char operation()
    {
        return mOperation;
    };

    std::string what()
    {
        std::stringstream ss;
        ss << "Incompatible shape: " << mARows
           << "x" << mACols << " " << mOperation << " " << mBRows << "x" << mBCols;
        return ss.str();
    };
};

// class NullMatrix : public std::exception
// {
// private:
//     /* data */
// public:
  
// };



#endif