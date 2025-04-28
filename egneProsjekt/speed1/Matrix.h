// Matrix.h
#include <iostream>
#include <stdexcept> // for std::invalid_argument
#include <algorithm> // for std::copy, std::fill_n
#include <memory>   // for std::unique_ptr
#include <initializer_list> // for std::initializer_list
#include <cstddef> // for size_t
#include <utility> // for std::move
#include <vector>
#include <span>

template<typename T>
class Matrix {
public:
    // Default: zero×zero matrix
    Matrix() : _rows(0), _cols(0), _m_size(0), _data(nullptr) {}

    // Dimensions constructor default (=0)
    Matrix(size_t rows, size_t cols);

    // Dimensions constructor with specifed values
    Matrix(size_t rows, size_t cols, const T& value);

    // 2d init list assignment
    Matrix(const std::initializer_list<std::initializer_list<T>>& init);

    // Copy constructor & assignment (deep copy)
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    // Move constructor & assignment (steal data)
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(Matrix&& other) noexcept;

    /* Matrix operations */
    virtual Matrix& operator+=(const Matrix& other) ;
    virtual Matrix& operator-=(const Matrix& other) ;

    Matrix operator+(const Matrix& other) const ;
    Matrix operator-(const Matrix& other) const ;

    Matrix& operator*=(const Matrix& other) ;
    Matrix& operator/=(const Matrix& other) ;

    Matrix operator*(const Matrix& other) const ;
    Matrix operator/(const Matrix& other) const ;





    std::vector<T> get_row(int row_number)  const { // get row vector
        std::vector<T> row(_cols);
        std::copy_n(_data.get() + row_number * _cols, _cols, row.begin());
        return row;
    }


    std::vector<T> get_col(int column_number)  const { // get row vector
        std::vector<T> col(_rows);
        for (size_t i = 0; i < _rows; ++i) {
            col[i] = _data[i * _cols + column_number];
        }
        return col;
    }

    std::span<T> get_row_view(int row_number) {
        return std::span<T>(_data.get() + row_number * _cols, _cols);
    }

    std::span<T> get_col_view(int column_number) {
        return std::span<T>(_data.get() + column_number, _rows, _cols);
    }

    // iterations 

    virtual void operator++() { // Prefix
        for (size_t i = 0; i < _m_size; ++i)
            _data[i] += 1;
        //return *this;
    }
    
    virtual void operator++(int) { // Postfix
        Matrix temp = *this;
        ++(*this);
        //return temp;
    }


