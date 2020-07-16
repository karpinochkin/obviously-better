#include "qpoweroftwo.h"

QVector<quint32> QPowerOfTwo::GetValuesOfPowerOfTwo(quint32 value)
{
    try {
        if (value < 4) {
            throw QString(" value < 4");
        }

        QString binary = QString("%1").arg(value, 0, 2);
        value = getNearestValueOfPowerOfTwo(binary);
        return valuesVector(value);

    } catch (const QString& err ) {
        qDebug() << "QPowerOfTwo::GetValuesOfPowerOfTwo(quint32 value) : "<< err;
        return QVector<quint32>{};
    }
}

bool QPowerOfTwo::isPowerOfTwo(quint32 value)
{
    QString binary = QString("%1").arg(value, 0, 2);
    auto nearestValueOfPowerOfTwo = getNearestValueOfPowerOfTwo(binary);

    if (value == nearestValueOfPowerOfTwo) {
        return true;
    }
    return false;
}

quint32 QPowerOfTwo::getNearestValueOfPowerOfTwo(QString binaryValue)
{
    int size = binaryValue.size() - 1;
    return qPow(2, size);
}

QVector<quint32> QPowerOfTwo::valuesVector(quint32 value)
{
    QVector<quint32> output{};

    while (value != 2) {
        output.push_back(value);
        value /= 2;
    }

    return output;
}
