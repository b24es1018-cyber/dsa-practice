class Solution {
public:
    const long long MOD = 1000000007;

    long long power(long long x, long long n) {
        if (n == 0) return 1;

        long long half = power(x, n / 2);

        if (n % 2 == 0)
            return (half * half) % MOD;
        else
            return (((half * half) % MOD) * x) % MOD;
    }

    int countGoodNumbers(long long n) {
        long long evenPositions = (n + 1) / 2;
        long long oddPositions = n / 2;

        long long ans = (power(5, evenPositions) * power(4, oddPositions)) % MOD;

        return ans;
    }
};