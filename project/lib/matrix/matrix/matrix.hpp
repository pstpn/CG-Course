#pragma once

#include "Matrix.h"

template <typename Type>
std::shared_ptr<typename Matrix<Type>::MatrixRow[]>
Matrix<Type>::alloc_matrix(size_t rows, size_t cols)
{
    std::shared_ptr<MatrixRow[]> matr_ptr(new MatrixRow[rows]);
    try
    {
        for (size_t i = 0; i < rows; i++)
            matr_ptr[i].reset(new Type[cols], cols);
    }
    catch (std::bad_alloc &err)
    {
        throw Memory_Allocation_Exception(__FILE__, __LINE__, __TIME__, "memory allocation error");
    }
    return matr_ptr;
}
template <typename Type>
Matrix<Type>::Matrix(size_t rows, size_t columns)
{
    this->rows = rows;
    this->cols = columns;
    this->matrix_ptr = alloc_matrix(rows, columns);
}
template <typename Type>
Matrix<Type>::Matrix(Type **c_matrix, size_t rows, size_t cols)
{
    this->rows = rows;
    this->cols = cols;
    this->matrix = alloc_matrix(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            matrix_ptr[i][j] = c_matrix[i][j];
}
template <typename Type>
Matrix<Type>::Matrix(size_t rows, size_t columns, const Type &filler)
{
    this->rows = rows;
    this->cols = columns;
    this->matrix_ptr = alloc_matrix(rows, columns);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            matrix_ptr[i][j] = filler;
}
template <typename Type>
Matrix<Type>::Matrix(std::initializer_list<std::initializer_list<Type> > init_list)
{
    size_t rows = init_list.size();
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto &row_list: init_list)
        if (row_list.size() != cols)
        {
            throw Wrong_Init_List_Exception(__FILE__, __LINE__, __TIME__, "wrong size of initializer row (must be equal)");
        }

    this->rows = rows;
    this->cols = cols;
    this->matrix_ptr = alloc_matrix(rows, cols);
    size_t i = 0;
    for (const auto &ilist: init_list)
        for (const auto &elem: ilist)
        {
            matrix_ptr[i / cols][i % cols] = elem;
            i++;
        }
}
template <typename Type>
Matrix<Type>::Matrix(const Matrix &matrix) : MatrixBase(matrix.rows, matrix.cols)
{
    this->matrix_ptr = alloc_matrix(matrix.rows, matrix.cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            matrix_ptr[i][j] = matrix[i][j];
}
template <typename Type>
Matrix<Type>::Matrix(Matrix &&matrix) noexcept
{
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->matrix_ptr = matrix.matrix_ptr;
}
//equals
template <typename Type>
Matrix<Type> &Matrix<Type>::operator=(const Matrix &matrix)
{
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->matrix_ptr = alloc_matrix(matrix.rows, matrix.cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            matrix_ptr[i][j] = matrix[i][j];
    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator=(Matrix<Type> &&matrix) noexcept
{
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->matrix_ptr = matrix.matrix_ptr;
    return *this;
}
template <typename Type>
Matrix<Type> &Matrix<Type>::operator=(std::initializer_list<std::initializer_list<Type> > init_list)
{
    Matrix<Type>tmp = Matrix(init_list);
    *this = tmp;
    return *this;
}
// iterators
template <typename Type>
MatrixIterator<Type> Matrix<Type>::begin()
{
    MatrixIterator<Type> iter(matrix_ptr, rows, cols, 0);
    return iter;
}
template <typename Type>
MatrixIterator<Type> Matrix<Type>::end()
{
    MatrixIterator<Type> iter(matrix_ptr, rows, cols, cols * rows);
    return iter;
}
// template <typename Type>
// ConstMatrixIterator<Type> Matrix<Type>::begin() const
// {
//     ConstMatrixIterator<Type> iter(matrix_ptr, rows, cols, 0);
//     return iter;
// }
// template <typename Type>
// ConstMatrixIterator<Type> Matrix<Type>::end() const
// {
//     ConstMatrixIterator<Type> iter(matrix_ptr, rows, cols, cols * rows);
//     return iter;
// }
// template <typename Type>
// ConstMatrixIterator<Type> Matrix<Type>::cbegin() const
// {
//     ConstMatrixIterator<Type> iter(matrix_ptr, rows, cols, 0);
//     return iter;
// }
// template <typename Type>
// ConstMatrixIterator<Type> Matrix<Type>::cend() const
// {
//     ConstMatrixIterator<Type> iter(matrix_ptr, rows, cols, cols * rows);
//     return iter;
// }
// template <typename Type>
// bool Matrix<Type>::operator==(const Matrix& matrix) const
// {
//     ConstMatrixIterator<Type> lhs_iter = begin();
//     ConstMatrixIterator<Type> rhs_iter = matrix.begin();

//     for (; lhs_iter != this->end(); lhs_iter++, rhs_iter++)
//     {
//         if (*lhs_iter != *rhs_iter)
//             return false;
//     }
//     if (rhs_iter != matrix.end())
//         return false;
//     return true;
// }
// template <typename Type>
// bool Matrix<Type>::operator!=(const Matrix& matrix) const
// {
//     return !((*this) == matrix);
// }
template <typename Type>
typename Matrix<Type>::MatrixRow & Matrix<Type>::operator[](size_t row)
{
    return matrix_ptr[row];
}
template <typename Type>
const typename Matrix<Type>::MatrixRow & Matrix<Type>::operator[](size_t row) const
{
    return matrix_ptr[row];
}
// template <typename Type>
// Matrix<Type> Matrix<Type>::operator+(const Matrix<Type> &matrix) const
// {
//     if (matrix.rows != rows || matrix.cols != cols)
//     {
//         throw Sizes_Differ_Exception(__FILE__, __LINE__, __TIME__,
//                                      "impossible to make operation: sizes of matrix are incorrect");
//     }
//     Matrix<Type> result(rows, cols);
//     for (size_t i = 0; i < matrix.rows; i++)
//         for (size_t j = 0; j < matrix.cols; j++)
//             result[i][j] = matrix[i][j] + matrix_ptr[i][j];
//     return result;
// }
// template <typename Type>
// Matrix<Type> &Matrix<Type>::operator+=(const Matrix &matrix)
// {
//     if (matrix.rows != rows || matrix.cols != cols)
//     {
//         throw Sizes_Differ_Exception(__FILE__, __LINE__, __TIME__,
//                                      "impossible to make operation: sizes of matrix are incorrect");
//     }
//     for (size_t i = 0; i < matrix.rows; i++)
//         for (size_t j = 0; j < matrix.cols; j++)
//             matrix_ptr[i][j] += matrix[i][j];
//     return *this;
// }
// template <typename Type>
// Matrix<Type> Matrix<Type>::operator-(const Matrix<Type> &matrix) const
// {
//     if (matrix.rows != rows || matrix.cols != cols)
//         throw Sizes_Differ_Exception(__FILE__, __LINE__, __TIME__, "impossible to make operation: sizes of matrix are incorrect");
//     Matrix<Type> result(rows, cols);
//     for (size_t i = 0; i < matrix.rows; i++)
//         for (size_t j = 0; j < matrix.cols; j++)
//             result[i][j] = matrix_ptr[i][j] - matrix[i][j];
//     return result;
// }
// template <typename Type>
// Matrix<Type> &Matrix<Type>::operator-=(const Matrix &matrix)
// {
//     if (matrix.rows != rows || matrix.cols != cols)
//         throw Sizes_Differ_Exception(__FILE__, __LINE__, __TIME__, "impossible to make operation: sizes of matrix are incorrect");
//     for (size_t i = 0; i < matrix.rows; i++)
//         for (size_t j = 0; j < matrix.cols; j++)
//             matrix_ptr[i][j] -= matrix[i][j];
//     return *this;
// }
template <typename Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type> &matrix) const
{
    if (cols != matrix.rows)
        throw Sizes_Differ_Exception(__FILE__, __LINE__, __TIME__, "impossible to make operation: sizes of matrix are incorrect");
    Matrix<Type> result(rows, matrix.cols);
    for (size_t i = 0; i < rows; i++)
        for (size_t k = 0; k < matrix.cols; k++)
        {
            result[i][k] = 0;
            for (size_t j = 0; j < cols; j++)
                result[i][k] += matrix_ptr[i][j] * matrix[j][k];
        }
    return result;
}
template <typename Type>
Matrix<Type> Matrix<Type>::operator*(const Type &elem) const noexcept
{
    Matrix<Type>res(*this);
    for (auto &el : res)
        el *= elem;
    return res;
}
template <typename Type>
Matrix<Type> &Matrix<Type>::operator*=(const Matrix &matrix)
{
    if (cols != matrix.rows)
        throw Sizes_Differ_Exception(__FILE__, __LINE__, __TIME__, "impossible to make operation: sizes of matrix are incorrect");
    Matrix<Type> result(rows, matrix.cols);
    for (size_t i = 0; i < rows; i++)
        for (size_t k = 0; k < matrix.cols; k++)
        {
            result[i][k] = 0;
            for (size_t j = 0; j < cols; j++)
                result[i][k] += matrix_ptr[i][j] * matrix[j][k];
        }
    *this = result;
    return *this;
}
template <typename Type>
Matrix<Type> &Matrix<Type>::operator*=(const Type &elem) noexcept
{
    for (auto &el : *this)
        el *= elem;
    return (*this);
}

template <typename Type>
Type &Matrix<Type>::MatrixRow::operator[](size_t index)
{
    if (index >= size)
    {
        throw Index_Out_Of_Range_Exception(__FILE__, __LINE__, __TIME__, "column index out of range");
    }
    return row[index];
}

template <typename Type>
const Type &Matrix<Type>::MatrixRow::operator[](size_t index) const
{
    if (index >= size)
    {
        throw Index_Out_Of_Range_Exception(__FILE__, __LINE__, __TIME__, "column index out of range");
    }
    return row[index];
}
template <typename Type>
void Matrix<Type>::MatrixRow::reset(Type *row, const size_t size) {
    this->size = size;
    this->row.reset(row);
}

template <typename Type>
void Matrix<Type>::MatrixRow::reset() {
    size = 0;
    row.reset();
}
