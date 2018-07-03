#include <cstdlib>
#include <iostream>
#include <ctime>

#include "uint1024.h"

uint64 rand64() {
    uint64 t = 0ull;
    for (int i = 0; i < 10; i ++) {
        t = t << 5 ^ rand();
    }
    return t;
}

uint1024 pow_mod(uint1024 x, const uint1024 & m, const uint1024 & n) {
    uint1024 res = 1ull;
    int mLen = m.getLength();
    x %= n;
    for (int i = 0; i < mLen; i ++) {
        if (m.getBit(i)) {
            res = res * x % n;
        }
        x = x * x % n;
    }
    return res;
}

const int MRR = 50;
uint64 xList[MRR];
bool runMillerRabin(uint1024 n) {
    if (n < 5) {
        return n == 2 || n == 3;
    }
    uint1024 m = n - 1;
    uint k = 0;
    while (m.getBit(0) == 0u) {
        k ++;
        m >>= 1;
    }
    for (int r = 0; r < MRR; r ++) {
        uint1024 x = xList[r];
        x = x % (n - 2) + 2;
        uint1024 xLast = pow_mod(x, m, n);
        if (xLast == 1) {
            continue;
        }
        for (uint i = 1; i <= k; i ++) {
            x = xLast * xLast % n;
            if (x == 1) {
                if (xLast != n - 1) {
                    return false;
                } else {
                    break;
                }
            }
            xLast = x;
        }
        if (x != 1) {
            return false;
        }
    }
    return true;
}

uint64 mul_mod(uint64 x, uint64 y, uint64 n) {
    uint64 res = 0ull;
    x %= n;
    y %= n;
    while (y) {
        if (y & 1) {
            res += x;
            res -= res >= n ? n : 0;
        }
        x <<= 1;
        x -= x >= n ? n : 0;
        y >>= 1;
    }
    return res;
}

uint64 pow_mod(uint64 x, uint64 m, uint64 n) {
    uint64 res = 1ull;
    x %= n;
    while (m) {
        if (m & 1) {
            res = mul_mod(res, x, n);
        }
        x = mul_mod(x, x, n);
        m >>= 1;
    }
    return res;
}

bool runMillerRabin2(uint64 n) {
    if (n < 5) {
        return n == 2 || n == 3;
    }
    uint64 m = n - 1;
    uint k = 0;
    while ((m & 1) == 0u) {
        k ++;
        m >>= 1;
    }
    for (int r = 0; r < MRR; r ++) {
        uint64 x = xList[r];
        x = x % (n - 2) + 2;
        uint64 xLast = pow_mod(x, m, n);
        if (xLast == 1) {
            continue;
        }
        for (uint i = 1; i <= k; i ++) {
            x = mul_mod(xLast, xLast, n);
            if (x == 1) {
                if (xLast != n - 1) {
                    return false;
                } else {
                    break;
                }
            }
            xLast = x;
        }
        if (x != 1) {
            return false;
        }
    }
    return true;
}

void selfJudge1() {
    int len = 62;
    uint1024 a, b, c;
    while (true) {
        a.random(len);
        b.random(len);
        c.random(len);
        c += 1;
        std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
        uint1024 res1 = pow_mod(a, b, c);
        uint64 res2 = pow_mod(a.toUint64(), b.toUint64(), c.toUint64());
        if (res1 != res2) {
            std::cout << "res1 = " << res1 << ", res2 = " << res2 << std::endl;
            break;
        }
    }
}

void selfJudge2() {
    int len = 62;
    uint1024 n;
    for (int i = 0; i < MRR; i ++) {
        do {
            xList[i] = rand64();
        } while (xList[i] < 10);
    }
    while (true) {
        n.random(len);
        std::cout << "n = " << n << std::endl;
        bool res1 = runMillerRabin(n);
        bool res2 = runMillerRabin2(n.toUint64());
        if (res1 != res2) {
            std::cout << "res1 = " << res1 << ", res2 = " << res2 << std::endl;
            break;
        }
    }
}

void findPrime() {
    int len = 512;
    uint1024 n;
    do {
        n.random(len);
        std::cout << "checking: n = " << n << std::endl;
    } while(! runMillerRabin(n));
    std::cout << "n = " << n << " is a prime number." << std::endl;
}

int main() {
    srand(time(0));
    //selfJudge1();
    //selfJudge2();
    findPrime();
    return 0;
}