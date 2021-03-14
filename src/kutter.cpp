#include "kutter.hpp"

Kutter::Kutter(QObject *parent) : QObject(parent)
{

}

void Kutter::encode(QByteArray &array)
{
    for (auto i = 0; i < array.size(); i++) {
        array[i] = QColor(20, 150, 200).rgb();
    }
}

void Kutter::encode(QRgb *data, int size)
{
    for (auto i = 0; i < size; i++) {
        data[i] = QColor(25, 150, 200).rgb();
    }
}

QBitArray raw(QByteArray &array)
{
    QBitArray bits(4 * array.length());

    for(int i = 0; i < array.count(); ++i)
        for(int b = 0; b < 8; b++)
            bits.setBit( i * 8 + b, array.at(i) & (1 << (7 - b)));

    return bits;
}
