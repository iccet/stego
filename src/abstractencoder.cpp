#include "abstractencoder.hpp"

QBitArray AbstractEncoder::toBitArray(QByteArray &array)
{
    QBitArray bits(8 * array.length());

    for(int i = 0; i < array.count(); ++i)
        for(int b = 0; b < 8; b++)
            bits.setBit(i * 8 + b, array.at(i) & (1 << (7 - b)));

    return bits;
}

QByteArray AbstractEncoder::toByteArray(QBitArray &array)
{
    QByteArray bytes(array.count(), 0);

    for(int i = 0; i < array.count(); ++i)
        bytes[i / 8] = (bytes.at(i / 8) | ((array[i] ? 1 : 0) << (7 - (i % 8))));

    return bytes;
}
