#include "biginteger.h"

#include <QDebug>

BigInteger::BigInteger() : _sign(Sign::POSITIVE), _size(0), _number(new unsigned char[0]) {}

BigInteger::BigInteger(const BigInteger &big) :
    _sign(big._sign), _size(big._size), _number(new unsigned char[big._size])
{
    for (size_t i = 0; i < _size; ++i) {
        _number[i] = big._number[i];
    }
}

BigInteger::BigInteger(BigInteger &&big) :
    _sign(big._sign), _size(big._size), _number(big._number)
{
    big._sign = Sign::POSITIVE;
    big._size = 0;
    big._number = new unsigned char[0];
}

BigInteger::BigInteger(const int num) : _size(0), _number(new unsigned char[0])
{
    unsigned int n;
    if (num >= 0) {
        _sign = Sign::POSITIVE;
        n = num;

    } else {
        _sign = Sign::NEGATIVE;
        n = -num;
    }

    while (n) {
        pushBack(n & 255);
        n >>= 8;
    }
}

BigInteger::BigInteger(const long num) : _size(0), _number(new unsigned char[0])
{
    unsigned long n;
    if (num >= 0) {
        _sign = Sign::POSITIVE;
        n = num;

    } else {
        _sign = Sign::NEGATIVE;
        n = -num;
    }

    while (n) {
        pushBack(n & 255);
        n >>= 8;
    }
}

BigInteger::BigInteger(const long long num) : _size(0), _number(new unsigned char[0])
{
    unsigned long long n;
    if (num >= 0) {
        _sign = Sign::POSITIVE;
        n = num;

    } else {
        _sign = Sign::NEGATIVE;
        n = -num;
    }

    while (n) {
        pushBack(n & 255);
        n >>= 8;
    }
}

BigInteger::BigInteger(const unsigned int num) :
    _sign(Sign::POSITIVE), _size(0), _number(new unsigned char[0])
{
    unsigned int n = num;

    while (n) {
        pushBack(n & 255);
        n >>= 8;
    }
}

BigInteger::BigInteger(const unsigned long num) :
    _sign(Sign::POSITIVE), _size(0), _number(new unsigned char[0])
{
    unsigned long n = num;

    while (n) {
        pushBack(n & 255);
        n >>= 8;
    }
}

BigInteger::BigInteger(const unsigned long long num) :
    _sign(Sign::POSITIVE), _size(0), _number(new unsigned char[0])
{
    unsigned long long n = num;

    while (n) {
        pushBack(n & 255);
        n >>= 8;
    }
}

BigInteger::BigInteger(const char *const num) : _size(0), _number(new unsigned char[0])
{
    size_t size = 0;
    while (num[size] != '\0') {
        ++size;
    }

    char *n = new char[size];

    for (size_t i = 0; i < size; ++i) {
        n[i] = num[i];
    }

    if (n[0] == '-') {
        _sign = Sign::NEGATIVE;
        char *array = new char[size - 1];
        --size;

        for (size_t i = 0; i < size; ++i) {
            array[i] = n[i + 1];
        }

        delete[] n;
        n = array;
    } else {
        _sign = Sign::POSITIVE;
    }

    while (size) {
        unsigned char c = 0;

        for (int i = 0; i < 8; ++i) {
            c += (n[size - 1] & 1) << i;
            halfString(n, size);

            if (n[0] == '0') {
                char *array = new char[size - 1];
                --size;

                for (size_t i = 0; i < size; ++i) {
                    array[i] = n[i + 1];
                }

                delete[] n;
                n = array;
            }

            if (size == 0) {
                break;
            }
        }

        pushBack(c);
    }

    delete[] n;
}

BigInteger::BigInteger(const std::string &num) : _size(0), _number(new unsigned char[0])
{
    std::string n = num;

    if (n.front() == '-') {
        _sign = Sign::NEGATIVE;
        n = n.substr(1);
    } else {
        _sign = Sign::POSITIVE;
    }

    while (n.size()) {
        unsigned char c = 0;

        for (int i = 0; i < 8; ++i) {
            c += (n.back() & 1) << i;
            halfString(n);

            if (n.empty()) {
                break;
            }
        }

        pushBack(c);
    }
}

