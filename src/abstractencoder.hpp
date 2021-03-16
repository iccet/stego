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
     * @param data
     * @param container
     */
    virtual void encode(QString data, QByteArray &container) = 0;

    /**
     * Encode a raw data.
     *
     * @param data
     * @param container
     * @param size
     */
    virtual void encode(QString data, QRgb *container, int size) = 0;

    /**
     * Decode a raw data.
     *
     * @param container
     */
    virtual QByteArray decode(QRgb *container, int size) = 0;

    /**
     * Decode a raw data.
     *
     * @param container
     */
    virtual QByteArray decode(QByteArray &container) = 0;


protected:
    /**
     * @href https://wiki.qt.io/Working_with_Raw_Data
     */
    QBitArray toBitArray(QByteArray &array);
    QByteArray toByteArray(QBitArray &array);

};

Q_DECLARE_INTERFACE(AbstractEncoder, "encoder")

#endif // ABSTRACTENCODER_HPP
