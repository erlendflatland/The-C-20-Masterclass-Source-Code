

class Matrix;

class MatrixRotation : public Matrix
{
public:
    using Matrix::Matrix; // Inherit constructors from Matrix
    ~MatrixRotation();

    void rotateMatrix(Matrix& matrix, float angle);


}