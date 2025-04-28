#include <iostream>
// #include "Matrix.h" inkldurt i operators.cpp allerede
#include "operators.cpp"

#include <chrono>  // For timing

#include "MatrixInline.h"
#include "arv1.cpp"
#include "iterators.cpp"
#include "vectors.cpp"

#include "MatrixRotation.h"

int main(){
    

    // operators(); // test the operators




    //mat1+=mat1;
    // arv1();

    // iterators(); // test the iterators
   
    // ulik tid ved bruk av std::vector og std::unique_ptr : 
    // vectors(100000);
    // vectors(1000000*10);

    // TODO: expand m feks roter og skalering
    MatrixRotation<int> m1(3, 3, 1); // impt rotasjon etc;

    /* Step 10: Robot-Related Task – Kinematic Transformations
    Homogeneous Transformation Matrices:

    Implement methods for working with 4x4 transformation matrices for robotics applications (translation, rotation, scaling, etc.).

    Task:

    Implement a function that multiplies a 3D point with a 4x4 homogeneous transformation matrix. Test with simple translation and rotation.

    Step 11: Computational Efficiency – Loop Performance
    Reduce Complexity:

    Optimize matrix multiplication by using optimized algorithms, such as Strassen's algorithm, or by using block multiplication to reduce memory cache misses.

    Task:

    Write an optimized version of matrix multiplication (e.g., Strassen's algorithm) and compare it to a brute force approach in terms of performance.

    Step 12: Advanced Robot Simulation – Jacobian Matrix
    Jacobian Matrix for Kinematics:

    Implement the Jacobian matrix for a robot arm or manipulator. This matrix is essential for solving forward and inverse kinematics.

    Task:

    Implement the Jacobian matrix for a 2D robotic arm. Create a test case with an arm configuration and use the Jacobian to calculate the end-effector velocity.

    Step 13: Error Handling and Validation
    Error Handling:

    Ensure that the matrix operations (addition, multiplication) handle invalid operations gracefully, such as mismatched dimensions.

    Task:

    Write tests that check for errors when attempting to add two matrices of incompatible sizes. Ensure appropriate exceptions are thrown.

    Step 14: Robot Control – Motion Planning
    Trajectory Planning (Polynomial Interpolation):

    Use matrices to represent trajectories and implement polynomial interpolation to plan a path for a robot.

    Task:

    Implement polynomial interpolation for trajectory planning and test it with a sequence of waypoints.

    Step 15: Matrix Template for Other Data Types
    Template Specialization:

    Specialize the Matrix class template for certain data types, such as Matrix<int> for integer matrices or Matrix<float> for high precision matrices.

    Task:

    Implement specialized methods for certain data types, e.g., a matrix with integer values may have different optimization techniques compared to matrices with floating-point numbers.

    Step 16: Final Benchmarking & Optimization
    Benchmarking:

    Use std::chrono to benchmark the different operations implemented: matrix creation, multiplication, addition, and specialized operations for robotics.

    Task:

    Create a performance test that compares matrix operations on large matrices and analyze the results in terms of time taken. */



    /* andre ting  : 
        Three-way operator, 
        function like entities 
        Custom iterators for your containers 
        add c++ 20 ting som concepts
    */

    return 0;
}