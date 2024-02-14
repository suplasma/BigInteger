#pragma once

#include <QString>

#include <iostream>

class BigInteger {
public:
    BigInteger();
    BigInteger(const BigInteger &big);
    BigInteger(BigInteger &&big);
    explicit BigInteger(const int num);
    explicit BigInteger(const long num);
    explicit BigInteger(const long long num);
    explicit BigInteger(const unsigned int num);
    explicit BigInteger(const unsigned long num);
    explicit BigInteger(const unsigned long long num);
    explicit BigInteger(const char *const num);
    explicit BigInteger(const std::string &num);
    explicit BigInteger(const QString &num);

    ~BigInteger();

    const char *const toCharPtrHex();
    std::string toStdHex() const;
    QString toHex() const;
    int toInt() const;
    long toLong() const;
    long long toLongLong() const;
    unsigned int toUInt() const;
    unsigned long toULong() const;
    unsigned long long toULongLong() const;
    const char *const toCharPtr();
    std::string toStdString() const;
    QString toString() const;
    bool toBool() const;

    BigInteger &operator=(const BigInteger &big);
    BigInteger &operator=(BigInteger &&big);

    BigInteger &operator+();
    BigInteger operator-() const;

    BigInteger &operator++();
    BigInteger &operator--();

    BigInteger operator++(int);
    BigInteger operator--(int);

    BigInteger operator>>(const size_t n) const;
    BigInteger operator<<(const size_t n) const;

    BigInteger operator+(const BigInteger &big) const;
    BigInteger operator-(const BigInteger &big) const;
    BigInteger operator*(const BigInteger &big) const;
    BigInteger operator/(const BigInteger &big) const;
    BigInteger operator%(const BigInteger &big) const;

    bool operator<(const BigInteger &big) const;
    bool operator>(const BigInteger &big) const;
    bool operator<=(const BigInteger &big) const;
    bool operator>=(const BigInteger &big) const;
    bool operator==(const BigInteger &big) const;
    bool operator!=(const BigInteger &big) const;

    BigInteger operator|(const BigInteger &big) const;
    BigInteger operator&(const BigInteger &big) const;
    BigInteger operator^(const BigInteger &big) const;
    BigInteger operator~() const;
    BigInteger operator!() const;

    BigInteger &operator>>=(const size_t n);
    BigInteger &operator<<=(const size_t n);

    BigInteger &operator+=(const BigInteger &big);
    BigInteger &operator-=(const BigInteger &big);
    BigInteger &operator*=(const BigInteger &big);
    BigInteger &operator/=(const BigInteger &big);
    BigInteger &operator%=(const BigInteger &big);

    BigInteger &operator|=(const BigInteger &big);
    BigInteger &operator&=(const BigInteger &big);
    BigInteger &operator^=(const BigInteger &big);

    BigInteger abs() const;
    BigInteger pow(const BigInteger &big) const;
    std::pair<BigInteger, BigInteger> divide(const BigInteger &big) const;

private:
    enum class Sign { POSITIVE, NEGATIVE };

    BigInteger(const size_t size, Sign sign);

    void pushFront(const unsigned char c, const size_t n = 1);
    void pushBack(const unsigned char c, const size_t n = 1);
    void popFront(const size_t n = 1);
    void popBack(const size_t n = 1);
    void popNull();
    char hexChar(const unsigned char c) const;
    void halfString(char *const str, const size_t size) const;
    void doubleString(char *&str, size_t &size) const;
    void halfString(std::string &str) const;
    void doubleString(std::string &str) const;
    void halfString(QString &str) const;
    void doubleString(QString &str) const;

    Sign _sign;
    size_t _size;
    unsigned char *_number;
    char *_str = nullptr;
};