BigInteger::BigInteger(const QString &num) : _size(0), _number(new unsigned char[0])
{
    QString n = num;

    if (n.front() == '-') {
        _sign = Sign::NEGATIVE;
        n = n.right(n.size() - 1);
    } else {
        _sign = Sign::POSITIVE;
    }

    while (n.size()) {
        unsigned char c = 0;

        for (int i = 0; i < 8; ++i) {
            c += (n.back().digitValue() & 1) << i;
            halfString(n);

            if (n.isEmpty()) {
                break;
            }
        }

        pushBack(c);
    }
}

BigInteger::~BigInteger()
{
    delete[] _number;

    if (_str != nullptr) {
        delete[] _str;
    }
}

const char *const BigInteger::toCharPtrHex()
{
    if (_str != nullptr) {
        delete[] _str;
    }

    if (_sign == Sign::NEGATIVE) {
        if (_size > 0) {
            _str = new char[3 * _size + 2];
            _str[0] = '-';
            _str[1] = ' ';

            size_t n = 1;
            for (size_t i = _size - 1; i < _size; --i) {
                _str[++n] = hexChar(_number[i] >> 4);
                _str[++n] = hexChar(_number[i] & 15);
                _str[++n] = ' ';
            }

            _str[n] = '\0';

        } else {
            _str = new char[5];
            _str[0] = '-';
            _str[1] = ' ';
            _str[2] = '0';
            _str[3] = '0';
            _str[4] = '\0';
        }
    } else {
        if (_size > 0) {
            _str = new char[3 * _size];
            size_t n = -1;
            for (size_t i = _size - 1; i < _size; --i) {
                _str[++n] = hexChar(_number[i] >> 4);
                _str[++n] = hexChar(_number[i] & 15);
                _str[++n] = ' ';
            }

            _str[n] = '\0';
        } else {
            _str = new char[3];
            _str[0] = '0';
            _str[1] = '0';
            _str[2] = '\0';
        }
    }

    return _str;
}

std::string BigInteger::toStdHex() const
{
    std::string hex;

    if (_sign == Sign::NEGATIVE) {
        hex.append("- ");
    }

    if (_size > 0) {
        for (size_t i = _size - 1; i < _size; --i) {
            hex.push_back(hexChar(_number[i] >> 4));
            hex.push_back(hexChar(_number[i] & 15));
            hex.push_back(' ');
        }

        hex.pop_back();
    } else {
        hex.append("00");
    }

    return hex;
}

QString BigInteger::toHex() const
{
    QString hex;

    if (_sign == Sign::NEGATIVE) {
        hex.append("- ");
    }

    if (_size > 0) {
        for (size_t i = _size - 1; i < _size; --i) {
            hex.push_back(hexChar(_number[i] >> 4));
            hex.push_back(hexChar(_number[i] & 15));
            hex.push_back(' ');
        }

        hex = hex.left(hex.size() - 1);
    } else {
        hex.append("00");
    }

    return hex;
}

int BigInteger::toInt() const
{
    int num = 0;

    if (_sign == Sign::POSITIVE) {
        for (size_t i = _size - 1; i < _size; --i) {
            num <<= 8;
            num += _number[i];
        }
    } else {
        for (size_t i = _size - 1; i < _size; --i) {
            num <<= 8;
            num -= _number[i];
        }
    }

    return num;
}

long BigInteger::toLong() const
{
    long num = 0;
    if (_sign == Sign::POSITIVE) {
        for (size_t i = _size - 1; i < _size; --i) {
            num <<= 8;
            num += _number[i];
        }
    } else {
        for (size_t i = _size - 1; i < _size; --i) {
            num <<= 8;
            num -= _number[i];
        }
    }

    return num;
}

long long BigInteger::toLongLong() const
{
    long long num = 0;

    if (_sign == Sign::POSITIVE) {
        for (size_t i = _size - 1; i < _size; --i) {
            num <<= 8;
            num += _number[i];
        }
    } else {
        for (size_t i = _size - 1; i < _size; --i) {
            num <<= 8;
            num -= _number[i];
        }
    }

    return num;
}

unsigned int BigInteger::toUInt() const
{
    unsigned int num = 0;

    for (size_t i = _size - 1; i < _size; --i) {
        num <<= 8;
        num += _number[i];
    }

    return num;
}

unsigned long BigInteger::toULong() const
{
    unsigned long num = 0;

    for (size_t i = _size - 1; i < _size; --i) {
        num <<= 8;
        num += _number[i];
    }

    return num;
}

