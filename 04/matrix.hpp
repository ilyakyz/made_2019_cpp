#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>
#include <stdexcept>

class Matrix {
    class Row;
    
public:
    Matrix(size_t rows, size_t cols): rows_(rows), cols_(cols), p_data_(new int[rows * cols] {}) {}
    
    ~Matrix() {
        delete[] p_data_;
    }
    
    bool operator ==(const Matrix& other) const;
    
    bool operator !=(const Matrix& other) const;
    
    Matrix& operator *=(int num);
    
    size_t get_rows() const {
        return rows_;
    }
    
    size_t get_columns() const {
        return cols_;
    }
    
    Row operator [](size_t row) {
        if (row >= rows_) throw std::out_of_range("");
        return {cols_, p_data_ + cols_ * row};
    }
    
    const Row operator [](size_t row) const {
        if (row >= rows_) throw std::out_of_range("");
        return {cols_, p_data_ + cols_ * row};
    }
    
private:
    class Row {
    public:
        Row(size_t cols, int* p_data): cols_(cols), p_data_(p_data) {}
        
        int& operator [](size_t col) {
            if (col >= cols_) throw std::out_of_range("");
            return p_data_[col];
        }
        const int& operator [](size_t col) const {
            if (col >= cols_) throw std::out_of_range("");
            return p_data_[col];
        }
    private:
        size_t cols_;
        int* p_data_;
    };
    
    size_t rows_;
    size_t cols_;
    int* p_data_;
};

#endif /* matrix_hpp */
