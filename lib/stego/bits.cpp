#include "bits.hpp"

namespace Stg
{
    QBitArray toBitArray(const QByteArray &array)
    {
        QBitArray bits(8 * array.length());

        for(int i = 0; i < array.count(); ++i)
            for(int b = 0; b < 8; b++)
                bits.setBit(i * 8 + b, array.at(i) & (1 << (7 - b)));

        return bits;
    }

    QByteArray toByteArray(const QBitArray &array)
    {
        QByteArray bytes(array.count() / 8, 0);

        for(int i = 0; i < array.count(); ++i)
            bytes[i / 8] = (bytes.at(i / 8) | ((array[i] ? 1 : 0) << (7 - (i % 8))));

        return bytes;
    }

    char changeBit(char byte, bool bit, int position)
    {
        return byte ^ ((-bit ^ byte) & (1UL << position));
    }

    void copy(const QByteArray &src, QByteArray &dst)
    {
        dst.setRawData(src.data(), src.count());
    }

    QVector<QVector<QByteArray::value_type>> copy(const QByteArray &src, int w)
    {
        const auto *p = reinterpret_cast<const char(*)[w]>(src.data());
        QVector<QVector<QByteArray::value_type>> matrix(w / sizeof(QRgb));

        int r = 0;
        for (auto &row : matrix)
        {
            auto begin = std::next(p[r], sizeof(QRgb) - 2);
            std::copy(ConstSkipIterator(sizeof(QRgb), begin),
                      ConstSkipIterator(p[r++] + w), std::back_inserter(row));
        }

        return matrix;
    }

} // namespace Stg