unsigned long long BigInteger::toULongLong() const
{
    unsigned long long num = 0;

    for (size_t i = _size - 1; i < _size; --i) {
        num <<= 8;
        num += _number[i];
    }

    return num;
}

const char *const BigInteger::toCharPtr()
{
    if (_str != nullptr) {
        delete[] _str;
    }

    _str = new char[2];
    _str[0] = '0';
    size_t size = 1;

    for (size_t i = _size - 1; i < _size; --i) {
        for (int j = 7; j >= 0; --j) {
            doubleString(_str, size);
            _str[size - 1] += (_number[i] >> j) & 1;
        }
    }

    if (_sign == Sign::NEGATIVE) {
        char *array = new char[size + 2];
        array[0] = '-';

        for (size_t i = 0; i < size; ++i) {
            array[i + 1] = _str[i];
        }

        delete[] _str;
        _str = array;
        ++size;
    }
    _str[size] = '\0';

    return _str;
}

std::string BigInteger::toStdString() const
{
    std::string str = "0";

    for (size_t i = _size - 1; i < _size; --i) {
        for (int j = 7; j >= 0; --j) {
            doubleString(str);
            str[str.size() - 1] += (_number[i] >> j) & 1;
        }
    }

    if (_sign == Sign::NEGATIVE) {
        str.insert(0, 1, '-');
    }

    return str;
}

QString BigInteger::toString() const
{
    QString str = "0";

    for (size_t i = _size - 1; i < _size; --i) {
        for (int j = 7; j >= 0; --j) {
            doubleString(str);
            str.replace(
                str.size() - 1, 1,
                QString::number(str[str.size() - 1].digitValue() + ((_number[i] >> j) & 1)));
        }
    }

    if (_sign == Sign::NEGATIVE) {
        str.insert(0, '-');
    }

    return str;
}

bool BigInteger::toBool() const
{
    return _size;
}

BigInteger &BigInteger::operator=(const BigInteger &big)
{
    unsigned char *arr = new unsigned char[big._size];

    _sign = big._sign;
    _size = big._size;

    for (size_t i = 0; i < _size; ++i) {
        arr[i] = big._number[i];
    }

    delete[] _number;
    _number = arr;

    return *this;
}

BigInteger &BigInteger::operator=(BigInteger &&big)
{
    if (this != &big) {
        delete[] _number;

        _sign = big._sign;
        _size = big._size;
        _number = big._number;

        unsigned char *array = new unsigned char[0];
        big._sign = Sign::POSITIVE;
        big._number = array;
        big._size = 0;
    }

    return *this;
}

BigInteger &BigInteger::operator+()
{
    return *this;
}

BigInteger BigInteger::operator-() const
{
    BigInteger res(*this);
    res._sign = _sign == Sign::POSITIVE ? Sign::NEGATIVE : Sign::POSITIVE;
    return res;
}

BigInteger &BigInteger::operator++()
{
    int remember = _sign == Sign::POSITIVE ? 1 : -1;

    for (size_t i = 0; i < _size; ++i) {
        remember = _number[i] + remember;
        _number[i] = remember & 255;
        remember >>= 8;
    }

    if (remember) {
        pushBack(1);
    }

    if (_size > 0 && _number[_size - 1] == 0) {
        popBack();
    }

    if (_size == 0) {
        _sign = Sign::POSITIVE;
    }

    return *this;
}

BigInteger &BigInteger::operator--()
{
    int remember = _sign == Sign::POSITIVE ? -1 : 1;

    for (size_t i = 0; i < _size; ++i) {
        remember = _number[i] + remember;
        _number[i] = remember & 255;
        remember >>= 8;
    }

    if (_size == 0) {
        _sign = Sign::NEGATIVE;
    }

    if (remember) {
        pushBack(1);
    }

    if (_size > 0 && _number[_size - 1] == 0) {
        popBack();
    }

    return *this;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger res(*this);

    int remember = _sign == Sign::POSITIVE ? 1 : -1;

    for (size_t i = 0; i < _size; ++i) {
        remember = _number[i] + remember;
        _number[i] = remember & 255;
        remember >>= 8;
    }

    if (remember) {
        pushBack(1);
    }

    if (_size > 0 && _number[_size - 1] == 0) {
        popBack();
    }

    if (_size == 0) {
        _sign = Sign::POSITIVE;
    }

    return res;
}

