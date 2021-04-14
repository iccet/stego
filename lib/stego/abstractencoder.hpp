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
    virtual bool encode(QString data, QByteArray &container) = 0;

    /**
     * Encode a raw data.
     *
     * @param data
     * @param container
     * @param size
     */
    virtual bool encode(QString data, uchar *container, int size);

    /**
     * Decode a raw data.
     *
     * @param container
     */
    virtual QByteArray decode(const uchar *container, int size);

    /**
     * Decode a raw data.
     *
     * @param container
     */
    virtual QByteArray decode(const QByteArray &container) = 0;


protected:
};

Q_DECLARE_INTERFACE(AbstractEncoder, "encoder")

#endif // ABSTRACTENCODER_HPP
