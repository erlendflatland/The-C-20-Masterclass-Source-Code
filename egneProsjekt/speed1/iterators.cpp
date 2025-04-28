

#include <iostream>

void iterators() {

    std::cout << "Iterators" << std::endl;
    Matrix<int> m(3,3,1);
    
    

    std::cout << m;

    // std::cout << m++;
    ++m;
    std::cout << m;

    //std::cout <<++m;
    m++;
    std::cout << m;

    
}