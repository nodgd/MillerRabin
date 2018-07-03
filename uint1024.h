#ifndef UINT1024_H_
#define UINT1024_H_

#include <ostream>

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;

const int UINT1024_LENGTH = 1024;
const int UINT1024_DIGIT = UINT1024_LENGTH / 32;

class uint1024 {

private:
    uint digit[UINT1024_DIGIT];

public:
    uint1024();
    uint1024(uint64 var);
    uint1024(const char * varHex);
    uint1024(const uint1024 & var);
    virtual ~uint1024();
    
public:
    //赋值运算
    uint1024 & operator = (uint64 var);
    uint1024 & operator = (const char * varHex);
    uint1024 & operator = (const uint1024 & var);

    //比较运算
    bool operator == (uint64) const;
    bool operator < (uint64) const;
    bool operator <= (uint64) const;
    bool operator != (uint64) const;
    bool operator > (uint64) const;
    bool operator >= (uint64) const;
    bool operator == (const uint1024 & var) const;
    bool operator < (const uint1024 & var) const;
    bool operator <= (const uint1024 & var) const;
    bool operator != (const uint1024 & var) const;
    bool operator > (const uint1024 & var) const;
    bool operator >= (const uint1024 & var) const;

    //位运算
    uint1024 operator ~ () const;
    uint1024 & operator <<= (uint var);
    uint1024 & operator >>= (uint var);
    uint1024 operator >> (uint var) const;
    uint1024 operator << (uint var) const;
    uint1024 & operator |= (uint64 var);
    uint1024 & operator &= (uint64 var);
    uint1024 & operator ^= (uint64 var);
    uint1024 & operator |= (const uint1024 & var);
    uint1024 & operator &= (const uint1024 & var);
    uint1024 & operator ^= (const uint1024 & var);
    uint1024 operator | (uint64 var) const;
    uint1024 operator & (uint64 var) const;
    uint1024 operator ^ (uint64 var) const;
    uint1024 operator | (const uint1024 & var) const;
    uint1024 operator & (const uint1024 & var) const;
    uint1024 operator ^ (const uint1024 & var) const;

    //代数运算
    uint1024 & operator += (uint64 var);
    uint1024 & operator -= (uint64 var);
    uint1024 & operator *= (uint64 var);
    uint1024 & operator /= (uint64 var);
    uint1024 & operator %= (uint64 var);
    uint1024 & operator += (const uint1024 & var);
    uint1024 & operator -= (const uint1024 & var);
    uint1024 & operator *= (const uint1024 & var);
    uint1024 & operator /= (const uint1024 & var);
    uint1024 & operator %= (const uint1024 & var);
    uint1024 operator + (uint64 var) const;
    uint1024 operator - (uint64 var) const;
    uint1024 operator * (uint64 var) const;
    uint1024 operator / (uint64 var) const;
    uint1024 operator % (uint64 var) const;
    uint1024 operator + (const uint1024 & var) const;
    uint1024 operator - (const uint1024 & var) const;
    uint1024 operator * (const uint1024 & var) const;
    uint1024 operator / (const uint1024 & var) const;
    uint1024 operator % (const uint1024 & var) const;

public:
    //其他函数
    uint64 toUint64() const;
    uint getLength() const;
    void setBit(uint i, uint v);
    uint getBit(uint i) const;
    void printHex() const;
    void random(uint length);
    friend std::ostream & operator << (std::ostream & out, const uint1024 & var);
};

#endif