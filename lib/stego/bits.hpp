#ifndef BITS_HPP
#define BITS_HPP

#include <QBitArray>
#include <QVector>
#include <QRgb>

#include <numeric>

#include "skip.hpp"

/**
 * @href https://wiki.qt.io/Working_with_Raw_Data
 */
QBitArray toBitArray(const QByteArray &array);
QByteArray toByteArray(const QBitArray &array);

char changeBit(char byte, bool bit, int position = 0);

void copy(const QByteArray &src, QByteArray &dst);
QVector<QVector<QByteArray::value_type>> copy(const QByteArray &src, int w);

#endif // BITS_HPP
