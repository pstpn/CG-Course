#include <iostream>
# include <memory>

# include "../errors/errors.hpp"

using namespace std;

template <typename Type>
class Matrix;

template <typename Type>
class MatrixIterator
{
public:
    //constructors
    MatrixIterator();
    MatrixIterator(const MatrixIterator &it) = default;
    MatrixIterator(const shared_ptr<typename Matrix<Type>::MatrixRow[]>& matrix_ptr, size_t rows, size_t cols, size_t ind = 0);

    // getting access
    Type& operator*();
    const Type& operator*() const;

    Type* operator->();
    const Type* operator->() const;

    explicit operator bool() const;
    
    // equals
    MatrixIterator<Type>& operator =(const MatrixIterator<Type> &other);
    MatrixIterator<Type>& operator +=(size_t ind);
    MatrixIterator<Type>& operator -=(size_t ind);

    // math
    MatrixIterator<Type>& operator ++();
    MatrixIterator<Type> operator ++(int);
    MatrixIterator<Type> operator +(size_t ind);

    MatrixIterator<Type>& operator --();
    MatrixIterator<Type> operator --(int);
    MatrixIterator<Type> operator -(size_t ind);

    // comparison
    bool operator!=(MatrixIterator const& other) const;
    bool operator==(MatrixIterator const& other) const;
    bool operator<(MatrixIterator const& other) const;
    bool operator>(MatrixIterator const& other) const;
    bool operator<=(MatrixIterator const& other) const;
    bool operator>=(MatrixIterator const& other) const;
    
private:
    void check_index();
    void check_nullptr();
    weak_ptr <typename Matrix<Type>::MatrixRow[]> matrix;
    size_t cols;
    size_t rows;
    size_t index;
};

#include "MatrixIterator.hpp"