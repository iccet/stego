#include "lsb.hpp"

Lsb::Lsb(QObject *parent) : QObject(parent)
{

}

void Lsb::encode(QString data, QByteArray &container)
{
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream << data.toLocal8Bit();
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
    QByteArray bytes = QByteArray::fromRawData((const char*)container, size);
    encode(data, bytes);

    int i = 0;
    foreach(auto byte, bytes)
    {
        container[i++] = byte;
    }
}

QByteArray Lsb::decode(const QRgb *container, int size)
{
    QByteArray bytes = QByteArray::fromRawData((const char*)container, size);
    return decode(bytes);
}

QByteArray Lsb::decode(const QByteArray &container)
{
    QBitArray bits(container.count() * 8);
    QByteArray bytes = container.mid(1 << 7);
    QBitArray len(sizeof(QRgb) * 8);

    auto f = [](int length, QBitArray &bits, const QByteArray &bytes)
    {
        for(int i = 0; i < length; i++)
        {
            int index = i * sizeof(QRgb) - 2;
            bits[i] = bytes[index] & 1;
        }
    };

    f(len.count(), len, container);

    bool ok;
    int length = toByteArray(len)
            .toHex().toInt(&ok, 16) * 8;

    if(!ok) qWarning() << "Bad message length";
    f(length, bits, bytes);

    return toByteArray(bits);
}

