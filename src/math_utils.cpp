#include "dsalib/math_utils.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <stdexcept>

namespace dsalib {

long long MathUtils::gcd(long long a, long long b) {
    a = std::llabs(a);
    b = std::llabs(b);
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long MathUtils::lcm(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return std::llabs(a / gcd(a, b) * b);
}

long long MathUtils::mod_pow(long long base, long long exponent, long long mod) {
    if (mod <= 0) {
        throw std::invalid_argument("mod must be positive");
    }
    if (exponent < 0) {
        throw std::invalid_argument("negative exponent is not supported");
    }
    base %= mod;
    if (base < 0) {
        base += mod;
    }
    long long result = 1 % mod;
    while (exponent > 0) {
        if (exponent & 1LL) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1LL;
    }
    return result;
}

std::vector<int> MathUtils::sieve(int limit) {
    if (limit < 2) {
        return std::vector<int>();
    }
    std::vector<bool> composite(static_cast<std::size_t>(limit + 1), false);
    for (long long p = 2; p * p <= limit; ++p) {
        if (!composite[static_cast<std::size_t>(p)]) {
            for (long long x = p * p; x <= limit; x += p) {
                composite[static_cast<std::size_t>(x)] = true;
            }
        }
    }
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (!composite[static_cast<std::size_t>(i)]) {
            primes.push_back(i);
        }
    }
    return primes;
}

std::vector<std::pair<long long, int> > MathUtils::prime_factorization(
    long long value) {
    std::vector<std::pair<long long, int> > factors;
    if (value == 0) {
        factors.push_back(std::make_pair(0, 1));
        return factors;
    }
    if (value < 0) {
        factors.push_back(std::make_pair(-1, 1));
        value = -value;
    }
    for (long long p = 2; p * p <= value; p += (p == 2 ? 1 : 2)) {
        if (value % p == 0) {
            int count = 0;
            while (value % p == 0) {
                value /= p;
                ++count;
            }
            factors.push_back(std::make_pair(p, count));
        }
    }
    if (value > 1) {
        factors.push_back(std::make_pair(value, 1));
    }
    return factors;
}

MathUtils::Matrix MathUtils::multiply(const Matrix& a, const Matrix& b) {
    if (a.empty() || b.empty() || a[0].empty() || b[0].empty()) {
        return Matrix();
    }
    std::size_t rows = a.size();
    std::size_t inner = a[0].size();
    std::size_t cols = b[0].size();
    if (b.size() != inner) {
        throw std::invalid_argument("matrix dimensions do not match");
    }
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i].size() != inner) {
            throw std::invalid_argument("left matrix is ragged");
        }
    }
    for (std::size_t i = 0; i < b.size(); ++i) {
        if (b[i].size() != cols) {
            throw std::invalid_argument("right matrix is ragged");
        }
    }
    Matrix result(rows, std::vector<long long>(cols, 0));
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t k = 0; k < inner; ++k) {
            if (a[i][k] == 0) {
                continue;
            }
            for (std::size_t j = 0; j < cols; ++j) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

MathUtils::Matrix MathUtils::identity(std::size_t n) {
    Matrix result(n, std::vector<long long>(n, 0));
    for (std::size_t i = 0; i < n; ++i) {
        result[i][i] = 1;
    }
    return result;
}

MathUtils::Matrix MathUtils::matrix_power(Matrix base, long long exponent) {
    if (exponent < 0) {
        throw std::invalid_argument("negative matrix exponent");
    }
    if (base.empty() || base.size() != base[0].size()) {
        throw std::invalid_argument("matrix_power requires square matrix");
    }
    for (std::size_t i = 0; i < base.size(); ++i) {
        if (base[i].size() != base.size()) {
            throw std::invalid_argument("matrix_power requires square matrix");
        }
    }
    Matrix result = identity(base.size());
    while (exponent > 0) {
        if (exponent & 1LL) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        exponent >>= 1LL;
    }
    return result;
}

long long MathUtils::fibonacci(long long n) {
    if (n < 0) {
        throw std::invalid_argument("negative fibonacci index");
    }
    if (n == 0) {
        return 0;
    }
    Matrix transform(2, std::vector<long long>(2, 0));
    transform[0][0] = 1;
    transform[0][1] = 1;
    transform[1][0] = 1;
    transform[1][1] = 0;
    Matrix powered = matrix_power(transform, n - 1);
    return powered[0][0];
}

}  // namespace dsalib
