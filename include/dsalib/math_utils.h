#ifndef DSALIB_MATH_UTILS_H
#define DSALIB_MATH_UTILS_H

#include <utility>
#include <vector>

namespace dsalib {

class MathUtils {
public:
    typedef std::vector<std::vector<long long> > Matrix;

    static long long gcd(long long a, long long b);
    static long long lcm(long long a, long long b);
    static long long mod_pow(long long base, long long exponent, long long mod);
    static std::vector<int> sieve(int limit);
    static std::vector<std::pair<long long, int> > prime_factorization(
        long long value);
    static Matrix multiply(const Matrix& a, const Matrix& b);
    static Matrix identity(std::size_t n);
    static Matrix matrix_power(Matrix base, long long exponent);
    static long long fibonacci(long long n);
};

}  // namespace dsalib

#endif
