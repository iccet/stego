#ifndef KUTTER_HPP
#define KUTTER_HPP

#include <QObject>
#include <QDebug>
#include <QRgb>
#include <QColor>
#include <QBitArray>

class Kutter : public QObject
{
    Q_OBJECT
public:
    explicit Kutter(QObject *parent = nullptr);

    /**
     * Encode a raw data.
     *
     * @param array Container whose values are encoded.
     */
    void encode(QByteArray &array);
    void encode(QRgb *data, int size);

private:
    /**
     * @href https://wiki.qt.io/Working_with_Raw_Data
     */
    QBitArray raw(QByteArray &array);
};

#endif // KUTTER_HPP
