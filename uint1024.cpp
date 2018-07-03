#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "uint1024.h"

uint1024::uint1024() {
    * this = 0ull;
}
uint1024::uint1024(uint64 var) {
    * this = var;
}
uint1024::uint1024(const char * varHex) {
    * this = varHex;
}
uint1024::uint1024(const uint1024 & var) {
    * this = var;
}
uint1024::~uint1024() {
}

//赋值运算
uint1024 & uint1024::operator = (uint64 var) {
    memset(digit, 0, sizeof(digit));
    digit[0] = var & 0xffffffff;
    digit[1] = var >> 32;
    return * this;
}
static uint hexCharToInt(char ch) {
    if ('0' <= ch && ch <= '9') {
        return (uint) (ch - '0');
    } else if ('A' <= ch && ch <= 'F') {
        return (uint) (ch - 'A' + 10);
    } else if ('a' <= ch && ch <= 'f') {
        return (uint) (ch - 'a' + 10);
    } else if (ch == '_'){
        return 0x10;
    } else {
        return 0xff;
    }
}
uint1024 & uint1024::operator = (const char * varHex) {
    memset(digit, 0, sizeof(digit));
    int varLen = 0, cnt = 0;
    while (varLen < (UINT1024_DIGIT << 1)) {
        uint t = hexCharToInt(varHex[varLen]);
        if (t == 0xff) {
            break;
        } else {
            varLen ++;
            cnt += t != 0x10;
        }
    }
    operator = (0ull);
    for (int i = 0; i < varLen; i ++) {
        uint t = hexCharToInt(varHex[i]);
        if (t != 0x10) {
            cnt --;
            digit[cnt >> 3] |= t << (cnt << 2);
        }
    }
    return * this;
}
uint1024 & uint1024::operator = (const uint1024 & var) {
    memcpy(digit, var.digit, sizeof(digit));
    return * this;
}

//比较运算
bool uint1024::operator == (uint64 var) const {
    return operator == (uint1024(var));
}
bool uint1024::operator < (uint64 var) const {
    return operator < (uint1024(var));
}
bool uint1024::operator <= (uint64 var) const {
    return operator <= (uint1024(var));
}
bool uint1024::operator != (uint64 var) const {
    return operator != (uint1024(var));
}
bool uint1024::operator > (uint64 var) const {
    return operator > (uint1024(var));
}
bool uint1024::operator >= (uint64 var) const {
    return operator >= (uint1024(var));
}
bool uint1024::operator == (const uint1024 & var) const {
    for (int i = UINT1024_DIGIT - 1; i >= 0; i --) {
        if (digit[i] != var.digit[i]) {
            return false;
        }
    }
    return true;
}
bool uint1024::operator < (const uint1024 & var) const {
    for (int i = UINT1024_DIGIT - 1; i >= 0; i --) {
        if (digit[i] != var.digit[i]) {
            return digit[i] < var.digit[i];
        }
    }
    return false;
}
bool uint1024::operator <= (const uint1024 & var) const {
    for (int i = UINT1024_DIGIT - 1; i >= 0; i --) {
        if (digit[i] != var.digit[i]) {
            return digit[i] < var.digit[i];
        }
    }
    return true;
}
bool uint1024::operator != (const uint1024 & var) const {
    return ! operator == (var);
}

bool uint1024::operator > (const uint1024 & var) const {
    return ! operator <= (var);
}

bool uint1024::operator >= (const uint1024 & var) const {
    return ! operator < (var);
}

