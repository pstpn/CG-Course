#pragma once

#include <memory>

// #include "const_matrix_iterator.h"
#include "BaseMatrix.hpp"
#include "matrix_iterator.h"


template <typename Type>
class Matrix final: public MatrixBase
{
public:
    class MatrixRow;
    
    explicit Matrix(size_t rows = 0, size_t columns = 0);
    Matrix(size_t rows, size_t columns, const Type &filler);
    Matrix(std::initializer_list<std::initializer_list<Type> > init_list);
    Matrix(Type **c_matrix, size_t rows, size_t cols); //

    explicit Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix) noexcept;

    Matrix<Type> &operator=(const Matrix &matrix);
    Matrix<Type> &operator=(Matrix &&matrix) noexcept;
    Matrix<Type> &operator=(std::initializer_list<std::initializer_list<Type> > init_list);

    virtual ~Matrix() = default;

    MatrixIterator<Type> begin();
    MatrixIterator<Type> end();
    
    Matrix<Type> operator*(const Matrix &matrix) const;
    Matrix<Type> &operator*=(const Matrix &matrix);
    Matrix<Type> operator*(const Type &elem) const noexcept;
    Matrix<Type> &operator*=(const Type &elem) noexcept;

    MatrixRow &operator[](size_t row);
    const MatrixRow &operator[](size_t row) const;

private:
    std::shared_ptr<MatrixRow[]> matrix_ptr { nullptr };
    std::shared_ptr<MatrixRow[]> alloc_matrix(size_t rows, size_t cols);
    
public:
    class MatrixRow {
    private:
        std::shared_ptr<Type[]> row;
        size_t size;

    public:
        MatrixRow(Type *row, const size_t size): row(row), size(size) { }
        MatrixRow(): row(nullptr), size(0) { }

        Type &operator[](size_t index);
        const Type &operator[](size_t index) const;
        void reset();
        void reset(Type *row, size_t size);
    };
};

#include "matrix.hpp"

