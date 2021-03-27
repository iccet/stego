#include "kutter.hpp"

Kutter::Kutter(QObject *parent)
    : QObject(parent)
    , _generator(QRandomGenerator::global())
    , _q(.1)
    , _c(4)
{
}

bool Kutter::encode(QString data, QByteArray &container)
{
    Q_ASSERT(std::accumulate(container.begin(), container.end(), 0));

    QByteArray bytes = data.toLocal8Bit();
    auto bits = toBitArray(bytes);

    std::uniform_int_distribution<int> distribution(0, container.count() / sizeof(QRgb) - 1);

    bool ok;
    for (int i = 0; i < bits.count(); i++)
    {
        int p = distribution(*const_cast<QRandomGenerator *>(_generator)) * sizeof(QRgb);
        QColor c = container.mid(p, 4).toHex().toUInt(&ok, 16);

        Q_ASSERT(ok);
        auto d = _q * delta(c);
        container[p + 2] = c.blue() + (bits[i] ? d : -d);
    }

    return 1;
}

QRgb Kutter::delta(QColor color)
{
    return 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
}

bool Kutter::encode(QString data, uchar *container, int size)
{
    return 0;
}

QByteArray Kutter::decode(const uchar *container, int size)
{
    QByteArray bytes = QByteArray::fromRawData((const char*)container, size);
    return decode(bytes);
}

QByteArray Kutter::decode(const QByteArray &container)
{
    const int _c_by_px = _c * sizeof(QRgb);

    QBitArray bits((container.count() - sizeof(QRgb)) * CHAR_BIT);

    for (int i = 0; i < container.count(); i += sizeof(QRgb))
    {
        QByteArray strip = container.mid(i - _c_by_px, _c_by_px);
        strip += container.mid(i + sizeof(QRgb), _c_by_px);

        auto begin = std::next(strip.cbegin(), sizeof(QRgb) - 2);
        auto s = std::accumulate(
                ConstSkipIterator(sizeof(QRgb), begin),
                ConstSkipIterator(strip.cend()), 0);

        auto guess = (s - container[i + 2]) / _c / 2;
        bits[i] = std::signbit(container[i + 2] - guess);
    }
    return toByteArray(bits);
}

QByteArray Kutter::decode(int h, int w, const QByteArray &container)
{
    Q_ASSERT(w * h == container.count());

    const auto *p = reinterpret_cast<const char(*)[w]>(container.data());

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            qDebug() << QString::number(p[i][j], 16);
        }
}