BigInteger BigInteger::operator--(int)
{
    BigInteger res(*this);

    int remember = _sign == Sign::POSITIVE ? -1 : 1;

    for (size_t i = 0; i < _size; ++i) {
        remember = _number[i] + remember;
        _number[i] = remember & 255;
        remember >>= 8;
    }

    if (_size == 0) {
        _sign = Sign::NEGATIVE;
    }

    if (remember) {
        pushBack(1);
    }

    if (_size > 0 && _number[_size - 1] == 0) {
        popBack();
    }

    return res;
}

BigInteger BigInteger::operator>>(const size_t n) const
{
    BigInteger res(*this);

    size_t big = n >> 3;

    if (res._size >= big) {
        res.popFront(big);
    } else {
        res.popFront(res._size);
    }

    int small = n & 7;

    if (small && res._size) {
        size_t i = 0;

        for (; i < res._size - 1; ++i) {
            res._number[i] >>= small;
            res._number[i] += res._number[i + 1] << (8 - small);
        }

        res._number[i] >>= small;

        if (res._number[i] == 0) {
            res.popBack();
        }
    }

    return res;
}

BigInteger BigInteger::operator<<(const size_t n) const
{
    BigInteger res(*this);
    res.pushFront(0, n >> 3);

    int small = n & 7;

    if (small && res._size) {
        size_t i = res._size - 1;

        int n = res._number[i] >> (8 - small);
        if (n) {
            res.pushBack(n);
        }

        for (; i > 0; --i) {
            res._number[i] <<= small;
            res._number[i] += res._number[i - 1] >> (8 - small);
        }

        res._number[i] <<= small;
    }

    return res;
}

BigInteger BigInteger::operator+(const BigInteger &big) const
{
    BigInteger res(*this);

    if (_size < big._size) {
        res.pushBack(0, big._size - _size);
    }

    int remember = 0;
    size_t i = 0;

    if (res._sign == big._sign) {
        for (; i < big._size; ++i) {
            remember = res._number[i] + big._number[i] + remember;
            res._number[i] = remember & 255;
            remember >>= 8;
        }

        for (; i < _size; ++i) {
            remember = res._number[i] + remember;
            res._number[i] = remember & 255;
            remember >>= 8;
        }

        if (remember) {
            res.pushBack(1);
        }

        if (res._size > 0 && res._number[res._size - 1] == 0) {
            res.popBack();
        }
    } else {
        for (; i < big._size; ++i) {
            remember = res._number[i] - big._number[i] + remember;
            res._number[i] = remember & 255;
            remember >>= 8;
        }

        for (; i < _size; ++i) {
            remember = res._number[i] + remember;
            res._number[i] = remember & 255;
            remember >>= 8;
        }

        if (remember) {
            res = ~res;
            if (res._sign == Sign::POSITIVE) {
                res._sign = Sign::NEGATIVE;
                --res;
            } else {
                res._sign = Sign::POSITIVE;
                ++res;
            }
        }

        res.popNull();
    }

    return res;
}

BigInteger BigInteger::operator-(const BigInteger &big) const
{
    BigInteger res(*this);

    if (_size < big._size) {
        res.pushBack(0, big._size - _size);
    }

    int remember = 0;
    size_t i = 0;

    if (res._sign != big._sign) {
        for (; i < big._size; ++i) {
            remember = res._number[i] + big._number[i] + remember;
            res._number[i] = remember & 255;
            remember >>= 8;
        }

        for (; i < _size; ++i) {
            remember = res._number[i] + remember;
            res._number[i] = remember & 255;
            remember >>= 8;
        }

        if (remember) {
            res.pushBack(1);
        }

        if (res._size > 0 && res._number[res._size - 1] == 0) {
            res.popBack();
        }
    } else {
        for (; i < big._size; ++i) {
            remember = res._number[i] - big._number[i] + remember;
            res._number[i] = remember & 255;
            remember >>= 8;
        }

        for (; i < _size; ++i) {
            remember = res._number[i] + remember;
            res._number[i] = remember & 255;
            remember >>= 8;
        }

        if (remember) {
            res = ~res;
            if (res._sign == Sign::POSITIVE) {
                res._sign = Sign::NEGATIVE;
                --res;
            } else {
                res._sign = Sign::POSITIVE;
                ++res;
            }
        }

        res.popNull();
    }

    return res;
}