    // TBD: cross, dot, transpose, inverse, etc.
    Matrix transpose() const {
        Matrix<T> result(_cols, _rows);
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                result._data[j * _rows + i] = _data[i * _cols + j];
            }
        }
        return result;
    }

    void transpose() {
        Matrix<T> result(_cols, _rows);
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                result._data[j * _rows + i] = _data[i * _cols + j];
            }
        }
        *this = std::move(result);
    }

    Matrix<T> inverse() const {
        if (_rows != _cols) {
            throw std::invalid_argument("Only square matrices can be inverted");
        }
    
        const size_t n = _rows;
    
        // Create a copy of the matrix and the identity matrix (for the result)
        Matrix<T> result(n, n, T());
        Matrix<T> copy(*this);  // Copy of the matrix to work with
    
        // Initialize result as identity matrix
        for (size_t i = 0; i < n; ++i) {
            result(i, i) = T(1);
        }
    
        // Perform LU decomposition on the matrix (copy)
        for (size_t i = 0; i < n; ++i) {
            // Find pivot: largest element in the current column
            size_t pivotRow = i;
            for (size_t j = i + 1; j < n; ++j) {
                if (std::abs(copy(j, i)) > std::abs(copy(pivotRow, i))) {
                    pivotRow = j;
                }
            }
    
            if (copy(pivotRow, i) == T(0)) {
                throw std::runtime_error("Matrix is singular and cannot be inverted");
            }
    
            // Swap rows to make the pivot the largest element
            if (pivotRow != i) {
                for (size_t j = 0; j < n; ++j) {
                    std::swap(copy(i, j), copy(pivotRow, j));
                    std::swap(result(i, j), result(pivotRow, j));
                }
            }
    
            // Normalize the pivot row
            T pivot = copy(i, i);
            for (size_t j = 0; j < n; ++j) {
                copy(i, j) /= pivot;
                result(i, j) /= pivot;
            }
    
            // Eliminate other rows
            for (size_t k = 0; k < n; ++k) {
                if (k == i) continue; // Skip the pivot row
                T factor = copy(k, i);
                for (size_t j = 0; j < n; ++j) {
                    copy(k, j) -= factor * copy(i, j);
                    result(k, j) -= factor * result(i, j);
                }
            }
        }
    
        return result;
    }
    
    void inverse() {
        if (_rows != _cols) {
            throw std::invalid_argument("Only square matrices can be inverted");
        }
    
        const size_t n = _rows;
    
        // Create a copy of the matrix and the identity matrix (for the result)
        Matrix<T> result(n, n, T());
        Matrix<T> copy(*this);  // Copy of the matrix to work with
    
        // Initialize result as identity matrix
        for (size_t i = 0; i < n; ++i) {
            result(i, i) = T(1);
        }
    
        // Perform LU decomposition on the matrix (copy)
        for (size_t i = 0; i < n; ++i) {
            // Find pivot: largest element in the current column
            size_t pivotRow = i;
            for (size_t j = i + 1; j < n; ++j) {
                if (std::abs(copy(j, i)) > std::abs(copy(pivotRow, i))) {
                    pivotRow = j;
                }
            }
    
            if (copy(pivotRow, i) == T(0)) {
                throw std::runtime_error("Matrix is singular and cannot be inverted");
            }
    
            // Swap rows to make the pivot the largest element
            if (pivotRow != i) {
                for (size_t j = 0; j < n; ++j) {
                    std::swap(copy(i, j), copy(pivotRow, j));
                    std::swap(result(i, j), result(pivotRow, j));
                }
            }
    
            // Normalize the pivot row
            T pivot = copy(i, i);
            for (size_t j = 0; j < n; ++j) {
                copy(i, j) /= pivot;
                result(i, j) /= pivot;
            }
    
            // Eliminate other rows
            for (size_t k = 0; k < n; ++k) {
                if (k == i) continue; // Skip the pivot row
                T factor = copy(k, i);
                for (size_t j = 0; j < n; ++j) {
                    copy(k, j) -= factor * copy(i, j);
                    result(k, j) -= factor * result(i, j);
                }
            }
        }
    
        // Use move semantics to assign the result to *this (in-place modification)
        *this = std::move(result);
    }


    /*
    // C++ 20 concept 
    template<typename Other>
    requires std::is_base_of_v<Matrix<T>, Other>
    virtual Matrix& operator-=(const Other & other) {
        if (_rows != other.get_rows() || _cols != other.get_cols()) {
            throw std::invalid_argument("Matrix dimensions must agree for subtraction");
        }
        for (size_t i = 0; i < _m_size; ++i) {
            _data[i] += other.at(i);
        }
        std::cout << "Matrix -= operator called" << std::endl;

        return *this;
    }
    */ 


    // Destructor
    ~Matrix();

    // Access element (row-major)
    virtual T& at(size_t r, size_t c);
    virtual const T& at(size_t r, size_t c) const;

    virtual T& at(size_t i) { return _data[i] ;}  // 1d access
    virtual const T& at(size_t i) const { return _data[i]; } // 1d access
    
    
    size_t get_rows() const;
    size_t get_cols() const;
    size_t get_size() const; // get total 1d size


    const T* get_data() const { 
        return _data.get();  // Return a raw pointer to the data managed by unique_ptr
    }

private:
    size_t _rows, _cols, _m_size;
    std::unique_ptr<T[]> _data; // length = rows*cols
};

template<typename T>
Matrix<T>::~Matrix() {
    // No explicit cleanup needed as std::unique_ptr handles memory management
}

// Default constructor, zero matrix
template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) 
    : _rows(rows), _cols(cols), _m_size(rows * cols), _data(std::make_unique<T[]>(rows * cols)) {
    std::fill_n(_data.get(), _m_size, T()); // Use std::fill_n for efficient initialization
}

// Constructor with specified values
template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T& value)
    : _rows(rows), _cols(cols), _m_size(rows * cols), _data(std::make_unique<T[]>(rows * cols)) {
    std::fill_n(_data.get(), _m_size, value); // Initialize all elements with the specified value
}

/* init list constructor */
template<typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& init)
    : _rows(init.size()),
      _cols(init.begin()->size()),
      _m_size(_rows * _cols),
      _data(std::make_unique<T[]>(_m_size)) {
    std::cout<< "init list initializer" << std::endl;
    size_t i = 0;
    for (const auto& row : init) {
        if (row.size() != _cols) {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
        for (const auto& val : row) {
            _data[i++] = val;
        }
    }
}

// Copy constructor (deep copy)
template<typename T>
Matrix<T>::Matrix(const Matrix& other)
    : _rows(other._rows), _cols(other._cols), _m_size(other._m_size), _data(std::make_unique<T[]>(other._m_size)) {
    std::copy(other._data.get(), other._data.get() + _m_size, _data.get());
    std::cout<< "Copy constructor" << std::endl;

}

// Copy assignment operator
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if (this != &other) { // Avoid self-assignment
        _rows = other._rows;
        _cols = other._cols;
        _m_size = other._m_size;
        _data = std::make_unique<T[]>(_m_size);
        std::copy(other._data.get(), other._data.get() + _m_size, _data.get());
    }
    
    std::cout<< "Copy assignment" << std::endl;

    return *this;
}

