#include "lsb.hpp"

Lsb::Lsb(QObject *parent) : QObject(parent)
{

}

void Lsb::encode(QString data, QByteArray &container)
{
    for (auto i = 0; i < container.size(); i++)
    {
        container[i] = QColor(20, 150, 200).rgb();
    }
}

void Lsb::encode(QString data, QRgb *container, int size)
{
    auto bytes = data.toLocal8Bit();
    auto bits = toBitArray(bytes);

    Q_ASSERT(bits.count() < size);

    for(int i = 0; i < bits.count(); i++)
        container[i] |= bits[i];
}

QByteArray Lsb::decode(QRgb *container, int size)
{
    QByteArray bytes(100, Qt::Uninitialized);

    for(int i = 0; i < 100; i++)
    {
        bytes[i / 8] = (bytes.at(i / 8) | ((container[i] ? 1 : 0) << (7 - (i % 8))));;
    }

    return bytes;
}

