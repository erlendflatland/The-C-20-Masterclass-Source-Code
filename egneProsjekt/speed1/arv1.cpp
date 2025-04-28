
void arv1() {
    // diverse arv ;
    // auto m2 = std::make_unique<MatrixInline<int>>(std::move(m1));
    
    // 
    // TODO : inline, loop unrolling
    MatrixInline<int> m1(3,3,1); // ny versjon av matrix m inline functions,
                     // functions not inlined are inhertited from Matrix class
    // m1+=m1;
    
    Matrix<int> m(3,3,1);

    Matrix<int>* p = new MatrixInline<int>(3,3,1);

    std::cout << "p->get_rows() : " << p->get_rows() << std::endl;
    std::cout << "p->get_cols() : " << p->get_cols() << std::endl;

    std::cout << "m1.get_rows() : " << m1.get_rows() << std::endl;
    std::cout << "m1.get_cols() : " << m1.get_cols() << std::endl;

    p->operator+=(m1);                
    p->operator+=(*p); // : Matrix<T>(rows, cols, value) i constructor av MatrixInline !


    p->operator-=(m1);                
    p->operator-=(*p); // : Matrix<T>(rows, cols, value) i constructor av MatrixInline !
    p->operator-=(m); // : Matrix<T>(rows, cols, value) i constructor av MatrixInline !


    // vil ikke virke siden vi har unique_ptr som medlem : 
    // auto m2 = new MatrixInline<int>(m1);
    // auto m2 = std::make_unique<MatrixInline<int>>(std::move(m1));


    // loop unrolling fx by summing elements in a row or column    


    Matrix<int> mat1(3, 3, 1);
    // std::cout << mat1; // test the << operator;
}