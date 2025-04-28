template<typename T>
class Matrix; // Forward declaration of Matrix

template<typename T>
class MatrixRotation : public Matrix<T> 
{
public:
    using Matrix<T>::Matrix; // Inherit constructors from Matrix<T>
    ~MatrixRotation() = default;

    // Add any additional methods or overrides here
};
