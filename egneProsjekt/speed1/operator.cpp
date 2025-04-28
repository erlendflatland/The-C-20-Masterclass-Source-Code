#include <iostream>
#include "Matrix.h"

void operators() {  

    Matrix<int> mat1(3, 3, 1);
    Matrix<int> mat2(3, 4);

    /*
    try {
        Matrix<int> mat3 = mat1 + mat2;  // This should throw
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }*/ 

    // skal virke
    Matrix<int> mat4(3, 3, 2);
    std::initializer_list<int> init = {1, 2, 3};
    Matrix<int> mat5({init, init, init});

    // operator +=
    mat5 += mat4;

    std::cout<<"copy ctor? : " ;
    const auto& mat6Ref(mat5);      // no copy ctor, just binds reference


    std::cout<<"copy ctor? : " ;
    const auto mat6Const(mat5);       // copy ctor?

    std::cout<<"copy ctor? : " ;
    Matrix<int> mat6(mat5);         // direct initialization ⇒ calls copy ctor

    std::cout<<"copy ctor?  : " ;
    const auto mat7 = mat5;        // copy initialization ⇒ calls copy ctor

    Matrix<int> m8;
    // m8 = mat1;

    std::cout<<"move ctor? : " ;
    Matrix<int> mMoveConst(std::move(mat5));


    // move assignment 1 : 
    Matrix<int> mMoveAss;
    std::cout<<"move assignment? : " ;
    mMoveAss = Matrix<int>(3, 3, 9);

    // not move assignment, this is move constructor : 
    std::cout<<"move ctor? : ";
    auto mMoveAss2 = std::move(mMoveAss);



    // use && to make it an rvalue reference
    std::cout<<"move assignment? : ";
    // will not be move assignment, but move constructor :
    // auto mMoveAss3 = std::move(mMoveAss2);

    Matrix<int> src(3, 3, 9);     // src is an l-value
    Matrix<int> dst; 
    dst = std::move(src);
}