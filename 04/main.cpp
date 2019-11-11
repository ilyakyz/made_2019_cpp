#include <iostream>
#include <stdexcept>

#include "matrix.hpp"

int main(int argc, const char * argv[]) {
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);
    assert(m.get_rows() == 5);
    assert(m.get_columns() == 3);
    
    m[1][2] = 5;
    assert(m[2][1] == 0);
    assert(m[1][2] == 5);

    try {
        m[2][3] = 5;
        assert(false);
    } catch (const std::out_of_range&) {}

    try {
        m[5][1] = 5;
        assert(false);
    } catch (const std::out_of_range&) {}
    
    const Matrix& mc = m;
    assert(mc[2][1] == 0);
    assert(mc[1][2] == 5);
    
    m *= 3;
    assert(m[1][2] == 15);

    assert(m == m);
    Matrix m1(rows, cols);
    assert(m != m1);
    m1[1][2] = 15;
    assert(m == m1);
    std::cout << "OK\n";
}