BigInteger BigInteger::operator*(const BigInteger &big) const
{
    BigInteger res;
    BigInteger p(*this);

    for (size_t i = 0; i < big._size; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (big._number[i] & (1 << j)) {
                res += p;
            }

            p += p;
        }
    }

    if (big._sign == Sign::NEGATIVE) {
        res._sign = static_cast<Sign>(!static_cast<bool>(res._sign));
    }

    return res;
}

BigInteger BigInteger::operator/(const BigInteger &big) const
{
    assert(big._size);
    BigInteger dividend(*this);
    BigInteger divisor(big);
    BigInteger res;

    dividend._sign = Sign::POSITIVE;
    divisor._sign = Sign::POSITIVE;

    size_t i = -1;
    while (dividend >= divisor) {
        divisor <<= 1;
        ++i;
    }
    size_t size = i + 1;

    for (; i < size; --i) {
        divisor >>= 1;
        if (dividend >= divisor) {
            dividend -= divisor;
            res += BigInteger(1 << i);
        }
    }

    if (_sign != big._sign) {
        res._sign = Sign::NEGATIVE;
    }

    return res;
}

BigInteger BigInteger::operator%(const BigInteger &big) const
{
    assert(big._size);
    BigInteger dividend(*this);
    BigInteger divisor(big);
    BigInteger res;

    dividend._sign = Sign::POSITIVE;
    divisor._sign = Sign::POSITIVE;

    size_t i = -1;
    while (dividend >= divisor) {
        divisor <<= 1;
        ++i;
    }
    size_t size = i + 1;

    for (; i < size; --i) {
        divisor >>= 1;
        if (dividend >= divisor) {
            dividend -= divisor;
            res += BigInteger(1 << i);
        }
    }

    dividend._sign = _sign;

    return dividend;
}

bool BigInteger::operator<(const BigInteger &big) const
{
    if (_sign != big._sign) {
        if (_sign == Sign::NEGATIVE) {
            return true;
        } else {
            return false;
        }
    }

    if (_size < big._size) {
        return !static_cast<bool>(_sign);
    }

    if (_size > big._size) {
        return static_cast<bool>(_sign);
    }

    for (size_t i = _size - 1; i < _size; --i) {
        if (_number[i] < big._number[i]) {
            return !static_cast<bool>(_sign);
        }

        if (_number[i] > big._number[i]) {
            return static_cast<bool>(_sign);
        }
    }

    return false;
}

bool BigInteger::operator>(const BigInteger &big) const
{
    return big < *this;
}

bool BigInteger::operator<=(const BigInteger &big) const
{
    return !(big < *this);
}

bool BigInteger::operator>=(const BigInteger &big) const
{
    return !(*this < big);
}

bool BigInteger::operator==(const BigInteger &big) const
{
    if (_sign != big._sign) {
        return false;
    }

    if (_size != big._size) {
        return false;
    }

    for (size_t i = 0; i < _size; ++i) {
        if (_number[i] != big._number[i]) {
            return false;
        }
    }

    return true;
}

bool BigInteger::operator!=(const BigInteger &big) const
{
    return !(*this == big);
}

BigInteger BigInteger::operator|(const BigInteger &big) const
{
    size_t sizeSmall;
    size_t sizeBig;
    unsigned char *ptr;

    if (_size <= big._size) {
        sizeSmall = _size;
        sizeBig = big._size;
        ptr = big._number;
    } else {
        sizeSmall = big._size;
        sizeBig = _size;
        ptr = _number;
    }

    BigInteger res(sizeBig, _sign);

    size_t i = 0;
    for (; i < sizeSmall; ++i) {
        res._number[i] = _number[i] | big._number[i];
    }

    while (i < sizeBig) {
        res._number[i] = ptr[i];
        ++i;
    }

    return res;
}

BigInteger BigInteger::operator&(const BigInteger &big) const
{
    size_t size = _size <= big._size ? _size : big._size;

    BigInteger res(size, _sign);

    for (size_t i = 0; i < size; ++i) {
        res._number[i] = _number[i] & big._number[i];
    }

    res.popNull();

    return res;
}

BigInteger BigInteger::operator^(const BigInteger &big) const
{
    size_t sizeSmall;
    size_t sizeBig;
    unsigned char *ptr;

    if (_size <= big._size) {
        sizeSmall = _size;
        sizeBig = big._size;
        ptr = big._number;
    } else {
        sizeSmall = big._size;
        sizeBig = _size;
        ptr = _number;
    }

    BigInteger res(sizeBig, _sign);

    size_t i = 0;
    for (; i < sizeSmall; ++i) {
        res._number[i] = _number[i] ^ big._number[i];
    }

    while (i < sizeBig) {
        res._number[i] = ptr[i];
        ++i;
    }

    res.popNull();

    return res;
}

