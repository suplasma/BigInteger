#include <QApplication>
#include <QDateTime>
#include <QDebug>

#include <iostream>
#include <thread>

#include <biginteger.h>
#include <math.h>

#include <integration/app-connector.h>

void f(int big)
{
    int *pr = new int[big];
    pr[0] = 2;
    int n = 1;
    bool flag;
    int p;
    for (int i = 3; i < big; ++i) {
        flag = true;
        p = sqrt(i);
        for (int j = 2; j <= p; ++j) {
            if (i % j == 0) {
                flag = false;
            }
        }
        if (flag) {
            pr[n] = i;
            ++n;
        }
    }

    delete[] pr;
}

int p(int big)
{
    bool flag;
    int p;
    for (int i = big;; ++i) {
        flag = true;
        p = sqrt(i);
        for (int j = 2; j <= p; ++j) {
            if (i % j == 0) {
                flag = false;
            }
        }
        if (flag) {

            return i;
        }
    }
}

qulonglong p(qulonglong big)
{
    bool flag;
    qulonglong p;
    for (qulonglong i = big;; ++i) {
        flag = true;
        p = sqrt(i);
        for (qulonglong j = 2ull; j <= p; ++j) {
            if (i % j == 0ull) {
                flag = false;
            }
        }
        if (flag) {

            return i;
        }
    }
}

BigInteger p(const BigInteger &big)
{
    bool flag;
    BigInteger n;
    for (auto i = big;; ++i) {
        flag = true;
        for (BigInteger j(2); (j * j) <= i; ++j) {
            if ((i % j) == n) {
                flag = false;
            }
        }
        if (flag) {

            return i;
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    service::integration::AppConnector appConnector(app);

    auto time = QDateTime::currentMSecsSinceEpoch();
    QList<int> list;
    BigInteger pow(1);
    list.clear();
    for (auto i = 2; i < 1000; ++i) {
        bool flag = true;
        for (auto &el : list) {
            if ((i % el) == 0) {
                flag = false;
            }
        }
        if (flag) {
            list.append(i);
            pow *= BigInteger(i);
        }
    }

    qCritical() << pow.toString();

    qCritical() << "FINISH" << QDateTime::currentMSecsSinceEpoch() - time;

    return app.exec();
}
