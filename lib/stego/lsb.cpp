#include "lsb.hpp"

Lsb::Lsb(QObject *parent) : QObject(parent)
{

}

bool Lsb::encode(QString data, QByteArray &container)
{
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream << data.toLocal8Bit();
    auto bits = toBitArray(bytes);

    if(container.count() < channel(bits.count()))
    {
        qWarning() << "Container is too small";
        return 0;
    }

    for(int i = 0; i < bits.count(); i++)
    {
        int index = channel(i);
        container[index] = changeBit(container[index], bits[i]);
    }

    return 1;
}

QByteArray Lsb::decode(const QByteArray &container)
{
    QBitArray bits((container.count() - sizeof(QRgb)) * 8);
    QByteArray bytes = container.mid(1 << 7);
    QBitArray len(sizeof(QRgb) * 8);

    auto f = [this](int length, QBitArray &bits, const QByteArray &bytes)
    {
        for(int i = 0; i < length; i++)
        {
            int index = channel(i);
            bits[i] = bytes[index] & 1;
        }
    };

    f(len.count(), len, container);

    bool ok;
    int length = toByteArray(len)
            .toHex().toInt(&ok, 16) * 8;

    if(!ok)
    {
        qWarning() << "Bad message length";
        return QByteArray();
    }

    f(length, bits, bytes);

    return toByteArray(bits);
}

int Lsb::channel(int bitIndex)
{
    return (bitIndex + 1) * sizeof(QRgb) - 2;
}

