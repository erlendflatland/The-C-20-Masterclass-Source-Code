// MatrixInline.h
#include <iostream>
#include <stdexcept> // for std::invalid_argument
#include <algorithm> // for std::copy, std::fill_n
#include <memory>   // for std::unique_ptr
#include <initializer_list> // for std::initializer_list
#include <cstddef> // for size_t
#include <utility> // for std::move

template<typename T>
class Matrix; // Forward declaration as a template class

template<typename T>
class MatrixInline : public Matrix<T> {
    // Inherits from Matrix class

public:

         
    
    /* inline void operator++() override { // Prefix
        for (size_t i = 0; i < _m_size; ++i)
            _data[i] += 1;
        //return *this;
    } */

    // Default: zero×zero matrix
    inline MatrixInline() : _rows(0), _cols(0), _m_size(0), _data(nullptr) {}

    // Dimensions constructor default (=0)
    inline MatrixInline(size_t rows, size_t cols)
        : _rows(rows), _cols(cols), _m_size(rows * cols), _data(std::make_unique<T[]>(rows * cols)) , Matrix<T>(rows, cols, T()) {
        std::fill_n(_data.get(), _m_size, T());
    }

    // Dimensions constructor with specified values
     MatrixInline(size_t rows, size_t cols, const T& value)
        // _rows(rows), _cols(cols), _m_size(rows * cols), _data(std::make_unique<T[]>(rows * cols))  {
        : _rows(rows), _cols(cols), _m_size(rows * cols), _data(std::make_unique<T[]>(rows * cols)) , Matrix<T>(rows, cols, value) {
            // above invokes base class constructor __ penalty


            std::fill_n(_data.get(), _m_size, value);
    }



    // init list as using base ctor
    
    MatrixInline(const std::initializer_list<std::initializer_list<T>>& init)
        : Matrix<T>(init) // delegate to base class constructor
    {
        // Possibly add extra initialization for MatrixInline
    }



    /* Ctor not automaticl inherited, either use 
    
        A) above (base-initialization) 

        B)  : using Matrix<T>::Matrix; // inside MatrixInline<T> : 
            // will inherit all ctors from Matrix<T>; but not assign derived class members 
    
    */

    /* to be inherited from Matrix class
    // 2d init list assignment
    MatrixInline(const std::initializer_list<std::initializer_list<T>>& init);




    */

    // Copy constructor (deep copy)
    inline MatrixInline(const MatrixInline& other)
        : _rows(other._rows), _cols(other._cols), _m_size(other._m_size), _data(std::make_unique<T[]>(other._m_size)) {
        std::copy(other._data.get(), other._data.get() + _m_size, _data.get());
        std::cout << "Copy constructor" << std::endl;
    }

    // Copy assignment operator
    inline MatrixInline& operator=(const MatrixInline& other) {
        if (this != &other) { // Avoid self-assignment
            _rows = other._rows;
            _cols = other._cols;
            _m_size = other._m_size;
            _data = std::make_unique<T[]>(_m_size);
            std::copy(other._data.get(), other._data.get() + _m_size, _data.get());
        }
        std::cout << "Copy assignment" << std::endl;
        return *this;
    }

    // Move constructor (steal data)
    inline MatrixInline(MatrixInline&& other) noexcept
        : _rows(other._rows), _cols(other._cols), _m_size(other._m_size), _data(std::move(other._data)) {
        other._rows = 0;
        other._cols = 0;
        other._m_size = 0;
        std::cout << "Move constructor" << std::endl;
    }

    // Move assignment operator (steal data)
    inline MatrixInline& operator=(MatrixInline&& other) noexcept {
        if (this != &other) { // Avoid self-assignment
            _rows = other._rows;
            _cols = other._cols;
            _m_size = other._m_size;
            _data = std::move(other._data);
            other._rows = 0;
            other._cols = 0;
            other._m_size = 0;
        }
        std::cout << "Move assignment" << std::endl;
        return *this;
    }


    /* MatrixInline operations */


    // kun denne overrider base-klassen, siden den andre bruker MatrixInline som input
    inline MatrixInline& operator+=(const Matrix<T>& other);