BigInteger BigInteger::operator~() const
{
    BigInteger res(_size, _sign);

    for (size_t i = 0; i < _size; ++i) {
        res._number[i] = ~_number[i];
    }

    res.popNull();

    return res;
}

BigInteger BigInteger::operator!() const
{
    BigInteger res;

    if (_size == 0) {
        unsigned char *arr = new unsigned char[1];
        arr[0] = 1;

        delete[] res._number;
        res._number = arr;
        res._size = 1;
    }

    return res;
}

BigInteger &BigInteger::operator>>=(const size_t n)
{
    size_t big = n >> 3;

    if (_size >= big) {
        popFront(big);
    } else {
        popFront(_size);
    }

    int small = n & 7;

    if (small && _size) {
        size_t i = 0;

        for (; i < _size - 1; ++i) {
            _number[i] >>= small;
            _number[i] += _number[i + 1] << (8 - small);
        }

        _number[i] >>= small;

        if (_number[i] == 0) {
            popBack();
        }
    }

    return *this;
}

BigInteger &BigInteger::operator<<=(const size_t n)
{
    pushFront(0, n >> 3);

    int small = n & 7;

    if (small && _size) {
        size_t i = _size - 1;

        int n = _number[i] >> (8 - small);
        if (n) {
            pushBack(n);
        }

        for (; i > 0; --i) {
            _number[i] <<= small;
            _number[i] += _number[i - 1] >> (8 - small);
        }

        _number[i] <<= small;
    }

    return *this;
}

BigInteger &BigInteger::operator+=(const BigInteger &big)
{
    if (_size < big._size) {
        pushBack(0, big._size - _size);
    }

    int remember = 0;
    size_t i = 0;

    if (_sign == big._sign) {
        for (; i < big._size; ++i) {
            remember = _number[i] + big._number[i] + remember;
            _number[i] = remember & 255;
            remember >>= 8;
        }

        for (; i < _size; ++i) {
            remember = _number[i] + remember;
            _number[i] = remember & 255;
            remember >>= 8;
        }

        if (remember) {
            pushBack(1);
        }

        if (_size > 0 && _number[_size - 1] == 0) {
            popBack();
        }
    } else {
        for (; i < big._size; ++i) {
            remember = _number[i] - big._number[i] + remember;
            _number[i] = remember & 255;
            remember >>= 8;
        }

        for (; i < _size; ++i) {
            remember = _number[i] + remember;
            _number[i] = remember & 255;
            remember >>= 8;
        }

        if (remember) {
            *this = ~*this;
            if (_sign == Sign::POSITIVE) {
                _sign = Sign::NEGATIVE;
                --*this;
            } else {
                _sign = Sign::POSITIVE;
                ++*this;
            }
        }

        popNull();
    }

    return *this;
}

BigInteger &BigInteger::operator-=(const BigInteger &big)
{
    if (_size < big._size) {
        pushBack(0, big._size - _size);
    }

    int remember = 0;
    size_t i = 0;

    if (_sign != big._sign) {
        for (; i < big._size; ++i) {
            remember = _number[i] + big._number[i] + remember;
            _number[i] = remember & 255;
            remember >>= 8;
        }

        for (; i < _size; ++i) {
            remember = _number[i] + remember;
            _number[i] = remember & 255;
            remember >>= 8;
        }

        if (remember) {
            pushBack(1);
        }

        if (_size > 0 && _number[_size - 1] == 0) {
            popBack();
        }
    } else {
        for (; i < big._size; ++i) {
            remember = _number[i] - big._number[i] + remember;
            _number[i] = remember & 255;
            remember >>= 8;
        }

        for (; i < _size; ++i) {
            remember = _number[i] + remember;
            _number[i] = remember & 255;
            remember >>= 8;
        }

        if (remember) {
            *this = ~*this;
            if (_sign == Sign::POSITIVE) {
                _sign = Sign::NEGATIVE;
                --*this;
            } else {
                _sign = Sign::POSITIVE;
                ++*this;
            }
        }

        popNull();
    }

    return *this;
}

