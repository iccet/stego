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

    std::uniform_int_distribution<int> distribution(_c, container.count() / sizeof(QRgb) - _c - 1);

    bool ok;
    for (int i = 0; i < bits.count(); i++)
    {
        int p = distribution(*const_cast<QRandomGenerator *>(_generator)) * sizeof(QRgb);
        QColor c = container.mid(p - 1, sizeof(QRgb)).toHex().toUInt(&ok, 16);

        Q_ASSERT(ok);
        Q_ASSERT(container.at(p + 2) == char(c.blue()));
        auto d = _q * delta(c);
        container[p + 2] = container[p + 2] + (bits[i] ? d : -d);
    }
    qDebug() << "Data" << bits;

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
    const int _start = _c * sizeof(QRgb);

    QBitArray bits(container.count());

    for (int i = _start; i < container.count() - _start; i += sizeof(QRgb))
    {
        QByteArray strip = container.mid(i - _start, 2 * _start + sizeof(QRgb));
        Q_ASSERT(strip.count() / sizeof(QRgb) == _c * 2 + 1);

        auto begin = std::next(strip.cbegin(), sizeof(QRgb) - 2);
        auto s = std::accumulate(
                ConstSkipIterator(sizeof(QRgb), begin),
                ConstSkipIterator(strip.cend()), 0);

        auto guess = s / _c / 2;
        bits[int(i / sizeof(QRgb)) - _c] = std::signbit( guess - container[i + 2]);
    }
    qDebug() << "Encoded" << bits;
    return toByteArray(bits);
}

QByteArray Kutter::decode(int h, int w, const QByteArray &container)
{
    Q_ASSERT_X(false, __FILE__, "Not implemented");
    Q_ASSERT(w * h == container.count());

    const auto *p = reinterpret_cast<const char(*)[w]>(container.data());

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            qDebug() << QString::number(p[i][j], 16);
        }
}
