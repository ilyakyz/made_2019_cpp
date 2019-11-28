#include "big_int.hpp"
#include <iomanip>

int abs_cmp(const BigInt& first, const BigInt& second) {
    if (first.size != second.size) {
        return first.size < second.size? -1 : 1;
    }
    for (int64_t i = static_cast<int64_t>(first.size) - 1; i >= 0; --i) {
        if (first.digits[i] != second.digits[i])
            return first.digits[i] < second.digits[i] ? -1 : 1;
    }
    return 0;
}

BigInt abs_add(const BigInt& first, const BigInt& second) {
    BigInt result;
    result.size = std::max(first.size, second.size);
    result.digits = new int64_t[result.size];
    bool overflow = false;
    for (size_t i = 0; i < result.size; ++i) {
        int64_t sum = overflow;
        if (i < first.size) {
            sum += first.digits[i];
        }
        if (i < second.size) {
            sum += second.digits[i];
        }
        result.digits[i] = sum % DIGIT_SIZE;
        
        overflow = sum >= DIGIT_SIZE;
    }
    
    if (overflow) {
        int64_t* new_digits = new int64_t[result.size];
        std::copy(result.digits, result.digits + result.size, new_digits);
        new_digits[result.size] = 1;
        delete[] result.digits;
        result.size += 1;
        result.digits = new_digits;
    }
    return result;
}

BigInt abs_sub(const BigInt& first, const BigInt& second) {
    BigInt result;
    result.size = first.size;
    result.digits = new int64_t[result.size];
    bool overflow = false;
    for (size_t i = 0; i < result.size; ++i) {
        int64_t sum = first.digits[i] - overflow;
        if (i < second.size) {
            sum -= second.digits[i];
        }
        result.digits[i] = (sum + DIGIT_SIZE) % DIGIT_SIZE;
        
        overflow = sum < 0;
    }
    
    size_t trim_size = 0;
    while (trim_size + 1 < result.size && result.digits[result.size - trim_size - 1] == 0) {
        ++trim_size;
    }
    if (trim_size != 0) {
        result.size -= trim_size;
        int64_t* new_digits = new int64_t[result.size];
        std::copy(result.digits, result.digits + result.size, new_digits);
        delete[] result.digits;
        result.digits = new_digits;
    }
    return result;
}

BigInt add(const BigInt& first, bool count_first_as_positive,
           const BigInt& second, bool count_second_as_positive)
{
    if (count_first_as_positive == count_second_as_positive) {
        BigInt result = abs_add(first, second);
        result.positive = count_first_as_positive;
        return result;
    }
    int cmp = abs_cmp(first, second);
    if (cmp == 0) {
        return BigInt(0);
    } else if (cmp == -1) {
        BigInt result = abs_sub(second, first);
        result.positive = count_second_as_positive;
        return result;
    } else {
        BigInt result = abs_sub(first, second);
        result.positive = count_first_as_positive;
        return result;
    }
}

BigInt operator + (const BigInt& first, const BigInt& second) {
    return add(first, first.positive, second, second.positive);
}

BigInt operator - (const BigInt& first, const BigInt& second) {
    return add(first, first.positive, second, !second.positive);
}

BigInt operator - (BigInt&& big_int) {
    BigInt result(std::move(big_int));
    result.positive = result == 0 || !result.positive;
    return result;
}

BigInt operator - (const BigInt& big_int) {
    BigInt result(big_int);
    result.positive = result == 0 || !result.positive;
    return result;
}

bool operator < (const BigInt& first, const BigInt& second) {
    if (first.positive != second.positive) {
        return second.positive;
    } else if (first.positive) {
        return abs_cmp(first, second) == -1;
    }
    return abs_cmp(first, second) == 1;
}

bool operator > (const BigInt& first, const BigInt& second) {
    return second < first;
}

bool operator <= (const BigInt& first, const BigInt& second) {
    return !(first > second);
}

bool operator >= (const BigInt& first, const BigInt& second) {
    return !(first < second);
}

bool operator == (const BigInt& first, const BigInt& second) {
    if (first.positive != second.positive) return false;
    return abs_cmp(first, second) == 0;
}

bool operator != (const BigInt& first, const BigInt& second) {
    return !(first == second);
}

std::ostream& operator << (std::ostream& out, const BigInt& big_int) {
    std::ios state(NULL);
    state.copyfmt(out);

    if (!big_int.positive)
        out << '-';
    out << big_int.digits[big_int.size - 1];

    for (int64_t i = static_cast<int64_t>(big_int.size) - 2; i >= 0; --i) {
        out << std::setw(log10(DIGIT_SIZE)) << std::setfill('0') << big_int.digits[i];
    }
    out.copyfmt(state);
    return out;
}
