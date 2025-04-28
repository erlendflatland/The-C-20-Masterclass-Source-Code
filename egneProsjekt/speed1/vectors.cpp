

/*
raslest for vector<unique_ptr<MatrixInline<int>>>
*/

void matrixLoopOperations2(const auto& Matrix) {
    // Loop through the matrix and print each element
    for (size_t i = 0; i < Matrix.get_rows(); ++i) {
        for (size_t j = 0; j < Matrix.get_cols(); ++j) {
            Matrix.at(i, j) ;
        }
    }
}
/*
Time taken for MatrixInline: vector 100 ms
Matrix operations : 102 ms
 ================= 
Time taken for Matrix: vector 80 ms
Matrix operations : 98 ms

 ================= 
Time taken for Matrix (raw pointer array **): 78 ms
Matrix operations : 98 ms
 ================= 
Time taken for Matrix: vector of pointers :105 ms
Matrix operations : 102 ms
 ================= 
Time taken for Matrix: smartpointer vector 171 ms
Matrix operations : 12 ms
 ================= 
Time taken for MatrixInline vector of smart-pointers using generate: 186 ms
Matrix operations : 12 ms
 ================= 
Time taken for MatrixInline vector of smart-pointers: 212 ms
Matrix operations : 23 ms
*/

void matrixLoopOperations( auto& Matrix) {
    Matrix -= Matrix;
}


/*
Time taken for MatrixInline: vector 149 ms
Matrix operations : 199 ms
 ================= 
Time taken for Matrix: vector 92 ms
Matrix operations : 185 ms
 ================= 
Time taken for MatrixInline (smart pointer array): 27 ms
Matrix operations : 0 ms
 ================= 
Time taken for Matrix (raw pointer array **): 85 ms
Matrix operations : 181 ms
 ================= 
Time taken for Matrix: vector of pointers :156 ms
Matrix operations : 199 ms
 ================= 
Time taken for Matrix: smartpointer vector 226 ms
Matrix operations : 208 ms
 ================= 
Time taken for MatrixInline vector of smart-pointers using generate: 247 ms
Matrix operations : 211 ms
 ================= 
Time taken for MatrixInline vector of smart-pointers: 282 ms
Matrix operations : 226 ms
*/


void matrixLoopOperations3(auto& Matrix) {
    // Loop through the matrix and print each element
    ++Matrix;
}

/*
raslest for vector<<MatrixInline<int>>> : 

Time taken for MatrixInline: vector 109 ms
Matrix operations : 6 ms
 ================= 
Time taken for Matrix: vector 86 ms
Matrix operations : 100 ms
Time taken for MatrixInline vector of smart-pointers: 213 ms
Matrix operations : 14 ms

men kun hvis :
    ikke overrider operator ++ i MatrixInline
    
    /* inline void operator++() override { // Prefix
        for (size_t i = 0; i < _m_size; ++i)
            _data[i] += 1;
        //return *this;
    } 
*/

