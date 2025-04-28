
vectors() {
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

}