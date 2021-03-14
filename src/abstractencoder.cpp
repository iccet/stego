#include "abstractencoder.hpp"

QBitArray AbstractEncoder::raw(QByteArray &array)
{
    QBitArray bits(4 * array.length());

    for(int i = 0; i < array.count(); ++i)
        for(int b = 0; b < 8; b++)
            bits.setBit( i * 8 + b, array.at(i) & (1 << (7 - b)));

    return bits;
}
