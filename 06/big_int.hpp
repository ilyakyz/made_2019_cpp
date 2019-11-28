#ifndef big_int_hpp
#define big_int_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>


static_assert(DIGIT_SIZE <= 1e18, "digit size too big");

class BigInt {
public:
    BigInt(int x):
        positive(x >= 0),
        size(x? ceil(log(abs(x) + 1) / log(DIGIT_SIZE)): 1),
        digits(new int64_t[size])
    {
        x = abs(x);
        for (size_t i = 0; i < size; ++i) {
            digits[i] = x % DIGIT_SIZE;
            x /= DIGIT_SIZE;
        }
    }
    
    BigInt(BigInt&& big_int):
        positive(big_int.positive),
        size(big_int.size),
        digits(big_int.digits)
    {
        big_int.digits = nullptr;
    }
    
    BigInt(const BigInt& big_int):
        positive(big_int.positive),
        size(big_int.size),
        digits(new int64_t[size])
    {
        std::copy(big_int.digits, big_int.digits + size, digits);
    }
    

    BigInt& operator=(const BigInt& big_int) {
        if (big_int == *this)
            return *this;
        int64_t* new_digits = new int64_t[big_int.size];
        delete[] digits;
        digits = new_digits;
        std::copy(big_int.digits, big_int.digits + big_int.size, digits);
        positive = big_int.positive;
        size = big_int.size;
        return *this;
    };

    BigInt& operator=(BigInt&& big_int) {
        digits = big_int.digits;
        positive = big_int.positive;
        size = big_int.size;
        big_int.digits = nullptr;
        return *this;
    }
    
    ~BigInt() {
        delete[] digits;
    }
    
private:
    BigInt() {
    }
    
    bool positive;
    size_t size;
    int64_t* digits;
    
    friend BigInt add(const BigInt& first, bool count_first_as_positive,
                      const BigInt& second, bool count_second_as_positive);
    friend BigInt operator + (const BigInt& first, const BigInt& second);
    friend BigInt operator - (const BigInt& first, const BigInt& second);
    friend BigInt operator - (BigInt&& big_int);
    friend BigInt operator - (const BigInt& big_int);
    friend bool operator < (const BigInt& first, const BigInt& second);
    friend int abs_cmp(const BigInt& first, const BigInt& second);
    friend BigInt abs_add(const BigInt& first, const BigInt& second);
    friend BigInt abs_sub(const BigInt& first, const BigInt& second);
    friend bool operator == (const BigInt& first, const BigInt& second);
    friend std::ostream& operator << (std::ostream& out, const BigInt& bigint);
};

BigInt operator + (const BigInt& first, const BigInt& second);
BigInt operator - (const BigInt& first, const BigInt& second);
BigInt operator - (BigInt&& big_int);
BigInt operator - (const BigInt& big_int);
bool operator < (const BigInt& first, const BigInt& second);
bool operator > (const BigInt& first, const BigInt& second);
bool operator <= (const BigInt& first, const BigInt& second);
bool operator >= (const BigInt& first, const BigInt& second);
bool operator == (const BigInt& first, const BigInt& second);
bool operator != (const BigInt& first, const BigInt& second);
std::ostream& operator << (std::ostream& out, const BigInt& bigint);

#endif /* big_int_hpp */
