#include "lsb.hpp"

Lsb::Lsb(QObject *parent) : QObject(parent)
{

}

void Lsb::encode(QString data, QByteArray &container)
{
    auto bytes = data.toLocal8Bit();
    auto bits = toBitArray(bytes);

    Q_ASSERT(bits.count() < container.count() * sizeof(QRgb));

    for(int i = 0; i < bits.count(); i++)
    {
        const int index = i * sizeof(QRgb) - 2;
        container[index] = changeBit(container[index], bits[i]);
    }
}

void Lsb::encode(QString data, QRgb *container, int size)
{
    auto bytes = data.toLocal8Bit();
    auto bits = toBitArray(bytes);

    Q_ASSERT(bits.count() < size);

    for(int i = 0; i < bits.count(); i++)
        container[i] = changeBit(container[i], bits[i]);
}

QByteArray Lsb::decode(QRgb *container, int size)
{
    QByteArray bytes(size, 0);
    return bytes;
}

QByteArray Lsb::decode(QByteArray &container)
{
    QByteArray bytes(container.count(), 0);

    for(int i = 0; i < container.count(); i++)
    {
        bytes[i] = container[i];

    }
    return container;
}