// Move constructor (steal data)
// std::move is used to transfer ownership of the data from 'other' to 'this' : it voids the other smartpointer
template<typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
    : _rows(other._rows), _cols(other._cols), _m_size(other._m_size), _data(std::move(other._data)) {
    other._rows = 0;
    other._cols = 0;
    other._m_size = 0;
    std::cout<< "Move constructor" << std::endl;

}

// Move assignment operator (steal data)
// std::move is used to transfer ownership of the data from 'other' to 'this' : it voids the other smartpointer
template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
    if (this != &other) { // Avoid self-assignment
        _rows = other._rows;
        _cols = other._cols;
        _m_size = other._m_size;
        _data = std::move(other._data);
        other._rows = 0;
        other._cols = 0;
        other._m_size = 0;
    }

    // std::cout<< "Move assignment" << std::endl;
    return *this;
}


template<typename T>
size_t Matrix<T>::get_cols() const  {
    return _cols;
}

template<typename T>
size_t Matrix<T>::get_rows() const {
    return _rows;
}

template<typename T>
size_t Matrix<T>::get_size() const {
    return _m_size;
}


/* Matrix operations */

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& other) {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must agree for addition");
    }
    for (size_t i = 0; i < _m_size; ++i) {
        _data[i] += other._data[i];
    }
    // std::cout << "Matrix += operator called" << std::endl;
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& other) {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must agree for subtraction");
    }

    /*
    
     would be faster : const T* other_data = other.get_data();

    
    for (size_t i = 0; i < _m_size; ++i) {
        _data[i] -= other_data[i];  // Now directly accessing the data
    } */


    for (size_t i = 0; i < _m_size; ++i) {
        _data[i] -= other._data[i];
    }


    // std::cout << "Matrix -= operator called" << std::endl;

    return *this;
}



template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix& other)   {
    if (_cols != other._rows) {
        throw std::invalid_argument("Matrix dimensions must agree for multiplication");
    }
    Matrix<T> result(_rows, other._cols, T());
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < other._cols; ++j) {
            for (size_t k = 0; k < _cols; ++k) {
                result._data[i * other._cols + j] += _data[i * _cols + k] * other._data[k * other._cols + j];
            }
        }
    }
    *this = std::move(result);
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(const Matrix& other) {
    throw std::logic_error("Matrix division is not defined");
}


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must agree for addition");
    }
    Matrix result(_rows, _cols);
    for (size_t i = 0; i < _m_size; ++i) {
        result._data[i] = _data[i] + other._data[i];
    }
    return result;
}


template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
    if (_rows != other._rows || _cols != other._cols) {
        throw std::invalid_argument("Matrix dimensions must agree for subtraction");
    }
    Matrix result(_rows, _cols);
    for (size_t i = 0; i < _m_size; ++i) {
        result._data[i] = _data[i] - other._data[i];
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const {
    if (_cols != other._rows) {
        throw std::invalid_argument("Matrix dimensions must agree for multiplication");
    }
    Matrix result(_rows, other._cols, T());
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < other._cols; ++j) {
            for (size_t k = 0; k < _cols; ++k) {
                result._data[i * other._cols + j] += _data[i * _cols + k] * other._data[k * other._cols + j];
            }
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const Matrix& other) const {
    throw std::logic_error("Matrix division is not defined");
}


template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix<T> const& m) {
    os << "\n";
    for (size_t i = 0; i < m.get_rows(); ++i) {
        os << "| ";
        for (size_t j = 0; j < m.get_cols(); ++j) {
            os << m.at(i, j) << ' ';
        }
        os << "|";
        os << "\n";
    }
    os << "\n ";
    return os;
}


template<typename T>
T& Matrix<T>::at(size_t r, size_t c) {
    if (r >= _rows || c >= _cols) {
        throw std::out_of_range("Matrix::at(): index out of range");
    }
    return _data[r * _cols + c];
}

template<typename T>
const T& Matrix<T>::at(size_t r, size_t c) const {
    if (r >= _rows || c >= _cols) {
        throw std::out_of_range("Matrix::at() const: index out of range");
    }
    return _data[r * _cols + c];
}