void vectors(int numElements = 100000) {
    // TODO: tilat bruke av vektorer som input
    // få rad-vector og kolonne-vektor ut
    // set rad-vector og kolonne-vektor
    // sjekk forskjell på std::vector og std::span og std::copy  og for-loop
    std::initializer_list<int> init = {1, 2, 3};
    MatrixInline<int> m1({init, init, init});

    // MatrixInline<int> m1({init, init, init});

    const auto& v1 = m1.get_row(1); // get row vector
    std::cout << "v1 : " << v1.size() << std::endl;
    for (const auto& val : v1) {
        std::cout << val << " ";
    }
    
    std::cout << "numElements : " << numElements << std::endl;
    std::cout << " ================= " << std::endl;
    using namespace std::chrono;
    {


        // Start measuring time for MatrixInline
        auto start = high_resolution_clock::now();

        std::vector<MatrixInline<int>> vMatIn;
        vMatIn.reserve(numElements);
        for (int i = 0; i < numElements; ++i) {
            vMatIn.emplace_back(3, 3, 3);
        }

        // Stop measuring time for MatrixInline
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Time taken for MatrixInline: vector " << duration.count() << " ms\n";
        
        
        start = high_resolution_clock::now();
    
        for ( auto& mat : vMatIn) {
            matrixLoopOperations(mat);
        } 
    
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        std::cout << "Matrix operations : " << duration.count() << " ms\n";
        
    }

    std::cout << " ================= " << std::endl;
    {
        // Start measuring time for Matrix
        auto start = high_resolution_clock::now();

        std::vector<Matrix<int>> vMat;
        vMat.reserve(numElements);
        for (int i = 0; i < numElements; ++i) {
            vMat.emplace_back(3, 3, 3);
        }

        // Stop measuring time for Matrix
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Time taken for Matrix: vector " << duration.count() << " ms\n";



            
        start = high_resolution_clock::now();
    
        for ( auto& mat : vMat) {
            matrixLoopOperations(mat);
        } 
    
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        std::cout << "Matrix operations : " << duration.count() << " ms\n";
    }
    std::cout << " ================= " << std::endl;


    /* invokes move assigment : 
    for (int i = 0; i < numElements; ++i) {
        vMat[i] = Matrix(3, 3, 3);
        vMat.at(i) = Matrix(3, 3, 3);

    } */ 




    {
        auto start = high_resolution_clock::now();

        
        // Create an array of unique_ptrs to MatrixInline objects
        // std::unique_ptr<std::unique_ptr<MatrixInline<int>>[]> vBase = std::make_unique<std::unique_ptr<MatrixInline<int>>[]>(numElements);
        std::unique_ptr<MatrixInline<int>[]> vBase = std::make_unique<MatrixInline<int>[]>(numElements);


        // invokes move assigment :
        // Initialize the array of unique_ptrs
        //for (int i = 0; i < numElements; ++i) {
        //    vBase[i] = MatrixInline<int>(3, 3, 3);  // Create each MatrixInline<int> object in place
        // }

        /* will be 0x0 matrix since nullptrs
        :
        
        std::cout << vBase[0] << std::endl;
        std::cout << vBase[0].get_cols() << std::endl;

        */


        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Time taken for MatrixInline (smart pointer array): " << duration.count() << " ms\n";
    


        start = high_resolution_clock::now();
    

        /*
        for (int i = 0; i < numElements; ++i) {
            matrixLoopOperations(vBase[i]);  // Dereference each pointer and pass to the function
        } */ 
    
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        std::cout << "Matrix operations : " << duration.count() << " ms\n";


    }

    std::cout << " ================= " << std::endl;

    {
        // Create an array of raw pointers to MatrixInline objects
        auto start = high_resolution_clock::now();
        Matrix<int>** vBase = new Matrix<int>*[numElements];

        // Initialize the array of raw pointers
        for (int i = 0; i < numElements; ++i) {
            vBase[i] = new Matrix<int>(3, 3, 3);  // Allocate a new MatrixInline<int> object for each element
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Time taken for Matrix (raw pointer array **): " << duration.count() << " ms\n";

        start = high_resolution_clock::now();
    
        for (int i = 0; i < numElements; ++i) {
            matrixLoopOperations(*vBase[i]);  // Dereference each pointer and pass to the function
        }
    
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        std::cout << "Matrix operations : " << duration.count() << " ms\n";
    

        // Cleanup the memory
        for (int i = 0; i < numElements; ++i) {
            delete vBase[i];  // Deallocate each MatrixInline object
        }
        delete[] vBase;  // Deallocate the array of pointers
    }
    std::cout << " ================= " << std::endl;



    {
        
        auto start = high_resolution_clock::now();


        // Create a vector of raw pointers to MatrixInline objects
        std::vector<MatrixInline<int>*> vBase;
        vBase.reserve(numElements);

        // Initialize the vector with new MatrixInline objects
        for (int i = 0; i < numElements; ++i) {
            vBase.push_back(new MatrixInline<int>(3, 3, 3));  // Using raw pointers
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Time taken for Matrix: vector of pointers :" << duration.count() << " ms\n";

        // Perform operations on the elements in the vector
        start = high_resolution_clock::now();

        for ( auto& mat : vBase) {
            matrixLoopOperations(*mat);  // Accessing through raw pointers
        }

        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        std::cout << "Matrix operations : " << duration.count()<< " ms\n";

        // Cleanup: manually delete the dynamically allocated MatrixInline objects
        for (auto mat : vBase) {
            delete mat;
        }
    }
    std::cout << " ================= " << std::endl;

    {
        auto start = high_resolution_clock::now();
        std::vector<std::unique_ptr<Matrix<int>>> vBase;
        vBase.reserve(numElements);
    
        for (int i = 0; i < numElements; ++i) {
            vBase.emplace_back(std::make_unique<MatrixInline<int>>(3, 3, 3));
        }
    
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Time taken for Matrix: smartpointer vector " << duration.count() << " ms\n";
    
            
        start = high_resolution_clock::now();
    
        for ( auto& mat : vBase) {
            matrixLoopOperations(*mat);
        } 
    
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        std::cout << "Matrix operations : " << duration.count() << " ms\n";
    
    }


    std::cout << " ================= " << std::endl;


    {
        auto start = high_resolution_clock::now();

        std::vector<std::unique_ptr<Matrix<int>>> vBase(numElements);

        std::generate(vBase.begin(), vBase.end(), []() {
            return std::make_unique<MatrixInline<int>>(3, 3, 3);
        });

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Time taken for MatrixInline vector of smart-pointers using generate: " << duration.count() << " ms\n";
        start = high_resolution_clock::now();
    
        for ( auto& mat : vBase) {
            matrixLoopOperations(*mat);
        } 
    
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        std::cout << "Matrix operations : " << duration.count() << " ms\n";
    }
    std::cout << " ================= " << std::endl;

    {


        auto start = high_resolution_clock::now();
        std::vector<std::unique_ptr<Matrix<int>>> vBase;
        //vBase.reserve(numElements);
    
        for (int i = 0; i < numElements; ++i) {
            vBase.emplace_back(std::make_unique<MatrixInline<int>>(3, 3, 3));
        }
    
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Time taken for MatrixInline vector of smart-pointers: " << duration.count() << " ms\n";
    
        start = high_resolution_clock::now();
    
        for ( auto& mat : vBase) {
            matrixLoopOperations(*mat);
        } 
    
        end = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(end - start);
        std::cout << "Matrix operations : " << duration.count() << " ms\n";
    
    }

}





// 1 emplace_back > push_back > at() v  []

/* 2 

const T* other_data = other.get_data();  // Get the raw pointer to the data from the other matrix

for (size_t i = 0; i < _m_size; ++i) {
    result._data[i] = _data[i] + other_data[i];
}

/// faster
std::transform(
    _data.get(), _data.get() + _m_size,    // Range 1
    other.get_data(),                      // Range 2
    _data.get(),                           // Output
    [](const T& a, const T& b) { return a - b; }
);

*/


/*

    ms base : 80


    ms derived : 
       94 : _rows(rows), _cols(cols), _m_size(rows * cols), _data(std::make_unique<T[]>(rows * cols))  {
       140 //  : _rows(rows), _cols(cols), _m_size(rows * cols), _data(std::make_unique<T[]>(rows * cols)) , Matrix<T>(rows, cols, value) {
       
*/

/*
Time taken for MatrixInline: 97 ms
Time taken for Matrix: 75 ms
Time taken for Matrix: 177 ms
Time taken for MatrixInline (smart pointer array): 190 ms
Time taken for Matrix (raw pointer array): 87 ms
*/