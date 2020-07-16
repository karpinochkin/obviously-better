#ifndef QDEGREEOFTWO_H
#define QDEGREEOFTWO_H

#include <QString>
#include <QDebug>
#include <QtMath>
#include <QVector>

/// Класс отвечает за составление вектора степеней двойки для указанного числа
class QPowerOfTwo
{
public:
    ~QPowerOfTwo() = default;

    static QVector<quint32> GetValuesOfPowerOfTwo(quint32 value);
    static bool isPowerOfTwo(quint32 value);

private:
    QPowerOfTwo() = default;
    static QVector<quint32> valuesVector(quint32 value);
    static quint32 getNearestValueOfPowerOfTwo(QString binaryValue);
};

#endif // QDEGREEOFTWO_H
