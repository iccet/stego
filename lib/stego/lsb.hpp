#ifndef LSB_HPP
#define LSB_HPP

#include <QObject>
#include <QDataStream>

#include "bits.hpp"
#include "abstractencoder.hpp"

class Lsb : public QObject, public AbstractEncoder
{
    Q_OBJECT
    Q_INTERFACES(AbstractEncoder)

private:
    inline int channel(int bitIndex);

public:
    explicit Lsb(QObject *parent = nullptr);
    virtual ~Lsb() = default;

    bool encode(QString data, QByteArray &container) override;
    bool encode(QString data, uchar *container, int size) override;

    QByteArray decode(const uchar *container, int size) override;
    QByteArray decode(const QByteArray &container) override;
};

#endif // LSB_HPP