BigInteger &BigInteger::operator*=(const BigInteger &big)
{
    BigInteger p(std::move(*this));

    for (size_t i = 0; i < big._size; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (big._number[i] & (1 << j)) {
                *this += p;
            }

            p += p;
        }
    }

    if (big._sign == Sign::NEGATIVE) {
        _sign = static_cast<Sign>(!static_cast<bool>(_sign));
    }

    return *this;
}

BigInteger &BigInteger::operator/=(const BigInteger &big)
{
    assert(big._size);
    BigInteger dividend(std::move(*this));
    BigInteger divisor(big);

    Sign sign = Sign::POSITIVE;

    if (dividend._sign != big._sign) {
        sign = Sign::NEGATIVE;
    }

    dividend._sign = Sign::POSITIVE;
    divisor._sign = Sign::POSITIVE;

    size_t i = -1;
    while (dividend >= divisor) {
        divisor <<= 1;
        ++i;
    }
    size_t size = i + 1;

    for (; i < size; --i) {
        divisor >>= 1;
        if (dividend >= divisor) {
            dividend -= divisor;
            *this += BigInteger(1 << i);
        }
    }

    _sign = sign;

    return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger &big)
{
    assert(big._size);
    BigInteger divisor(big);
    BigInteger res;

    Sign sign = _sign;

    _sign = Sign::POSITIVE;
    divisor._sign = Sign::POSITIVE;

    size_t i = -1;
    while (*this >= divisor) {
        divisor <<= 1;
        ++i;
    }
    size_t size = i + 1;

    for (; i < size; --i) {
        divisor >>= 1;
        if (*this >= divisor) {
            *this -= divisor;
            res += BigInteger(1 << i);
        }
    }

    _sign = sign;

    return *this;
}

BigInteger &BigInteger::operator|=(const BigInteger &big)
{
    size_t sizeSmall;
    size_t sizeBig;
    unsigned char *ptr;

    if (_size <= big._size) {
        sizeSmall = _size;
        sizeBig = big._size;
        ptr = big._number;

        if (_size < sizeBig) {
            pushBack(0, sizeBig - _size);
        }
    } else {
        sizeSmall = big._size;
        sizeBig = _size;
        ptr = _number;
    }

    size_t i = 0;
    for (; i < sizeSmall; ++i) {
        _number[i] = _number[i] | big._number[i];
    }

    while (i < sizeBig) {
        _number[i] = ptr[i];
        ++i;
    }

    return *this;
}

BigInteger &BigInteger::operator&=(const BigInteger &big)
{
    size_t size = _size <= big._size ? _size : big._size;

    for (size_t i = 0; i < size; ++i) {
        _number[i] &= big._number[i];
    }

    if (_size > size) {
        popBack(_size - size);
    }

    popNull();

    return *this;
}

BigInteger &BigInteger::operator^=(const BigInteger &big)
{
    size_t sizeSmall;
    size_t sizeBig;
    unsigned char *ptr;

    if (_size <= big._size) {
        sizeSmall = _size;
        sizeBig = big._size;
        ptr = big._number;

        if (_size < sizeBig) {
            pushBack(0, sizeBig - _size);
        }
    } else {
        sizeSmall = big._size;
        sizeBig = _size;
        ptr = _number;
    }

    size_t i = 0;
    for (; i < sizeSmall; ++i) {
        _number[i] = _number[i] ^ big._number[i];
    }

    while (i < sizeBig) {
        _number[i] = ptr[i];
        ++i;
    }

    popNull();

    return *this;
}

BigInteger BigInteger::abs() const
{
    BigInteger res(*this);
    res._sign = Sign::POSITIVE;
    return res;
}

BigInteger BigInteger::pow(const BigInteger &big) const
{
    BigInteger res(1);
    BigInteger p(*this);

    for (size_t i = 0; i < big._size; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (big._number[i] & (1 << j)) {
                res *= p;
            }

            p = p * p;
        }
    }

    return res;
}

std::pair<BigInteger, BigInteger> BigInteger::divide(const BigInteger &big) const
{
    assert(big._size);
    BigInteger dividend(*this);
    BigInteger divisor(big);
    BigInteger res;

    dividend._sign = Sign::POSITIVE;
    divisor._sign = Sign::POSITIVE;

    size_t i = -1;
    while (dividend >= divisor) {
        divisor <<= 1;
        ++i;
    }
    size_t size = i + 1;

    for (; i < size; --i) {
        divisor >>= 1;
        if (dividend >= divisor) {
            dividend -= divisor;
            res += BigInteger(1 << i);
        }
    }

    if (_sign != big._sign) {
        res._sign = Sign::NEGATIVE;
    }

    dividend._sign = _sign;

    return std::make_pair(res, dividend);
}

