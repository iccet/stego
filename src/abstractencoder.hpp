#ifndef ABSTRACTENCODER_HPP
#define ABSTRACTENCODER_HPP

#include <QObject>
#include <QDebug>
#include <QRgb>
#include <QColor>
#include <QBitArray>

class AbstractEncoder
{
public:
    AbstractEncoder() = default;
    virtual ~AbstractEncoder() = default;

    /**
     * Encode a raw data.
     *
     * @param container Container whose values are encoded.
     */
    virtual void encode(QString data, QByteArray &container) = 0;
    virtual void encode(QString data, QRgb *container, int size) = 0;

private:
    /**
     * @href https://wiki.qt.io/Working_with_Raw_Data
     */
    QBitArray raw(QByteArray &array);

};

#endif // ABSTRACTENCODER_HPP
