#include "matrix.hpp"

bool Matrix::operator ==(const Matrix& other) const {
   if (this == &other) return true;
   if (rows_ != other.rows_ || cols_ != other.cols_) return false;
   for (size_t i = 0; i < rows_ * cols_; ++i) {
       if (p_data_[i] != other.p_data_[i]) return false;
   }
   return true;
}

bool Matrix::operator !=(const Matrix& other) const {
    return !(*this == other);
}
    
Matrix& Matrix::operator *=(int num) {
    for (size_t i = 0; i < rows_ * cols_; ++i) {
        p_data_[i] *= num;
    }
    return *this;
}