BigInteger::BigInteger(const size_t size, BigInteger::Sign sign) :
    _sign(sign), _size(size), _number(new unsigned char[size])
{
}

void BigInteger::pushFront(const unsigned char c, const size_t n)
{
    unsigned char *array = new unsigned char[_size + n];

    size_t i = 0;
    for (; i < n; ++i) {
        array[i] = c;
    }

    for (size_t j = 0; j < _size; ++j, ++i) {
        array[i] = _number[j];
    }

    delete[] _number;
    _number = array;
    _size += n;
}

void BigInteger::pushBack(const unsigned char c, const size_t n)
{
    unsigned char *array = new unsigned char[_size + n];

    size_t i = 0;
    for (; i < _size; ++i) {
        array[i] = _number[i];
    }

    _size += n;
    for (; i < _size; ++i) {
        array[i] = c;
    }

    delete[] _number;
    _number = array;
}

void BigInteger::popFront(const size_t n)
{
    unsigned char *array = new unsigned char[_size - n];

    for (size_t i = n; i < _size; ++i) {
        array[i - n] = _number[i];
    }

    delete[] _number;
    _number = array;
    _size -= n;
}

void BigInteger::popBack(const size_t n)
{
    unsigned char *array = new unsigned char[_size - n];

    for (size_t i = 0; i < _size - n; ++i) {
        array[i] = _number[i];
    }

    delete[] _number;
    _number = array;
    _size -= n;
}

void BigInteger::popNull()
{
    size_t i = _size - 1;
    for (; i < _size; --i) {
        if (_number[i] != 0) {
            break;
        }
    }

    popBack(_size - i - 1);
}

char BigInteger::hexChar(const unsigned char c) const
{
    if (c < 10) {
        return '0' + c;
    }

    return 'A' + c - 10;
}

void BigInteger::halfString(char *const str, const size_t size) const
{
    int remember = 0;
    int r;

    for (size_t i = 0; i < size; ++i) {
        r = 5 * remember + ((str[i] + '0') >> 1);
        remember = str[i] & 1;
        str[i] = r;
    }
}

void BigInteger::doubleString(char *&str, size_t &size) const
{
    int remember = 0;
    int r;

    for (size_t i = size - 1; i < size; --i) {
        r = ((str[i] - '0') << 1) + remember;
        str[i] = (r > 9 ? r - 10 : r) + '0';
        remember = r > 9;
    }

    if (remember) {
        char *array = new char[size + 2];
        array[0] = '1';

        for (size_t i = 0; i < size; ++i) {
            array[i + 1] = str[i];
        }

        array[size + 1] = '\0';

        delete[] str;
        str = array;
        ++size;
    }
}

void BigInteger::halfString(std::string &str) const
{
    int remember = 0;
    int r;

    for (size_t i = 0; i < str.size(); ++i) {
        r = 5 * remember + ((str.at(i) + '0') >> 1);
        remember = str.at(i) & 1;
        str.replace(i, 1, 1, r);
    }

    if (str.front() == '0') {
        str = str.substr(1);
    }
}

void BigInteger::doubleString(std::string &str) const
{
    int remember = 0;
    int r;

    for (size_t i = str.size() - 1; i < str.size(); --i) {
        r = ((str.at(i) - '0') << 1) + remember;
        str.replace(i, 1, 1, (r > 9 ? r - 10 : r) + '0');
        remember = r > 9;
    }

    if (remember) {
        str.insert(0, 1, '1');
    }
}

void BigInteger::halfString(QString &str) const
{
    int remember = 0;
    int r;

    for (int i = 0; i < str.size(); ++i) {
        r = 5 * remember + (str.at(i).digitValue() >> 1);
        remember = str.at(i).digitValue() & 1;
        str.replace(i, 1, r + '0');
    }

    if (str.front() == '0') {
        str.remove(0, 1);
    }
}

void BigInteger::doubleString(QString &str) const
{
    int remember = 0;
    int r;

    for (int i = str.size() - 1; i >= 0; --i) {
        r = (str.at(i).digitValue() << 1) + remember;
        str.replace(i, 1, (r > 9 ? r - 10 : r) + '0');
        remember = r > 9;
    }

    if (remember) {
        str.insert(0, '1');
    }
}