    // ef: TODO; do this in base class, and override here 
    // " you can't use requires or template<typename T> on a virtual method, 
    // because virtual methods must have a fixed, non-template signature."
    // C++ 20 concept
    /*template<typename Other>
    requires std::is_base_of_v<Matrix<T>, Other>
    inline MatrixInline& operator-=(const Other & other) {
        if (_rows != other.get_rows() || _cols != other.get_cols()) {
            throw std::invalid_argument("MatrixInline dimensions must agree for subtraction");
        }
        for (size_t i = 0; i < _m_size; ++i) {
            _data[i] -= other.at(i);
        }
        std::cout << "MatrixInline (requires) -= operator called" << std::endl;
        return *this;
    }*/ 

    
    // we pass by refernce, so also derived objects can be passed
    inline MatrixInline& operator-=(const Matrix<T>& other) override {
        if (_rows != other.get_rows() || _cols != other.get_cols()) {

            std::cout << "rows: " << _rows << " cols: " << _cols << std::endl;
            std::cout << "other rows: " << other.get_rows() << " other cols: " << other.get_cols() << std::endl;
            throw std::invalid_argument("MatrixInline dimensions must agree for subtraction");
        }

        
        const T* other_data = other.get_data();  // Get the raw pointer to the data from the other matrix
        

        std::transform(
            _data.get(), _data.get() + _m_size,    // Range 1
            other.get_data(),                      // Range 2
            _data.get(),                           // Output
            [](const T& a, const T& b) { return a - b; }
        );
        /*
        for (size_t i = 0; i < _m_size; ++i) {
            _data[i] -= other_data[i];
        }  */

        // std::cout << "MatrixInline -= operator called" << std::endl;

        return *this;
    }


    /*
    inline MatrixInline& operator-=(const MatrixInline& other) {
        if (_rows != other.get_rows() || _cols != other.get_cols()) {
            throw std::invalid_argument("MatrixInline dimensions must agree for subtraction");
        }
        for (size_t i = 0; i < _m_size; ++i) {
            _data[i] -= other.at(i);
        }
        std::cout << "MatrixInline -= operator called" << std::endl;

        return *this;
    } */ 

    inline MatrixInline operator+(const Matrix<T>& other) const {
        if (_rows != other.get_rows() || _cols != other.get_cols()) {
            throw std::invalid_argument("MatrixInline dimensions must agree for addition");
        }
        MatrixInline result(_rows, _cols);


        const T* other_data = other.get_data();  // Get the raw pointer to the data from the other matrix

        for (size_t i = 0; i < _m_size; ++i) {
            result._data[i] = _data[i] + other_data[i];
        }
        std::transform(
            _data.get(), _data.get() + _m_size,    // Range 1
            other.get_data(),                      // Range 2
            _data.get(),                           // Output
            [](const T& a, const T& b) { return a - b; }
        );

        return result;
    }

    inline MatrixInline operator-(const Matrix<T>& other) const {
        if (_rows != other.get_rows() || _cols != other.get_cols()) {
            throw std::invalid_argument("MatrixInline dimensions must agree for subtraction");
        }

        const T* other_data = other.get_data();  // Get the raw pointer to the data from the other matrix

        MatrixInline result(_rows, _cols);
        for (size_t i = 0; i < _m_size; ++i) {
            result._data[i] = _data[i] - other_data[i];
        }
        return result;
    }


    // Destructor
    inline ~MatrixInline() {
        // No explicit cleanup needed as std::unique_ptr handles memory management
    }

    // Access element (row-major)
    inline T& at(size_t r, size_t c) override {
        if (r >= _rows || c >= _cols) {
            throw std::out_of_range("MatrixInline::at(): index out of range");
        }
        return _data[r * _cols + c];
    }

    inline const T& at(size_t r, size_t c) const override {
        if (r >= _rows || c >= _cols) {
            throw std::out_of_range("MatrixInline::at() const: index out of range");
        }
        return _data[r * _cols + c];
    }

    // Accessors
    inline size_t get_rows() const { return _rows; }
    inline size_t get_cols() const { return _cols; }
    inline size_t get_size() const { return _m_size; }


private:
    size_t _rows, _cols, _m_size;
    std::unique_ptr<T[]> _data; // length = rows*cols
};


template<typename T>
inline MatrixInline<T>& MatrixInline<T>::operator+=(const Matrix<T>& other) {
    if (_rows != other.get_rows() || _cols != other.get_cols()) {
        throw std::invalid_argument("MatrixInline dimensions must agree for addition");
    }
    const T* other_data = other.get_data();  // Get the raw pointer to the data from the other matrix
    for (size_t i = 0; i < _m_size; ++i) {
        _data[i] += other_data[i];
    }

    // std::cout << "MatrixInline += operator called" << std::endl;
    return *this;
}