//位运算
uint1024 uint1024::operator ~ () const {
    uint1024 res = 0ull;
    for (int i = 0; i < UINT1024_DIGIT; i ++) {
        res.digit[i] = ~ digit[i];
    }
    return res;
}
uint1024 & uint1024::operator <<= (uint var) {
    * this = operator << (var);
    return * this;
}
uint1024 & uint1024::operator >>= (uint var) {
    * this = operator >> (var);
    return * this;
}
uint1024 uint1024::operator << (uint var) const {
    uint offset = var >> 5;
    uint offsetA = var & 31;
    uint offsetB = 32 - offsetA;
    uint onesA = (1ull << offsetA) - 1u;
    uint onesB = (1ull << offsetB) - 1u;
    uint1024 res = 0ull;
    for (int i = UINT1024_DIGIT - 1; i >= 0; i --) {
        if (i - (int) (offset) >= 0) {
            res.digit[i] |= (digit[i - offset] & onesB) << offsetA;
        }
        if (i - (int) (offset) >= 1) {
            res.digit[i] |= digit[i - offset - 1] >> offsetB & onesA;
        }
    }
    return res;
}
uint1024 uint1024::operator >> (uint var) const {
    uint offset = var >> 5;
    uint offsetA = var & 31;
    uint offsetB = 32 - offsetA;
    uint onesA = (1ull << offsetA) - 1u;
    uint onesB = (1ull << offsetB) - 1u;
    uint1024 res = 0ull;
    for (int i = 0; i < UINT1024_DIGIT; i ++) {
        if (i + offset < UINT1024_DIGIT) {
            res.digit[i] |= digit[i + offset] >> offsetA & onesB;
        }
        if (i + offset + 1 < UINT1024_DIGIT) {
            res.digit[i] |= (digit[i + offset + 1] & onesA) << offsetB;
        }
    }
    return res;
}
uint1024 & uint1024::operator |= (uint64 var) {
    return operator |= (uint1024(var));
}
uint1024 & uint1024::operator &= (uint64 var) {
    return operator &= (uint1024(var));
}
uint1024 & uint1024::operator ^= (uint64 var) {
    return operator ^= (uint1024(var));
}
uint1024 & uint1024::operator |= (const uint1024 & var) {
    return * this = operator | (var);
}
uint1024 & uint1024::operator &= (const uint1024 & var) {
    return * this = operator & (var);
}
uint1024 & uint1024::operator ^= (const uint1024 & var) {
    return * this = operator ^ (var);
}
uint1024 uint1024::operator | (uint64 var) const {
    return operator | (uint1024(var));
}
uint1024 uint1024::operator & (uint64 var) const {
    return operator & (uint1024(var));
}
uint1024 uint1024::operator ^ (uint64 var) const {
    return operator ^ (uint1024(var));
}
uint1024 uint1024::operator | (const uint1024 & var) const {
    uint1024 res = 0ull;
    for (int i = 0; i < UINT1024_DIGIT; i ++) {
        res.digit[i] = digit[i] | var.digit[i];
    }
    return res;
}
uint1024 uint1024::operator & (const uint1024 & var) const {
    uint1024 res = 0ull;
    for (int i = 0; i < UINT1024_DIGIT; i ++) {
        res.digit[i] = digit[i] & var.digit[i];
    }
    return res;
}
uint1024 uint1024::operator ^ (const uint1024 & var) const {
    uint1024 res = 0ull;
    for (int i = 0; i < UINT1024_DIGIT; i ++) {
        res.digit[i] = digit[i] ^ var.digit[i];
    }
    return res;
}

//代数运算
uint1024 & uint1024::operator += (uint64 var) {
    return operator += (uint1024(var));
}
uint1024 & uint1024::operator -= (uint64 var) {
    return operator -= (uint1024(var));
}
uint1024 & uint1024::operator *= (uint64 var) {
    return operator *= (uint1024(var));
}
uint1024 & uint1024::operator /= (uint64 var) {
    return operator /= (uint1024(var));
}
uint1024 & uint1024::operator %= (uint64 var) {
    return operator %= (uint1024(var));
}
uint1024 & uint1024::operator += (const uint1024 & var) {
    return * this = operator + (var);
}
uint1024 & uint1024::operator -= (const uint1024 & var) {
    return * this = operator - (var);
}
uint1024 & uint1024::operator *= (const uint1024 & var) {
    return * this = operator * (var);
}
uint1024 & uint1024::operator /= (const uint1024 & var) {
    return * this = operator / (var);
}
uint1024 & uint1024::operator %= (const uint1024 & var) {
    return * this = operator % (var);
}
uint1024 uint1024::operator + (uint64 var) const {
    return operator + (uint1024(var));
}
uint1024 uint1024::operator - (uint64 var) const {
    return operator - (uint1024(var));
}
uint1024 uint1024::operator * (uint64 var) const {
    return operator * (uint1024(var));
}
uint1024 uint1024::operator / (uint64 var) const {
    return operator / (uint1024(var));
}
uint1024 uint1024::operator % (uint64 var) const {
    return operator % (uint1024(var));
}
uint1024 uint1024::operator + (const uint1024 & var) const {
    uint1024 res = 0ull;
    uint overflow_flag = 0;
    for (int i = 0; i < UINT1024_DIGIT; i ++) {
        uint64 tmp = (uint64) (digit[i]) + (uint64) (var.digit[i]) + (uint64) (overflow_flag);
        res.digit[i] = tmp & 0xffffffff;
        overflow_flag = tmp >> 32 & 0x1;
    }
    return res;
}
uint1024 uint1024::operator - (const uint1024 & var) const {
    uint1024 res = 0ull;
    uint borrow_flag = 0;
    for (int i = 0; i < UINT1024_DIGIT; i ++) {
        uint64 tmp = (uint64) (digit[i]) - (uint64) (var.digit[i]) - (uint64) (borrow_flag);
        res.digit[i] = tmp & 0xffffffff;
        borrow_flag = tmp >> 32 & 0x1; 
    }
    return res;
}
uint1024 uint1024::operator * (const uint1024 & var) const {
    uint1024 res = 0ull;
    for (int i = 0; i < UINT1024_DIGIT; i ++) {
        if (digit[i]) {
            uint overflow = 0;
            for (int j = 0; i + j < UINT1024_DIGIT; j ++) {
                //std::cout << "*:   " << "j = " << j << ", var.digit[j] = " << var.digit[j] << std::endl;
                uint64 tmp = (uint64) (digit[i]) * (uint64) (var.digit[j]) + (uint64) (res.digit[i + j]) + (uint64) (overflow);
                res.digit[i + j] = tmp & 0xffffffff;
                overflow = tmp >> 32;
            }
        }
    }
    return res;
}
uint1024 uint1024::operator / (const uint1024 & var) const {
    int offset = (int) (getLength()) - (int) (var.getLength());
    if (offset < 0) {
        return uint1024(0ull);
    }
    uint1024 res_div(0ull);
    uint1024 res_mod(* this);
    uint1024 varOffset = var << (uint) (offset);
    for (; offset >= 0; varOffset >>= 1, offset --) {
        if (res_mod >= varOffset) {
            res_div.setBit(offset, 1u);
            res_mod -= varOffset;
        }
    }
    return res_div;
}
uint1024 uint1024::operator % (const uint1024 & var) const {
    int offset = (int) (getLength()) - (int) (var.getLength());
    if (offset < 0) {
        return * this;
    }
    uint1024 res_mod(* this);
    uint1024 varOffset = var << (uint) (offset);
    for (; offset >= 0; varOffset >>= 1, offset --) {
        if (res_mod >= varOffset) {
            res_mod -= varOffset;
        }
    }
    return res_mod;
}

//其他函数
uint64 uint1024::toUint64() const {
    return (uint64) (digit[1]) << 32 | (uint64) (digit[0]);
}
uint uint1024::getLength() const {
    int i, j;
    for (i = UINT1024_DIGIT - 1; i >= 0 && digit[i] == 0; i --);
    if (i == -1) {
        return 0u;
    }
    for (j = 31; j >= 0 && (digit[i] >> j & 1) == 0; j --);
    return (uint)((i << 5 | j) + 1);
}
void uint1024::setBit(uint i, uint v) {
    if (i < UINT1024_LENGTH) {
        if (v == 0) {
            digit[i >> 5] &= ~ (1u << (i & 31));
        } else {
            digit[i >> 5] |= 1u << (i & 31);
        }
    }
}
uint uint1024::getBit(uint i) const {
    if (i < UINT1024_LENGTH) {
        return digit[i >> 5] >> (i & 31) & 1u;
    }
    return 0u;
}
void uint1024::printHex() const {
    int i;
    for (i = UINT1024_DIGIT - 1; i >= 1 && digit[i] == 0u; i --);
    printf("%x", digit[i]);
    for (i --; i >= 0; i --) {
        printf("_%08x", digit[i]);
    }
}
void uint1024::random(uint length) {
    operator = (0ull);
    length = length >= UINT1024_LENGTH ? UINT1024_LENGTH - 1 : length;
    for (int i = length - 1; i >= 0; i --) {
        digit[i >> 5] |= (uint) (rand() & 1) << (i & 31);
    }
}
std::ostream & operator << (std::ostream & out, const uint1024 & var) {
    int i;
    for (i = UINT1024_DIGIT - 1; i >= 1 && var.digit[i] == 0u; i --);
    out << std::hex << var.digit[i];
    for (i --; i >= 0; i --) {
        out << "_" << std::setfill('0') << std::setw(8) << std::hex << var.digit[i];
    }
    return out;
}